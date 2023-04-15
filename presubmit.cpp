#include "RSUsersLoader.h"
#include "RecommenderSystemLoader.h"
#include <iostream>
#include <string>

#define THRESHOLD 0.01


int main()
{
	int status = 0;
    // check all function for RS exist
    RecommenderSystem rec;
    sp_movie a = rec.add_movie("Batman",2022,{1,2,3,4});
    sp_movie b = rec.add_movie("StarWars",1977,{1,2,3,5});
    sp_movie c = rec.add_movie("ForestGump",1994,{1,2,3,4});

    std::cout << *a;
    std::cout << *b;
    std::cout << *c;

    // check all functions for user and UsersLoader exist and movie
    auto rs1 = RecommenderSystemLoader::create_rs_from_movies_file("presubmit.in_m");
    std::cout << rs1->recommend_system.size() << "\n";

    std::vector<RSUser> users = RSUsersLoader::create_users_from_file( "presubmit.in_u",std::move(rs1));

    std::cout << users.size() << "\n";

	return 0;
}