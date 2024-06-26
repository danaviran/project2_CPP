
#ifndef INC_22B_C_C__EX5_MOVIE_H
#define INC_22B_C_C__EX5_MOVIE_H

#include <iostream>
#include <vector>
#include <memory>

#define HASH_START 17
using std::shared_ptr;
using std::string;
using std::vector;
using std::pair;

class Movie;

//typedefs
typedef shared_ptr<const Movie> sp_movie;
typedef std::size_t (*hash_func)(const sp_movie& movie);
typedef bool (*equal_func)(const sp_movie& m1,const sp_movie& m2);
std::size_t sp_movie_hash(const sp_movie& movie);
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2);

class Movie
{
  const string _name;
  const int _year;

 public:
    /**
     * constructor
     * @param name: name of movie
     * @param year: year it was made
     */
    Movie(const string& name, int year):_name(name), _year(year){}

    /**
     * returns the name of the movie
     * @return const ref to name of movie
     */
    std::string get_name() const {return _name;}

    /**
     * returns the year the movie was made
     * @return year movie was made
     */
    int get_year() const {return _year;}

	/**
     * operator< for two movies
     * @param rhs: right hand side
     * @param lhs: left hand side
     * @return returns true if (lhs.year) < rhs.year or (rhs.year == lhs.year
     * & lhs.name < rhs.name) else return false
     */
    friend bool operator<(const Movie& lhs_movie, const Movie& rhs_movie);

    /**
     * operator<< for movie
     * @param os ostream to output info with
     * @param movie movie to output
     */
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
};


#endif //INC_22B_C_C__EX5_MOVIE_H
