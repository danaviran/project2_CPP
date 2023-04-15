#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H

// Includes
#include "RSUser.h"

// Using
using std::map;
using std::vector;
using std::make_shared;
using std::make_unique;
using std::unique_ptr;
using std::shared_ptr;

// Typedefs
typedef shared_ptr<const vector<double>> sp_features;

/**
 * RecommenderSystem Class
 */
class RecommenderSystem {

  // Private Members
  map<sp_movie, sp_features> recommend_system;

  // Private Struct

  /**
   * A struct containing a function helper for finding min-element in a map
   */
  struct ComparePair;

  // Private Functions


  void normalize_rank (const RSUser& user, map<sp_movie,double>& user_rank);

  /**
   * Calculates Vector of Preference of a user
   * @param normalized_map map of pairs of shared-pointer to Movie and the
   * normalized rank the user ranked it
   * @return Vector represents the Movie's features preferences of the user
   */
  vector<double> get_preference_vector (map<sp_movie,double>& normalized_map);

  /**
   * Calculates Similarity between two vectors
   * @param pref_vec Vector of Movie's features preferences of the user
   * @param features Vector of Movie's features
   * @return a number representing the similarity
   */
  double calc_similarity (const vector<double> &pref_vec, const vector<double>
      &features) const;

  /**
   * Given an RSUser and a Movie as arguments, the func returns a map of K
   * pairs that represent the K most similar movies to the Movie given.
   * @param user RSUer to recommend to
   * @param movie a Movie the user watched to find similar movies to it
   * @param k The number of the wanted map of most similar movies
   * @return a map of K pairs that represent the K most similar movies to the
   * Movie given, that the user did watch and rank.
   */
  map<sp_movie,double> find_k_similar (const RSUser& user, const sp_movie
  &movie, int k);

  /**
   * Calculate the Norm of a vector of numbers
   * @param vector current vector
   * @return the norm value
   */
  double calculate_norm (const vector<double> &vector) const;

 public:
  /**
   * Constructor
   */
  explicit RecommenderSystem ()
  = default;

  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie (const string &name, int year, const vector<double>
      &features);

  /**
   * Calculates the movie with highest score based on movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const RSUser &user);

  /**
   * Calculates the movie with highest predicted score based
   * on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k number of movies ranked by the user for calculation
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const RSUser &user, int k);

  /**
   * Predict a user rating for a movie given argument using item cf procedure
   * with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:number of movies ranked by the user for calculation
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const RSUser &user, const sp_movie &movie,int k);

  /**
   * Get movie
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie(const std::string &name, int year);

  /**
   * Ostream Operator funcs
   * @param os Ostream object
   * @param rs shared pointer or unique pointer to RecommendSystem
   * @return current Ostream object
   */
  friend std::ostream& operator<<(std::ostream& os,
      const unique_ptr<RecommenderSystem>& rs);
  friend std::ostream& operator<<(std::ostream& os,
      const shared_ptr<RecommenderSystem>& rs);
};


#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
