// Includes
#include "RecommenderSystem.h"
#include "RSUser.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#define ZERO 0
#define FLOAT_ZERO 0.0

/**
 * Private Helper Function
 * For full Documentation of methods check the header file
 */
double RecommenderSystem::calculate_norm (const vector<double> &vector) const
{
  double sum = ZERO;
  for (const auto& it : vector)
    {
      sum += (it * it);
    }
  return sqrt (sum);
}

/**
 * Private Helper Function
 * For full Documentation of methods check the header file
 */
vector<double> RecommenderSystem:: get_preference_vector
(map<sp_movie,double>& normalized_map)
{
  int num_of_features = (int) recommend_system.begin()->second->size();
  auto result_vector = vector<double> ();
  for (int i=0; i<num_of_features;i++)
    {
      result_vector.push_back (ZERO);
    }
  for (auto& it2 : normalized_map)
    {
      for (int i=0;i<num_of_features;i++)
        {
          auto cur_vec = vector<double>(*recommend_system[it2.first]);
          for (auto& it3 : cur_vec)
            {
              it3 *= it2.second;
            }
          for (int j=0; j<num_of_features;j++)
            {
              result_vector[j] += cur_vec[j];
            }
        }
    }
  return result_vector;
}

/**
 * Private Helper Function
 * For full Documentation of methods check the header file
 */
double RecommenderSystem:: calc_similarity (const vector<double>
    &pref_vec ,const vector<double> &features) const
  {
    auto pref_norm = calculate_norm (pref_vec);
    auto feat_norm = calculate_norm (features);
    auto orig_mult = std::inner_product (pref_vec.begin ()
        , pref_vec.end (), features.begin (), FLOAT_ZERO);
    return (orig_mult / (pref_norm * feat_norm));
  }

/**
 * Private Helper Function
 * For full Documentation of methods check the header file
 */
void RecommenderSystem::normalize_rank
(const RSUser& user, map<sp_movie,double>& user_rank)
{
  double sum = ZERO;
  int num_of_ranked = ZERO;
  for (auto& it : *user.get_ranks())
    {
      user_rank[it.first] = it.second;
      sum += it.second;
      num_of_ranked++;
    }
  for (auto& it: user_rank)
    {
      it.second -= (sum / num_of_ranked);
    }
}


/**
 * For full Documentation of methods check the header file
 */
sp_movie RecommenderSystem:: recommend_by_content (const RSUser &user)
{
  double max = ZERO;
  sp_movie rec_movie;
  map<sp_movie,double> user_rank = map<sp_movie,double>();
  normalize_rank (user, user_rank);
  vector<double> pref_num_vec = vector<double>();
  pref_num_vec = get_preference_vector (user_rank);
  // Iterate over all unseen movies
  for (auto &it: recommend_system)
    {
      auto cur_sp_movie = it.first;
      if (user.get_ranks()->find (cur_sp_movie) == user.get_ranks()->end())
        {
          auto similarity_val = calc_similarity
              (pref_num_vec, *it.second);
          if (similarity_val > max)
            {
              max = similarity_val;
              rec_movie = cur_sp_movie;
            }
        }
    }
  return rec_movie;
}

/**
 * For full Documentation of methods check the header file
 */
struct RecommenderSystem:: ComparePair
{
    bool operator()(const pair<sp_movie,double>& left, const
    pair<sp_movie,double>& right)
    {
      return left.second < right.second;
    }
};

/**
 * For full Documentation of methods check the header file
 */
map<sp_movie,double> RecommenderSystem:: find_k_similar
(const RSUser& user, const sp_movie &movie, int k)
  {
    auto similarity_map = map<sp_movie,double>();
    for (const auto& it: *user.get_ranks())
      {
        auto similarity = calc_similarity (*recommend_system
            [it.first],*recommend_system[movie]);
        similarity_map[it.first] = similarity;
      }
    if ((int) similarity_map.size() < k)
      {
        return similarity_map;
      }
    while ((int) similarity_map.size() > k)
      {
        auto cur_min = std::min_element(similarity_map.begin()
            , similarity_map.end(),ComparePair());
        similarity_map.erase (cur_min);
      }
    return similarity_map;
  }

/**
 * For full Documentation of methods check the header file
 */
sp_movie RecommenderSystem:: add_movie (const string &name, int year
                                        , const vector<double> &features)
  {
    auto sp_movie_info = make_shared<Movie> (name, year);
    auto sp_features_info =
        make_shared<vector<double>> (features);
    recommend_system[sp_movie_info] = sp_features_info;
    pair<string, int> movie_details;
    movie_details.first = name;
    movie_details.second = year;
    return sp_movie_info;
  }

/**
 * For full Documentation of methods check the header file
 */
sp_movie RecommenderSystem:: recommend_by_cf (const RSUser &user, int k)
  {
    double max = ZERO;
    sp_movie result_movie;
    for (const auto& it : recommend_system)
      {
        if (user.get_ranks()->find (it.first) == user.get_ranks()->end())
          {
            double similarity = predict_movie_score (user, it.first, k);
            if (similarity > max)
              {
                max = similarity;
                result_movie = it.first;
              }
          }
      }
    return result_movie;
  }

/**
 * For full Documentation of methods check the header file
 */
double RecommenderSystem:: predict_movie_score
(const RSUser &user, const sp_movie &movie,int k)
  {
    auto similarity_map = find_k_similar (user, movie,k);
    double sum1 = ZERO, sum2 = ZERO;
    for (const auto& it : similarity_map)
      {
        sum1 += it.second * user.get_ranks()->operator[] (it.first);
        sum2 += it.second;
      }
    return (double) sum1/sum2;
  }

/**
 * For full Documentation of methods check the header file
 */
sp_movie RecommenderSystem:: get_movie(const std::string &name, int year)
  {
    for (auto& it : recommend_system)
      {
        if ((it.first->get_name() == name) && (it.first->get_year() == year))
          {
            return it.first;
          }
      }
    return shared_ptr<Movie>(nullptr);
  }

/**
 * For full Documentation of methods check the header file
 */
std::ostream& operator<<(std::ostream& os,
    const unique_ptr<RecommenderSystem>& rs)
{
  for (const auto &it: rs->recommend_system)
    {
      std::cout << *it.first;
    }
  return os;
}

/**
 * For full Documentation of methods check the header file
 */
std::ostream& operator<<(std::ostream& os,
    const shared_ptr<RecommenderSystem>& rs)
  {
    for (const auto& it: rs->recommend_system)
      {
        std::cout << *it.first;
      }
    return os;
  }