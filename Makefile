vpath %.cpp zf_common/
vpath %.cpp game/
vpath %.cpp game/seeds
vpath %.cpp game/garden
vpath %.o obj/

BIN=pixelgarden
CXX=g++

SFML=-framework sfml-graphics -framework sfml-window -framework sfml-system
OBJDIR=obj


# search frameworks files for all the cpp files
common = $(shell cd zf_common; ls *.cpp )
commonobjs = $(patsubst %,$(OBJDIR)/%,$(common:.cpp=.o))
game = $(shell cd game; ls *.cpp ; for F in `ls -d */` ; do cd $$F; ls *.cpp ;cd ..; done)
gameobjs = $(patsubst %,$(OBJDIR)/%,$(game:.cpp=.o))



main=obj/main.o

all: $(BIN)



$(BIN) : $(main) $(commonobjs) $(gameobjs)
	$(CXX) -o $(BIN) $(OBJDIR)/* $(SFML)

$(OBJDIR)/%.o : %.cpp
	$(CXX) -c -o $@ $^

obj/main.o : main.cpp 
	$(CXX) -c -o $@ $^

clean:
	rm obj/*.o
	rm $(BIN)

remake:
	make clean
	make all

debug:
	@echo $(world)
.PHONY: clean remake debug
