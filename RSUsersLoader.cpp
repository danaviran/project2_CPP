#include <algorithm>
#include "RSUsersLoader.h"

#define LENGTH_ERROR "Error: length/width of given matrix is not valid.\n"
#define FILE_ERROR "Error: error in file.\n"
#define MIN_FEATURE 0
#define MAX_FEATURE 11
#define MOVIE_FORMAT '-'
#define SPACE ' '
#define INIT_UNORDERED 10
using std::all_of;

std::vector<RSUser> RSUsersLoader:: create_users_from_file
(const std::string& users_file_path, unique_ptr<RecommenderSystem> rs)
noexcept(false) {
  std::ifstream is; // Initialization
  shared_ptr<RecommenderSystem> sp_rs = std::move(rs);
  auto movies_by_index = map<int,sp_movie>();
  auto user_vec = vector<RSUser>();
  is.open(users_file_path,std::ios::in);
  if (!is.is_open() || !is.good()) {
      throw std::invalid_argument(FILE_ERROR); }
  string first_line;  // Process First Line
  getline (is, first_line);
  int counter = 0;
  std::stringstream s_stream(first_line);
  while (s_stream.operator bool()) {
      string movie, s_year;
      getline (s_stream, movie, MOVIE_FORMAT);
      getline (s_stream, s_year, SPACE);
      if (movie.empty() || s_year.empty()) {
          break; }
      int year = std::stoi(s_year);
      auto sp_mov = sp_rs->get_movie (movie,year);
      movies_by_index[counter] = sp_mov;
      counter++; }
  while ((is.good() && !is.eof())) { // Process Next Lines
      string cur_line;
      getline (is, cur_line);
      if (!cur_line.empty()) {
          rank_map user_rm = rank_map (INIT_UNORDERED, sp_movie_hash,
                                       sp_movie_equal);
          int counter2=0, cur_num;
          string username, n_str;
          std::stringstream s_stream(cur_line);
          getline (s_stream, username, SPACE);
          while (s_stream.good() && !(s_stream.eof())) {
              getline (s_stream, n_str, SPACE);
              if (all_of(n_str.begin(), n_str.end(),::isdigit)){
                  cur_num = std::stoi (n_str);
                  if (MIN_FEATURE >= cur_num || cur_num >= MAX_FEATURE){
                      throw std::length_error (LENGTH_ERROR); }
                  auto cur_sp_m=movies_by_index[counter2];
                  user_rm[cur_sp_m] = cur_num; }
              counter2++; }
          auto sp_rank_map = make_shared<rank_map>(user_rm);
          auto cur_user = RSUser(username,sp_rank_map,
                                 sp_rs);
          user_vec.push_back (cur_user); } }
  is.close();
  return user_vec;
}