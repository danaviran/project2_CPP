#include "Movie.h"
#define HASH_START 17
#define RES_MULT 31


/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie& movie){
    std::size_t res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
    return !(*m1 < *m2) && !(*m2 < *m1);
}

/**
 * operator< for two movies
 * @param rhs: right hand side
 * @param lhs: left hand side
 * @return returns true if (lhs.year) < rhs.year or (rhs.year ==
 * lhs.year & lhs.name < rhs.name) else return false
 */
bool operator<(const Movie& lhs_movie, const Movie& rhs_movie)
{
  return (lhs_movie._year < rhs_movie._year || (rhs_movie._year ==
  lhs_movie._year && lhs_movie._name < rhs_movie._name));
}

/**
 *
 * For full Documentation of methods check the header file
 */
std::ostream& operator<<(std::ostream& os, const Movie& movie)
{
  std::cout << movie.get_name() << " (" << movie.get_year() << ")\n";
  return os;
}