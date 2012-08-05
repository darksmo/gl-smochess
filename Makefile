INC = -I./src
LDFLAGS = $(INC) -L/usr/X11R6/lib -lGL -lGLU -lglut -lm
CC = gcc

main: clean
	$(CC) src/*.c $(LDFLAGS) -o chessboard

clean:
	rm -rf chessboard
