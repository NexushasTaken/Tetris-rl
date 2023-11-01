APPNAME = tetris
BUILD = build
TEST = ${BUILD}/tests
NAME=${BUILD}/${APPNAME}
CC = c++
SRCS = main.cpp tetris.cpp matrix_ds.cpp tetrimino.cpp tetris_matrix.cpp time.cpp random.cpp
OBJS = ${SRCS:%.cpp=${BUILD}/%.o}
CFLAGS = -ggdb -std=c++20 -MMD -MP
LDFLAGS = -L/usr/local/lib -lm -lraylib
DEPS = ${OBJS:%.o=%.d}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${CFLAGS} -o $@ $^

${BUILD}/%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD} ${TEST}:
	mkdir -p $@

# ---- StartTest ----
test_timer: ${TEST}/test_timer
	./${TEST}/$@

${TEST}/test_timer: time.cpp tests/timer.cpp
	mkdir -p ${TEST}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${TEST}/$(notdir $@) $^

test_random: ${TEST}/test_random
	./${TEST}/$@

${TEST}/test_random: random.cpp tests/random.cpp
	mkdir -p ${TEST}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${TEST}/$(notdir $@) $^
# ---- EndTest ----

debug: ${NAME}
	gdb ./${NAME}

run: ${NAME}
	./${NAME}

clean:
	rm -rf ${BUILD}/*.o ${NAME}

.PHONY: clean run test_timer
-include ${DEPS}
