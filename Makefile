APPNAME = tetris
BUILD = build
NAME=${BUILD}/${APPNAME}
CC = cc
SRCS = main.c grid.c utils.c
OBJS = ${SRCS:%.c=${BUILD}/%.o}
CFLAGS = -ggdb
LDFLAGS = -L/usr/local/lib -lm

all: ${BUILD} ${NAME}
	./${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${CFLAGS} -o $@ $^

${BUILD}/%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD}:
	mkdir -p $@

clean:
	rm -f ${BUILD}/*.o ${NAME}

.PHONY: clean
