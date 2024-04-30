CC=g++
CFLAGS = -std=c++20
LFLAGS = -lncurses

NAME = chess

SRC = main.cpp piece.cpp square.cpp board.cpp history.cpp
DEPS = piece.hpp square.hpp board.hpp history.hpp

OBJS = main.o piece.o square.o board.o history.o

YOU:$(SRC) $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o:%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)
