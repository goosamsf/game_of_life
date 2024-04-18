CXX = clang++ -Xclang -fopenmp
CXXFLAGS = -g -std=c++11 -Wall -Wextra 

NCURSES_CFLAGS = `pkg-config --cflags ncursesw`
NCURSES_LIBS =  `pkg-config --libs ncursesw`

LIBPATH= -L/opt/homebrew/opt/libomp/lib
IPATH = -I/opt/homebrew/opt/libomp/include 
LDFLAGS = -lomp
CXXFLAGS += $(NCURSES_CFLAGS)
LDFLAGS += $(NCURSES_LIBS)
.PHONY: clean game


game: game.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPATH) $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(IPATH)

clean: 
	@rm *.o


