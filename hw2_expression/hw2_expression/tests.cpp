//
//  tests.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include "catch.h"
#include "expr.hpp"

TEST_CASE("Equals") {
    SECTION("Num") {
        Num num1(1);
        Num num2(2);
        Num num3(1);
        CHECK_FALSE(num1.equals(&num2));
        CHECK_FALSE(num2.equals(&num1));
        CHECK(num1.equals(&num3));
        CHECK(num3.equals(&num1));
        CHECK_FALSE(num2.equals(&num3));
        CHECK_FALSE(num3.equals(&num2));
    }
    
    SECTION("Add_simple") {
        Add add1(new Num(1), new Num(2));
        Add add2(new Num(2), new Num(1));
        Add add3(new Num(1), new Num(2));
        CHECK_FALSE(add1.equals(&add2));
        CHECK_FALSE(add2.equals(&add1));
        CHECK(add1.equals(&add3));
        CHECK(add3.equals(&add1));
    }
    
    SECTION("Add_nested") {
        Add add1(new Add(new Num(1), new Num(2)), new Add(new Num(3), new Num(4)));
        Add add2(new Add(new Num(3), new Num(4)), new Add(new Num(1), new Num(2)));
        Add add3(new Add(new Num(1), new Num(2)), new Add(new Num(3), new Num(4)));
        CHECK_FALSE(add1.equals(&add2));
        CHECK_FALSE(add2.equals(&add1));
        CHECK(add1.equals(&add3));
        CHECK(add3.equals(&add1));
    }

    SECTION("Mult_simple") {
        Mult mult1(new Num(1), new Num(2));
        Mult mult2(new Num(2), new Num(1));
        Mult mult3(new Num(1), new Num(2));
        CHECK_FALSE(mult1.equals(&mult2));
        CHECK_FALSE(mult2.equals(&mult1));
        CHECK(mult1.equals(&mult3));
        CHECK(mult3.equals(&mult1));
    }
    
    SECTION("Mult_nested") {
        Mult mult1(new Add(new Num(1), new Num(2)), new Add(new Num(3), new Num(4)));
        Mult mult2(new Add(new Num(3), new Num(4)), new Add(new Num(1), new Num(2)));
        Mult mult3(new Add(new Num(1), new Num(2)), new Add(new Num(3), new Num(4)));
        CHECK_FALSE(mult1.equals(&mult2));
        CHECK_FALSE(mult2.equals(&mult1));
        CHECK(mult1.equals(&mult3));
        CHECK(mult3.equals(&mult1));
    }

    SECTION("Variable") {
        Variable var1("a");
        Variable var2("b");
        Variable var3("a");
        CHECK_FALSE(var1.equals(&var2));
        CHECK(var1.equals(&var3));
    }
};
