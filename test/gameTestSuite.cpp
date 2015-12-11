/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MyTestSuite1_init = false;
#include "/home/hoang/Documents/The Adventurous Man/sidescroller/test/gameTestSuite.h"

static MyTestSuite1 suite_MyTestSuite1;

static CxxTest::List Tests_MyTestSuite1 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite1( "gameTestSuite.h", 12, "MyTestSuite1", suite_MyTestSuite1, Tests_MyTestSuite1 );

static class TestDescription_suite_MyTestSuite1_testSimple : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite1_testSimple() : CxxTest::RealTestDescription( Tests_MyTestSuite1, suiteDescription_MyTestSuite1, 15, "testSimple" ) {}
 void runTest() { suite_MyTestSuite1.testSimple(); }
} testDescription_suite_MyTestSuite1_testSimple;

static class TestDescription_suite_MyTestSuite1_testApplication : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite1_testApplication() : CxxTest::RealTestDescription( Tests_MyTestSuite1, suiteDescription_MyTestSuite1, 21, "testApplication" ) {}
 void runTest() { suite_MyTestSuite1.testApplication(); }
} testDescription_suite_MyTestSuite1_testApplication;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
