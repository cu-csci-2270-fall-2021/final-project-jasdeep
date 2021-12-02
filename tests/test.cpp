// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_insert(commits, len, tabSize);
    
    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    
    len = 1;
    
    string commits1[] = {"computer"};
    tabSize = 5;
    
    result = test_insert(commits1, len, tabSize);
    
    expected = "0|| \n1|| \n2|| \n3|| \n4|| computer(0,)\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    len = 0;
    
    string commits2[] = {};
    tabSize = 5;
    
    result = test_insert(commits2, len, tabSize);
    
    expected = "0|| \n1|| \n2|| \n3|| \n4|| \n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    len = 10;
    string commits3[] = {"computer", "fun", "science", "test", "initial", "test", "ten", "fun", "test", "difficult"};
    tabSize = 3;
    
    result = test_insert(commits3, len, tabSize);
    
    expected = "0|| difficult(9,)-->ten(6,)-->computer(0,)\n1|| test(3,5,8,)-->science(2,)\n2|| initial(4,)-->fun(1,7,)\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(20);
}

//TODO add more tests for insert. Design tests for search from hashTable.

TEST_F(test_x, TestSearch){
    
    
    string result;
    string expected;
       
    int len = 9;
    string key = "science";
    
    string commits[] = {"computer", "science", "fun", "difficult", "science", "difficult", "fun", "twenty", "science"};
    int tabSize = 5;
    
    result = test_search(commits, len, tabSize, key);
    
    expected = "1\n4\n8\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(20);
    
    
    len = 5;
    key = "fun";
    
    string commits1[] = {"computer", "science", "fun", "difficult", "science"};
    tabSize = 3;
    
    result = test_search(commits1, len, tabSize, key);
    
    expected = "2\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    
    
    len = 2;
    key = "computer";
    
    string commits2[] = {"computer", "science"};
    tabSize = 3;
    
    result = test_search(commits2, len, tabSize, key);
    
    expected = "0\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    len = 0;
    key = "computer";
    
    string commits3[] = {};
    tabSize = 3;
    
    result = test_search(commits3, len, tabSize, key);
    
    expected = "";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
}