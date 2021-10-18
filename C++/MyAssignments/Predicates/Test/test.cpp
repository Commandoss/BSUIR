#define BOOST_TEST_MODULE Test
#include <boost/test/included/unit_test.hpp>

#include <string.h>
#include <fstream>

#include "predicates.h"
#include "filesys.h"

const string path1 = "files/testfile.txt";
const string newPath1 = "files/newTestName.txt";

const string testText = "Checkin";

const string predicate = "A22UUUidfsdfAAAA";
const string reversPredicate = "unnuuulllllluuuu";

BOOST_AUTO_TEST_SUITE(test_filesys)

BOOST_AUTO_TEST_CASE(fn_check_path) {
    BOOST_REQUIRE(check_path("Files/file.txt"));
    BOOST_REQUIRE(check_path("Header/filesys.h"));
    BOOST_REQUIRE(check_path("Source/main.cpp"));
}

BOOST_AUTO_TEST_CASE(fn_create_file) {
    create_file(path1);
    BOOST_REQUIRE(check_path(path1));
}

BOOST_AUTO_TEST_CASE(fn_write_and_read_file) {
    auto fion = create_file(path1);
    write_file(fion, testText);
    close_file(fion);
    
    fion = open_file(path1);
    string buffer = read_file(fion);
    close_file(fion);
    
    cout << buffer << endl;
    cout << testText << endl;
    BOOST_REQUIRE(buffer == testText);
}

BOOST_AUTO_TEST_CASE(fn_rename_file) {
    BOOST_REQUIRE(rename_file(path1, newPath1));
}


BOOST_AUTO_TEST_CASE(fn_remove_file) {
    BOOST_REQUIRE(remove_file(newPath1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_predicate)

BOOST_AUTO_TEST_CASE(fn_get_predicate) {
    string line = get_transformed_predicate(predicate);
    BOOST_REQUIRE(reversPredicate == line);
}

BOOST_AUTO_TEST_SUITE_END()
