CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer: randomtestadventurer.c dominion.c rngs.c
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	echo “randomtestadventurer.c” >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -d -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1: randomtestcard1.c dominion.c rngs.c
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	echo “randomtestcard1.c” >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -d -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.c rngs.c
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c $(CFLAGS)
	echo “randomtestcard2.c” >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	gcov -d -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

cardtest1: dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

rununittests: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	echo "cardtest1.c" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "cardtest2.c" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out	

	echo "cardtest3.c" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "cardtest4.c" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest1.c" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest2.c" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest3.c" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest4.c" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -d -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
