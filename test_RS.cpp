#include "RecommenderSystem.h"
#include <cassert>
#include <cmath>
using std::make_shared;
using std::pair;
using std::make_pair;
using std::cout;

#define NA NAN

namespace features{
    std::vector<double> Titanic = {7, 2, 9, 1};
    std::vector<double> Twilight = {3,4,6,5};
    std::vector<double> ForestGump = {1,7,7,6};
    std::vector<double> Batman =  {2,6,4,8};
    std::vector<double> StarWars = {3,3,4,9};
}



void test_rec_by_content(){


    rank_map rank_mapp(4, sp_movie_hash, sp_movie_equal);
    std::shared_ptr<RecommenderSystem> rs = make_shared<RecommenderSystem>();
    rs->add_movie( "Titanic", 1997, features::Titanic);
    rs->add_movie("Twilight", 2008, features::Twilight);
    rs->add_movie("ForestGump", 1994, features::ForestGump);
    rs->add_movie("Batman", 2022, features::Batman);
    rs->add_movie("StarWars", 1977, features::StarWars);

    auto rank = make_shared<rank_map>(rank_mapp);
    std::string name = "sofia";
    RSUser me(name, rank, rs);
    me.add_movie_to_rs( "Titanic", 1997, features::Titanic, 4);
    me.add_movie_to_rs("Twilight", 2008, features::Twilight, NA);
    me.add_movie_to_rs("ForestGump", 1994, features::ForestGump, 8);
    me.add_movie_to_rs("Batman", 2022, features::Batman, NA);
    me.add_movie_to_rs("StarWars", 1977, features::StarWars, NA);

    sp_movie res = rs->recommend_by_content(me);
    cout << "\nTEST REC BY CONTENT RESULT: " << (*res) << std::endl; // should print: "Batman (2022)\n"
    assert(res->get_name() == "Batman" && res->get_year() ==  2022);
}

void test_predict(){
    rank_map rank_mapp(4, sp_movie_hash, sp_movie_equal);
    std::shared_ptr<RecommenderSystem> rs = make_shared<RecommenderSystem>();
    rs->add_movie( "Titanic", 1997, features::Titanic);
    rs->add_movie("Twilight", 2008, features::Twilight);
    rs->add_movie("ForestGump", 1994, features::ForestGump);
    rs->add_movie("Batman", 2022, features::Batman);
    rs->add_movie("StarWars", 1977, features::StarWars);
    auto rank = make_shared<rank_map>(rank_mapp);
    std::string name = "Nicole";
    RSUser me(name, rank, rs);
    me.add_movie_to_rs("Titanic", 1997, features::Titanic, NA);
    me.add_movie_to_rs("Twilight", 2008, features::Twilight, NA);
    me.add_movie_to_rs("ForestGump", 1994, {1, 7, 7, 8}, 5);
    me.add_movie_to_rs("Batman", 2022, features::Batman, 2);
    me.add_movie_to_rs("StarWars", 1977, features::StarWars, 6);
    double res  = me.get_prediction_score_for_movie("Titanic", 1997, 2);
    double res1 = me.get_prediction_score_for_movie("Twilight", 2008, 2);
    cout << "TEST PREDICT RESULT: " << res << std::endl;
    cout << "TEST PREDICT RESULT: " << res1 << std::endl;
    assert(res == 5.4823290074185671);
    assert(res1 == 3.5232210003266946);
}

void test_rec_by_cf(){
    rank_map rank_mapp(4, sp_movie_hash, sp_movie_equal);
    std::shared_ptr<RecommenderSystem> rs = make_shared<RecommenderSystem>();
    rs->add_movie( "Titanic", 1997, features::Titanic);
    rs->add_movie("Twilight", 2008, features::Twilight);
    rs->add_movie("ForestGump", 1994, features::ForestGump);
    rs->add_movie("Batman", 2022, features::Batman);
    rs->add_movie("StarWars", 1977, features::StarWars);
    auto rank = make_shared<rank_map>(rank_mapp);
    std::string name = "Nicole";
    RSUser me(name, rank, rs);
    me.add_movie_to_rs("Titanic", 1997, features::Titanic, NA);
    me.add_movie_to_rs("Twilight", 2008, features::Twilight, NA);
    me.add_movie_to_rs("ForestGump", 1994, features::ForestGump, 5);
    me.add_movie_to_rs("Batman", 2022, features::Batman, 2);
    me.add_movie_to_rs("StarWars", 1977, features::StarWars, 6);
    sp_movie res = rs->recommend_by_cf(me, 2);
    cout << "TEST REC BY CF RESULT: "<< (*res) << std::endl;     // should print: "Titanic (1997)\n"
    assert(res->get_name() == "Titanic" && res->get_year() == 1997);
}

int main()
{
    test_rec_by_content();
    test_predict();
    test_rec_by_cf();
}