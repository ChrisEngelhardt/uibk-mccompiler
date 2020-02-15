#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"


struct MCIRTest : ::testing::Test{
    MC::MCC *mcc;

    MCIRTest(){
        mcc = new MC::MCC();
    }

    ~MCIRTest(){
        delete(mcc);
    }
};

TEST_F(MCIRTest, GetCFGBeforeParse){
    //GIVEN
    std::ostringstream os;

    //DURING

    //THEN
    EXPECT_THROW(mcc->getCFG(os), ICR_Exception);
}

TEST_F(MCIRTest, GenerationBeforeSemanticAnalysis){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->generateICR(os), ICR_Exception);
}

TEST_F(MCIRTest, GetCFGBeforeSemanticAnalysis){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->getCFG(os), ICR_Exception);
}

TEST_F(MCIRTest, CFGBeforeGeneration){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);

    //THEN
    EXPECT_THROW(mcc->getCFG(os), ICR_Exception);
}

TEST_F(MCIRTest, ICRGenerationBeforeSemanticAnalysis){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->generateICR(os), ICR_Exception);
}

TEST_F(MCIRTest, multipleFilesIR){
    //GIVEN
    const char *input = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear.mc";
    const char *input2 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear2.mc";
    const char *input3 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear3.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->parse(input2);
    mcc->parse(input3);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, binarySearchIR){
    //GIVEN
    const char *input = "../test/integration/binarySearch/binarySearch.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, emptyIR){
    //GIVEN
    const char *input = "../test/integration/empty/empty.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, femIR){
    //GIVEN
    const char *input = "../test/integration/fem/fem.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, fibIR){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, leapYearIR){
    //GIVEN
    const char *input = "../test/integration/leapYear/leapYear.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, leibnizPiIR){
    //GIVEN
    const char *input = "../test/integration/leibnizPi/leibnizPi.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, mandelbrotIR){
    //GIVEN
    const char *input = "../test/integration/mandelbrot/mandelbrot.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, numberGuessingIR){
    //GIVEN
    const char *input = "../test/integration/numberGuessing/numberGuessing.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, primeIR){
    //GIVEN
    const char *input = "../test/integration/prime/prime.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, sortingNetworkIR){
    //GIVEN
    const char *input = "../test/integration/sortingNetwork/sortingNetwork.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, subsetSumIR){
    //GIVEN
    const char *input = "../test/integration/subsetSum/subsetSum.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCIRTest, taylorIR){
    //GIVEN
    const char *input = "../test/integration/taylor/taylor.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);
    mcc->getICR(os);

    //THEN

    ASSERT_STRCASENE("", os.str().c_str());

    mcc->getCFG(os);

    ASSERT_STRCASENE("", os.str().c_str());
}
