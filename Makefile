# Lines that start with a # are comments
#
# Here we define variables that we can use later.
# When variables are used we must wrap them with $()
OBJS = Apriori.o
EXENAME = Apriori

CXX = clang++
CXXFLAGS = -Iinclude -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++14 -stdlib=libc++ -lpng -lc++abi

.PHONY: all clean

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXENAME)

Apriori.o : Apriori.cpp
	$(CXX) $(CXXFLAGS) Apriori.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null
