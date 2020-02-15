#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"

struct MCC_Test : ::testing::Test{
    MC::MCC *mcc;

    MCC_Test(){
        mcc = new MC::MCC();
    }

    ~MCC_Test(){
        delete(mcc);
    }
};

TEST_F(MCC_Test, InvalidPathException){
    //GIVEN
     const char* input = "";

    //THEN
    EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}

TEST_F(MCC_Test, ValidProgrammParse){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";

    //THEN
    EXPECT_NO_THROW(mcc->parse(input));
}

TEST_F(MCC_Test, InvalidInputStreamException){
    //GIVEN
     const char* input = "";
     std::ifstream ifs;

     //WHEN
     ifs.open (input, std::ifstream::in);

    //THEN
    EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
    ifs.close();
}

TEST_F(MCC_Test, ValidInputStream){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ifstream ifs;

    //WHEN
    ifs.open (input, std::ifstream::in);

    //THEN
    EXPECT_NO_THROW(mcc->parse(input));
    ifs.close();
}

TEST_F(MCC_Test, GetTreeFromInvalidFunction){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    const char *func = "NOTAVALIDFUNCTION";

    //WHEN
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->getAsDot(func), AST_Exception);
}

TEST_F(MCC_Test, GetTreeFromFunctionMain){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    const char *func = "main";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot(func);

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, GetTreeFromWithouthCallingParse){
  //GIVEN
  const char *func = "main";

  //THEN
  EXPECT_THROW(mcc->getAsDot(func), MC::MCC_Exception);
}

TEST_F(MCC_Test, multipleFilesParse){
    //GIVEN
    const char *input = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear.mc";
    const char *input2 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear2.mc";
    const char *input3 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear3.mc";

    //WHEN
    mcc->parse(input);
    mcc->parse(input2);
    mcc->parse(input3);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, binarySearchTest){
    //GIVEN
    const char *input = "../test/integration/binarySearch/binarySearch.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, emptyParse){
    //GIVEN
    const char *input = "../test/integration/empty/empty.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, femParse){
    //GIVEN
    const char *input = "../test/integration/fem/fem.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, fibParse){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, leapYearParse){
    //GIVEN
    const char *input = "../test/integration/leapYear/leapYear.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, leibnizPiParse){
    //GIVEN
    const char *input = "../test/integration/leibnizPi/leibnizPi.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, lucasNumberParse){
    //GIVEN
    const char *input = "../test/integration/lucasNumber/lucasNumber.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, mandelbrotParse){
    //GIVEN
    const char *input = "../test/integration/mandelbrot/mandelbrot.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, numberGuessingParse){
    //GIVEN
    const char *input = "../test/integration/numberGuessing/numberGuessing.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, primeParse){
    //GIVEN
    const char *input = "../test/integration/prime/prime.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, sortingNetworkParse){
    //GIVEN
    const char *input = "../test/integration/sortingNetwork/sortingNetwork.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, subsetSumParse){
    //GIVEN
    const char *input = "../test/integration/subsetSum/subsetSum.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, taylorParse){
    //GIVEN
    const char *input = "../test/integration/taylor/taylor.mc";

    //WHEN
    mcc->parse(input);
    const std::string dot = mcc->getAsDot();

    //THEN
    EXPECT_GT(dot.size(),0ul);
}

TEST_F(MCC_Test, synatxError1Parse){
  //GIVEN
   const char* input = "../test/integration/syntacitcError/1.c";

  //THEN
  EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}

TEST_F(MCC_Test, synatxError2Parse){
  //GIVEN
   const char* input = "../test/integration/syntacitcError/2.c";

  //THEN
  EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}

TEST_F(MCC_Test, synatxError3Parse){
  //GIVEN
   const char* input = "../test/integration/syntacitcError/3.c";

  //THEN
  EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}

TEST_F(MCC_Test, synatxError4Parse){
  //GIVEN
   const char* input = "../test/integration/syntacitcError/4.c";

  //THEN
  EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}

TEST_F(MCC_Test, synatxError5Parse){
  //GIVEN
   const char* input = "../test/integration/syntacitcError/5.c";

  //THEN
  EXPECT_THROW(mcc->parse(input), MC::MCC_Exception);
}
