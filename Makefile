
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = clang++
endif

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS =
else
  ifeq ("$(shell uname)", "Linux")
  LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat -lSDL_draw -lSDL_mixer
  endif
endif

OBJS = \
	main.o \
	manager.o \
	gamedata.o \
	spriteFactory.o \
	multiSpriteFactory.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	sprite.o \
	viewport.o \
	multiSprite.o \
	orbs.o \
	world.o \
	frame.o \
	collisionStrategy.o \
        explodingSprite.o\
        sound.o\
        explosion.o \
        bullet.o \
	ioManager.o \
	gui.o 
EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp manager.h spriteFactory.h multiSpriteFactory.h
manager.o: manager.cpp manager.h gamedata.h ioManager.h sprite.h clock.h \
	multiSprite.h spriteFactory.h world.h orbs.h
ioManager.o: ioManager.cpp ioManager.h
sound.o: sound.cpp sound.h
parseXML.o: parseXML.cpp parseXML.h
viewport.o: viewport.cpp viewport.h gamedata.h sprite.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
spriteFactory.o: spriteFactory.cpp spriteFactory.h factory.h frame.h
multiSpriteFactory.o: multiSpriteFactory.cpp multiSpriteFactory.h \
	factory.h frame.h
clock.o: clock.cpp clock.h manager.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h collisionStrategy.h
multiSprite.o: multiSprite.cpp multiSprite.h gamedata.h sprite.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h sprite.h \
	ioManager.h explosion.h
orbs.o: orbs.cpp orbs.h sprite.h gamedata.h viewport.h 
collisionStrategy.o: collisionStrategy.cpp collisionStrategy.h sprite.h
bullet.o: bullet.cpp bullet.h sprite.h
gui.o: gui.h gui.cpp frame.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
