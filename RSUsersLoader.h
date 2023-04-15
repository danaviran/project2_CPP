#ifndef SCHOOL_SOLUTION_USERFACTORY_H
#define SCHOOL_SOLUTION_USERFACTORY_H

#include "RecommenderSystem.h"
#include <istream>
#include <fstream>
#include <string>
#include <sstream>

typedef std::unordered_map<sp_movie, double, hash_func,equal_func> rank_map;

class RSUsersLoader
{
public:
    RSUsersLoader() = delete;
    /**
     * loads users by the given format with their movie's ranks
     * @param users_file_path path to file of the users and their movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file
    (const std::string& users_file_path, unique_ptr<RecommenderSystem> rs)
    noexcept(false);
};


#endif //SCHOOL_SOLUTION_USERFACTORY_H
