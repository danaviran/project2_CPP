//
// Created by dspec on 06/09/2022.
//

#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"
#include <vector>
#include "Movie.h"
#include <sstream>

#define PASSED std::cout << "\033[1;32mPASS\033[0m\n"; return 1;
#define FAILED std::cout << "\033[1;31mFAIL\033[0m\n"; return 0;
#define END_MESSAGE std::cout << "passed " << passed << " tests out of " << \
total << std::endl; return {passed, total};

typedef std::pair<int, int> (*test_func)();
typedef std::vector<test_func> test_func_vector;

typedef int (*func)();
typedef std::vector<func> func_vector;

/**
 * MOVIE
 */
int test_print()
{
    std::cout << "testing << operator: ";
    std::string test_name = "test_movie_name";
    int test_year = 1111;
    std::string expected_output = test_name + " (" + std::to_string
            (test_year) + ")\n";
    Movie test_movie(test_name, test_year);
    std::ostringstream output;
    output << test_movie;
    std::cout << expected_output << std::endl;
    if(output.str() == expected_output)
    {PASSED}
    else
    {FAILED}
}

int test_comparator()
{
    std::cout << "testing < operator: ";
    Movie a("Z", 1990), b("A", 1995), c("B", 1995);
    if(a < b && b < c && a < c)
    {PASSED}
    else
    {FAILED}
}

int test_get_movie_name()
{
    std::cout << "testing get_name: ";
    std::string test_string = "Test_string";
    Movie a(test_string, 1999);
    if(a.get_name() == test_string)
    {PASSED}
    else
    {FAILED}
}

int test_get_year()
{
    std::cout << "testing get_year: ";
    int test_year = 1457;
    Movie a("Whatever", test_year);
    if(a.get_year() == test_year)
    {PASSED}
    else
    {FAILED}
}

func_vector movie_funcs = {test_print, test_comparator, test_get_movie_name, test_get_year};

std::pair<int, int> tests_movie()
{
    std::cout << "***TESTING Movie***" << std::endl;
    int passed = 0, total = 0;
    for(auto f : movie_funcs)
    {
        passed += f();
        total++;
    }
    END_MESSAGE
}

/**
 * RSUser
 */
int test_get_username()
{
    std::cout << "testing get_name: ";
    std::string test_name = "test_name";
    auto null_rs = make_shared<RecommenderSystem>();
    auto sp_rank_map = make_shared<rank_map>();
    auto a = RSUser(test_name, sp_rank_map, null_rs);
    if(a.get_name() == test_name)
    {PASSED}
    else
    {FAILED}
}

int test_recommend_by_content()
{
    std::cout << "\033[1;33mNOTE!\033[0m THE FOLLOWING TEST DOES NOT CHECK IF "
                 "THE OUTPUT IS "
                 "CORRECT.\n";
    std::cout << "Checking that get_recommendations_by_content returns a "
                 "value: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
    try
    {
        auto output = users[0].get_recommendation_by_content();
        if(output == nullptr)
        {FAILED}
    }
    catch(std::exception&)
    {FAILED}
    PASSED
}

int test_recommend_by_cf()
{
    std::cout << "\033[1;33mNOTE!\033[0m THE FOLLOWING TEST DOES NOT CHECK "
                 "IF THE OUTPUT IS "
                 "CORRECT.\n";
    std::cout << "Checking that get_recommendations_by_cf returns a "
                 "value: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
    try
    {
        auto output = users[0].get_recommendation_by_cf(2);
        if(output == nullptr)
        {FAILED}
    }
    catch(std::exception&)
    {FAILED}
    PASSED
}

int test_add_movie()
{
    std::cout << "Testing add_movie_to_rs (added to rs): ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
//    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt", rs);
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",
                                                       std::move(rs));
    std::vector<double> test_features = {1, 1, 1, 1};
    std::string test_movie_name = "test";
    int test_movie_year = 1111;
    users[0].add_movie_to_rs(test_movie_name, test_movie_year, test_features, 1);
//    auto new_movie = rs->get_movie(test_movie_name, test_movie_year);
//    if(new_movie->get_name() == test_movie_name &&
//                                    new_movie->get_year() == test_movie_year)
//    {PASSED}
//    else
//    {FAILED}
    /**
     * The following chunk of code tries to predict a score for the movie we
     * just entered, presumably if it's not in rs some form of exception
     * would be raised.
     * You can also try commenting-out the code below an un-comment-ing the
     * code above for a direct test.
     * HOWEVER in that test I do not move 'rs' when creating the users, so
     * if your RecommenderSystemLoader returns a unique pointer, you would
     * get a false positive.
     */
    try {users[0].get_prediction_score_for_movie(test_movie_name,
                                                 test_movie_year, 2);}
    catch(std::exception&)
    {FAILED}
    PASSED
}

int test_add_movie_ranking()
{
    std::cout << "Testing add_movie_to_rs (added to this user's ranking): ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
    std::vector<double> test_features = {1, 1, 1, 1};
    std::string test_movie_name = "test";
    int test_movie_year = 1111;
    users[0].add_movie_to_rs(test_movie_name, test_movie_year, test_features, 1);
//    auto new_movie = rs->get_movie(test_movie_name, test_movie_year);
//    auto ranks0 = users[0].get_ranks();
//    auto iter = ranks0.find(new_movie);
//    if(iter != ranks0.end())
//    {PASSED}
//    FAILED
    auto ranks = users[0].get_ranks();
    for(const auto& entry : *ranks)
    {
        if(entry.first->get_name() == test_movie_name &&
            entry.first->get_year() == test_movie_year)
        {PASSED}
    }
    FAILED
}

