#ifndef GIT_USER_H
#define GIT_USER_H

// Includes
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include "Movie.h"
class RecommenderSystem;

// Typedefs
typedef std::unordered_map<sp_movie, double, hash_func,equal_func> rank_map;
typedef std::shared_ptr<RecommenderSystem> sp_recommendation_system;

/**
 * A user of Recommendation System
 */
class RSUser
{
  string _username;
  shared_ptr<rank_map> _user_rank_map;
  sp_recommendation_system _recommendation_system;

public:
    /**
     * Constructor
     * @param username string reference
     * @param user_rank_db shared_ptr to rank_map of user
     * @param recommendation_system shared_ptr to RecommendationSystem
     */
	RSUser(string& username, shared_ptr<rank_map> user_rank_db,
           sp_recommendation_system recommendation_system)
    : _username(username), _user_rank_map(std::move(user_rank_db)),
    _recommendation_system(std::move(recommendation_system))
    {
    }

	/**
	 * Getter for the user's name
	 * @return the username
	 */
    string get_name() {return _username;}

	/**
	 * Function for adding a movie to the DB
	 * @param name name of movie
     * @param year year it was made
	 * @param features a vector of the movie's features
	 * @param rate the user rate for this movie
	 */
	void add_movie_to_rs(const string& name, int year,const vector<double>
	    &features, double rate);

    /**
     * Getter for the ranks map
     * @return
     */
    shared_ptr<rank_map> get_ranks() const
    {
      return _user_rank_map;
    }

	/**
	 * Returns a recommendation according to the movie's content
	 * @return recommendation
	 */
	sp_movie get_recommendation_by_content() const;

	/**
	 * Returns recommendation according to the similarity recommendation method
	 * @param k the number of the most similar movies to calculate by
	 * @return recommendation
	 */
    sp_movie get_recommendation_by_cf(int k) const;

	/**
	 * Predicts the score for a given movie
	 * @param name the name of the movie
	 * @param year the year the movie was created
	 * @param k the parameter which represents the number of the most similar
	 * movies to predict the score by
	 * @return predicted score for the given movie
	 */
	double get_prediction_score_for_movie(const std::string& name, int year,
                                          int k) const;

	/**
	 * Output stream operator
	 * @param os the output stream
	 * @param user the user
	 * @return output stream
	 */
	friend std::ostream& operator<<(std::ostream& os, const RSUser& user);
};

#endif //GIT_USER_H
