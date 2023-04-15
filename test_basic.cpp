#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"

#include <iostream>
#include <vector>

int main(){
  // check movie
  Movie m1("Twilight", 2008);
  Movie m2("Wanted", 2008);
  bool need_true = (m1 < m2);
  std::cout << "check operator<: " << need_true << std::endl;
  Movie m3("Titanic", 1997);
  bool need_false = (m1 < m3);
  std::cout << "check operator<: " << need_false << std::endl;
  std::cout << "movies: " << std::endl;
  std::cout << m1;
  std::cout << m2;
  std::cout << m3;

//  // check rs and rsuser
  auto rs = RecommenderSystemLoader::create_rs_from_movies_file ("presubmit.in_m");
  std::vector<double> spiderman_vec = {1, 2, 3, 4};
  (*rs).add_movie("Spiderman", 2022, spiderman_vec);
  std::cout << "\nrs system: " << std::endl;
  std::cout << rs << std::endl;

  // check features vec
  // need to add as friend so work
  for (const auto& p : (*rs).recommend_system) // temp need to add main as friend for RecommenderSystem
  {
      std::cout << (*p.first) << ": ";
      for (const auto& d : *p.second)
      {
          std::cout << d << " ";
      }
      std::cout << std::endl;
  }

  std::cout << "\nget spiderman: " << std::endl;
  sp_movie sp_m1 = (*rs).get_movie("Spiderman", 2022);
  std::cout << *sp_m1 << std::endl;
  //sp_movie sp_m2 = (*rs).get_movie("Spiderman", 2021);



    // check rec bt cont
    auto rs2 = RecommenderSystemLoader::create_rs_from_movies_file ("presubmit.in_m");
    std::cout << "check 1: " << rs2->recommend_system.size() << "\n";
    for (auto& it : rs2->recommend_system)
    {
      std::cout << "check 2: " << *it.first << "\n";
    }
    std::vector<RSUser> users = RSUsersLoader::create_users_from_file("presubmit.in_u",std::move(rs2));

    // check RSUser
    std::cout << users.size() << std::endl;
    std::cout << "\nprint from RSUser: " << std::endl;
    for(auto& cur :users)
      {
        std::cout<<cur.get_name()<<std::endl;
        for(const auto& rank :*cur.get_ranks())
          {
            std::cout<<rank.first->get_name()<<" ("<<rank.second<<") ";
          }
        std::cout<<std::endl;
      }
    std::cout<< "NEW" << std::endl;
    std::cout<< users[0].get_ranks()->size() << std::endl;
    auto sp_rs = users[0].get_ranks();
    std::cout << sp_rs->size() << std::endl;
    auto sp_rs1 = users[1].get_ranks();
    std::cout << sp_rs1->size() << std::endl;
    auto sp_rs2 = users[2].get_ranks();
    std::cout << sp_rs2->size() << std::endl;
    auto sp_rs3 = users[3].get_ranks();
    std::cout << sp_rs3->size() << std::endl;



    sp_movie m5 = users[3].get_recommendation_by_content();
    std::cout<< "M5: " << *m5 << std::endl;


    double predict3 = users[2].get_prediction_score_for_movie("Titanic", 1997, 2);
    std::cout<< "p3 " << predict3 << std::endl;
}