int test_add_movie_multiple_users()
{
    std::cout << "Checking if add_movie_to_rs modified rs for other users: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
    std::vector<double> test_features = {1, 1, 1, 1};
    std::string test_movie_name = "test";
    int test_movie_year = 1111;
    users[0].add_movie_to_rs(test_movie_name, test_movie_year, test_features, 1);
    //I will try to get a prediction score for this movie from another user,
    //presumably, if the movie didn't appear in the other user's rs, the
    // attempt to predict it's score would result in an exception somewhere.
    try {users[1].get_prediction_score_for_movie(test_movie_name,
                                                 test_movie_year, 2);}
    catch(std::exception&)
    {FAILED}
    PASSED
}

int test_get_ranks()
{
    std::cout << "Testing get_ranks: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
    try {auto ranks = users[0].get_ranks();}
    catch (std::exception&)
    {FAILED}
    PASSED
}

int test_bad_input()
{
    std::cout << "Checking if RSUsersLoader throws an exception if its "
                 "feature values are out of bounds: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    try {
        auto users = RSUsersLoader::create_users_from_file
                ("RSUsersLoader_bad_input.txt", std::move(rs));
    }
    catch(std::exception&)
    {PASSED}
    FAILED
}

func_vector user_funcs = {test_get_username, test_get_ranks,
                          test_recommend_by_content,
                          test_recommend_by_cf, test_add_movie,
                          test_add_movie_ranking,
                          test_add_movie_multiple_users, test_bad_input};

std::pair<int, int> tests_RSUser()
{
    std::cout << "***TESTING RSUser***" << std::endl;
    int passed = 0, total = 0;
    for(auto f : user_funcs)
    {
        passed += f();
        total++;
    }
    END_MESSAGE
}

/**
 * RecommenderSystem
 */
int RecommenderSystem_print()
{
    std::cout << "testing RecommenderSystem's << operator: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    std::string buffer_rs, buffer_expected_output;
    std::stringstream s;
    s << rs;
    std::ifstream file;
    file.open("print_main_out_test.txt");
    while(getline(s, buffer_rs))
    {
        getline(file, buffer_expected_output);
        buffer_expected_output = buffer_expected_output.substr(0,
                                                               buffer_expected_output.size()-1);
        if(buffer_rs != buffer_expected_output)
        {
            file.close();
            FAILED
        }
    }
    file.close();
    PASSED
}

int RecommenderSystem_bad_input()
{
    std::cout << "Checking if RecommenderSystem throws an exception if its "
                 "feature values are out of bounds: ";
    try {
        auto rs = RecommenderSystemLoader::create_rs_from_movies_file
                ("RecommenderSystemLoader_bad_input.txt");
    }
    catch(std::exception&)
    {PASSED}
    FAILED
}

/**
 * WARNING! I calculate the expected result for this test myself, by hand
 * and with no confirmation.
 * therefor IT IS VERY LIKELY THIS TEST IS WRONG! I am BAD AT MATH.
 * Feel free to comment-out this test if you doubt it.
 */
int test_predict_movie_score()
{
    std::cout << "\033[1;33mWARNING!\033[0m I calculated the expected result "
                 "by myself, it's "
                 "possible the following test is wrong.\n";
    std::cout << "Testing predict_movie_score: ";
    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
    rank_map sofias_map(0, sp_movie_hash, sp_movie_equal);
    sofias_map[rs->get_movie("Twilight", 2008)] = 4;
    sofias_map[rs->get_movie("ForestGump", 1994)] = 8;
    auto test_movie = rs->get_movie("Titanic", 1997);
    //Over here I'm assuming RSUser's constructor receives a shared pointer,
    // if this isn't true in your project this will result in a false
    // positive, so feel free to change it to make sense (or comment-out this
    // test entirely)
    auto sp_sofias_map = make_shared<rank_map>(sofias_map);
    std::shared_ptr<RecommenderSystem> shared_rs = std::move(rs);
    std::string name = "sofia";
    RSUser Sofia(name, sp_sofias_map, shared_rs);
    double result = shared_rs->predict_movie_score(Sofia, test_movie, 2);
    double expected_result = 5.892423222;
    double offset = 0.000001;
    if(result > expected_result-offset && result < expected_result+offset)
    {PASSED}
    else
    {FAILED}

}

func_vector rec_funcs = {RecommenderSystem_print,
                         RecommenderSystem_bad_input,
                         test_predict_movie_score};

std::pair<int,int> tests_RecommenderSystem()
{
    std::cout << "***TESTING RecommenderSystem***" <<std::endl;
    int passed = 0, total = 0;
    for(auto f : rec_funcs)
    {
        passed += f();
        total++;
    }
    END_MESSAGE
}

/**
 * MAIN
 */
test_func_vector tests = {tests_movie,tests_RecommenderSystem, tests_RSUser};

int main()
{
    int passed = 0, total = 0;
    for(auto test : tests)
    {
        std::pair<int, int> results = test();
        passed += results.first;
        total += results.second;
        std::cout << std::endl;
    }
    std::cout << "Passed " << passed << " tests out of a total of " << total
    <<std::endl;
    if(passed == total)
    {
        std::cout << "*********************************" << std::endl;
        std::cout << "***PASSED ALL TESTS, GOOD JOB!***" << std::endl;
        std::cout << "*********************************" << std::endl;
    }
    return passed != total; ///return 0 if all passed, 1 otherwise.
}