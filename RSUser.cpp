// don't change those includes
#include <iterator>
#include <algorithm>
#include <cmath>
#include "RSUser.h"
#include "RecommenderSystem.h"

/**
 * For full Documentation of methods check the header file
 */
void RSUser:: add_movie_to_rs(const string& name, int year,const
vector<double> &features, double rate)
{
  if (!std::isnan(rate))
    {
      auto check = _recommendation_system->get_movie (name, year);
      if (check == nullptr)
        {
          _recommendation_system->add_movie (name,year,features);
        }
      (*_user_rank_map)[_recommendation_system->get_movie (name,year)] = rate;
    }
}

/**
 * For full Documentation of methods check the header file
 */
sp_movie RSUser:: get_recommendation_by_content() const
{
  return _recommendation_system->recommend_by_content (*this);
}

/**
 * For full Documentation of methods check the header file
 */
sp_movie RSUser:: get_recommendation_by_cf(int k) const
{
  return _recommendation_system->recommend_by_cf(*this,k);
}

/**
 * For full Documentation of methods check the header file
 */
double RSUser:: get_prediction_score_for_movie(const string& name, int year,
                                               int k) const
{
  auto movie = _recommendation_system->get_movie (name, year);
  return _recommendation_system->predict_movie_score(*this,movie,k);
}

/**
 * For full Documentation of methods check the header file
 */
std::ostream& operator<<(std::ostream& os, const RSUser& user)
{
  std::cout << "name: " << user._username << "\n";
  std::cout << user._recommendation_system;
  return os;
}