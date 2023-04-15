#include "RecommenderSystemLoader.h"

#define LENGTH_ERROR "Error: invalid length.\n"
#define FILE_ERROR "Error: error in file.\n"
#define MIN_FEATURE 0
#define MAX_FEATURE 11
#define MOVIE_FORMAT '-'
#define SPACE ' '

/**
 * For full documentation check header file
 */
unique_ptr<RecommenderSystem> RecommenderSystemLoader::
create_rs_from_movies_file
    (const std::string &movies_file_path) noexcept (false)
{
  RecommenderSystem recommender_system;
  std::ifstream is;
  is.open(movies_file_path,std::ios::in);
  if (!is.is_open() || !is.good())
    {
      throw std::invalid_argument(FILE_ERROR);
    }
 while ((is.good() && !is.eof()))
    {
      string cur_line;
      while (getline (is, cur_line))
        {
          string name, year_string;
          int year;
          double cur_num;
          auto features = vector<double>();
          std::stringstream s_stream(cur_line);
          if (s_stream.good())
            {
              getline (s_stream, name, MOVIE_FORMAT);
              getline (s_stream, year_string, SPACE);
              if (!year_string.empty())
                {
                  year = stoi(year_string);
                }
            }
          while (s_stream.good() && !(s_stream.eof()))
            {
              string cur_num_string;
              getline (s_stream, cur_num_string, SPACE);
              cur_num = std::stod(cur_num_string);
              if (MIN_FEATURE < cur_num && cur_num < MAX_FEATURE)
                {
                  features.push_back (cur_num);
                }
              else
                {
                  throw std::length_error(LENGTH_ERROR);
                }
            }
          recommender_system.add_movie (name, year, features);
        }
    }
  is.close();
  auto up_rs = make_unique<RecommenderSystem>(recommender_system);
  return up_rs;
}
