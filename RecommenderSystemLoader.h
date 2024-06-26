#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H

#include "RecommenderSystem.h"
#include <fstream>
#include <sstream>

class RecommenderSystemLoader {
 public:
  RecommenderSystemLoader () = delete;

  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommenderSystem which was created with
   * those movies
   */
  static unique_ptr<RecommenderSystem> create_rs_from_movies_file
	  (const string &movies_file_path) noexcept (false);
};

#endif //RECOMMENDERSYSTEMLOADER_H
