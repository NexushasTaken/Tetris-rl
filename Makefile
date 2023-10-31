APPNAME = tetris
BUILD = build
TEST = ${BUILD}/tests
NAME=${BUILD}/${APPNAME}
CC = c++
SRCS = main.cpp tetris.cpp matrix_ds.cpp tetrimino.cpp tetris_matrix.cpp timer.cpp
OBJS = ${SRCS:%.cpp=${BUILD}/%.o}
CFLAGS = -ggdb -std=c++20 -MMD -MP
LDFLAGS = -L/usr/local/lib -lm -lraylib
DEPS = ${OBJS:%.o=%.d}

compile: ${NAME}

run: ${NAME}
	./${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${CFLAGS} -o $@ $^

${BUILD}/%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD} ${TEST}:
	mkdir -p $@

test_timer: ${TEST}/test_timer
	./${TEST}/$@

${TEST}/test_timer: timer.cpp tests/timer.cpp
	mkdir -p ${BUILD}/tests
	${CC} ${CFLAGS} ${LDFLAGS} -o ${TEST}/test_timer $^

debug: ${NAME}
	gdb ./${NAME}

clean:
	rm -rf ${BUILD}/*.o ${NAME}

.PHONY: clean run build test_timer
-include ${DEPS}
