### Makefile for the Xenox 04 invitation ###

DEBUG = yes 	# produce debugging info
DEBUGOUT = yes 	# verbose debug output

OBJS=src/main.o src/SDLWindow.o src/PNGImage.o src/Texture.o src/Music.o\
	src/Scene.o src/Bitmapfont.o src/Particle.o src/Intro.o src/About.o\
	src/Scroller.o

CXX=g++
CXXFLAGS=-O2 -Wall -ansi -pedantic -I/usr/X11/include/ `sdl-config --cflags` `pkg-config libpng --cflags`
LIBS=`sdl-config --libs` -lGL -lGLU -lSDL_mixer `pkg-config libpng --libs`
TARGET=xl04_invite

all: $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
clean:
	rm -f $(OBJS)
