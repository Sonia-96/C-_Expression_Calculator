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
        NumExpr num1(1);
        NumExpr num2(2);
        NumExpr num3(1);
        NumExpr num4(-1);
        CHECK_FALSE(num1.equals(&num2));
        CHECK_FALSE(num2.equals(&num1));
        CHECK(num1.equals(&num3));
        CHECK(num3.equals(&num1));
        CHECK_FALSE(num2.equals(&num3));
        CHECK_FALSE(num3.equals(&num2));
        CHECK(!num1.equals(&num4));
    }
    
    SECTION("Add_simple") {
        AddExpr add1(new NumExpr(1), new NumExpr(2));
        AddExpr add2(new NumExpr(2), new NumExpr(1));
        AddExpr add3(new NumExpr(1), new NumExpr(2));
        CHECK_FALSE(add1.equals(&add2));
        CHECK_FALSE(add2.equals(&add1));
        CHECK(add1.equals(&add3));
        CHECK(add3.equals(&add1));
        CHECK(!add2.equals(&add3));
        CHECK(!add3.equals(&add2));
    }
    
    SECTION("Add_nested") {
        AddExpr add1(new AddExpr(new NumExpr(1), new NumExpr(2)), new MultExpr(new NumExpr(3), new NumExpr(4)));
        AddExpr add2(new MultExpr(new NumExpr(3), new NumExpr(4)), new AddExpr(new NumExpr(1), new NumExpr(2)));
        AddExpr add3(new AddExpr(new NumExpr(1), new NumExpr(2)), new MultExpr(new NumExpr(3), new NumExpr(4)));
        CHECK_FALSE(add1.equals(&add2));
        CHECK_FALSE(add2.equals(&add1));
        CHECK(add1.equals(&add3));
        CHECK(add3.equals(&add1));
        CHECK(!add2.equals(&add3));
        CHECK(!add3.equals(&add2));
    }

    SECTION("Mult_simple") {
        MultExpr mult1(new NumExpr(1), new NumExpr(2));
        MultExpr mult2(new NumExpr(2), new NumExpr(1));
        MultExpr mult3(new NumExpr(1), new NumExpr(2));
        CHECK_FALSE(mult1.equals(&mult2));
        CHECK_FALSE(mult2.equals(&mult1));
        CHECK(mult1.equals(&mult3));
        CHECK(mult3.equals(&mult1));
        CHECK(!mult2.equals(&mult3));
        CHECK(!mult3.equals(&mult2));
    }
    
    SECTION("Mult_nested") {
        MultExpr mult1(new AddExpr(new NumExpr(1), new NumExpr(2)), new MultExpr(new NumExpr(3), new NumExpr(4)));
        MultExpr mult2(new MultExpr(new NumExpr(3), new NumExpr(4)), new AddExpr(new NumExpr(1), new NumExpr(2)));
        MultExpr mult3(new AddExpr(new NumExpr(1), new NumExpr(2)), new MultExpr(new NumExpr(3), new NumExpr(4)));
        CHECK_FALSE(mult1.equals(&mult2));
        CHECK_FALSE(mult2.equals(&mult1));
        CHECK(mult1.equals(&mult3));
        CHECK(mult3.equals(&mult1));
        CHECK(!mult2.equals(&mult3));
        CHECK(!mult3.equals(&mult2));
    }

    SECTION("Variable") {
        VarExpr var1("a");
        VarExpr var2("1");
        VarExpr var3("a");
        CHECK_FALSE(var1.equals(&var2));
        CHECK(var1.equals(&var3));
        CHECK(!var2.equals(&var3));
    }
};

TEST_CASE("Interp") {
    SECTION("Num") {
        CHECK((new NumExpr(0)) -> interp() == 0);
        CHECK((new NumExpr(-100))-> interp() == -100);
    }
    
    SECTION("Add_simple") {
        
    }
    
    SECTION("Add_nested") {
        
    }
    
    SECTION("Mult_simple") {
        MultExpr mult1(new NumExpr(3), new NumExpr(2));
        CHECK(mult1.interp() == 6);
    }
    
    SECTION("Mult_nested") {
        MultExpr mult1(new AddExpr(2, 3), new MultExpr(4, 5));
        CHECK(mult1.interp() == 100);
    }
    
    SECTION("Variable") {
        VarExpr var1("x");
        CHECK_THROWS_WITH(var1.interp(), "A variable has no value!");
    }
}

TEST_CASE("has_variable") {
    SECTION("Num") {
        
    }
    
    SECTION("Add_simple") {
        
    }
    
    SECTION("Add_nested") {
        
    }
    
    SECTION("Mult_simple") {
        MultExpr mult1(new NumExpr(3), new NumExpr(2));
    }
    
    SECTION("Mult_nested") {
        MultExpr mult1(new AddExpr(2, 3), new MultExpr(4, 5));
    }
    
    SECTION("Variable") {
        
    }
}

TEST_CASE("subst") {
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
           ->subst("x", new VarExpr("y"))
           ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );
    CHECK( (new VarExpr("x"))
           ->subst("x", new AddExpr(new VarExpr("y"),new NumExpr(7)))
           ->equals(new AddExpr(new VarExpr("y"),new NumExpr(7))) );
}
