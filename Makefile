APPNAME = tetris
BUILD = build
NAME=${BUILD}/${APPNAME}
CC = c++
SRCS = main.cpp matrix_ds.cpp tetrimino.cpp tetris_matrix.cpp timer.cpp
OBJS = ${SRCS:%.cpp=${BUILD}/%.o}
CFLAGS = -ggdb -std=c++20
LDFLAGS = -L/usr/local/lib -lm -lraylib

all: ${NAME}
	./${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${CFLAGS} -o $@ $^

${BUILD}/%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD}:
	mkdir -p $@

debug: ${NAME}
	gdb ./${NAME}

clean:
	rm -f ${BUILD}/*.o ${NAME}

.PHONY: clean
