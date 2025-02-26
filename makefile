PROG_NAME=Gridded_Map_Visualizer

CC=gcc
ERR=-Wall
OTM=-O2

INC_DIR=-I include -I C:\MinGW\include
LIB_DIR=-L lib -L C:\MinGW\lib

OBJS=main.o
LIBS=-l:libgdi32.a -l:libuser32.a -l:libglfw3.a -l:libopengl32.a

all: $(PROG_NAME) clean

$(PROG_NAME): main.o
	$(CC) main.o $(LIB_DIR) $(LIBS) -o $(PROG_NAME).exe

main.o:
	$(CC) $(ERR) $(OTM) $(INC_DIR) -c src/main.c -o main.o

clean:
	del *.o