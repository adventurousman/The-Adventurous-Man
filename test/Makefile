CXXTEST_HOME = cxxtest-4.3
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

.PHONY: all clean

all: runner

gameTestSuite.cpp: gameTestSuite.h
	$(CXXTEST_GEN) --error-printer $< -o $@

runner: gameTestSuite.cpp *.h ../CApp.h ../CPlayer.h ../CEnemy.h ../BaseUtil.h ../CEnemy.h ../AttackBullet.h
	g++ $< -I$(CXXTEST_INCLUDE) -o $@

clean:
	rm -f runner gameTestSuite.cpp
