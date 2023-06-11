CC=gcc

NAME=libcstdnetwork.a

SRC = src/accept_server.c\
	 src/backup_server.c\
	 src/client_actions.c\
	 src/client_del.c\
	 src/client_size.c\
	 src/create_server.c\
	 src/destroy_server.c\
	 src/init_server.c\
	 src/kick.c\
	 src/setup_func.c\
	 src/setup_func_2.c\
	 src/search_client.c\
	 src/start_server.c\

SRC_DEFAULT = src/default/default_client_connected.c\
	 src/default/default_client_disconnected.c\
	 src/default/default_receive.c\
	 src/default/default_send.c\
	 src/default/default_timeout.c\

SRC_TEST = tests/unit_test.c

CFLAGS 	+= -O3 -Ofast -Wall

CFLAGS_DEBUG += -Wall -g2 -Wextra -Wundef

OBJ_DIR = .obj
OBJ = ${patsubst %c, ${OBJ_DIR}/%o, ${SRC}}
OBJ += ${patsubst %c, ${OBJ_DIR}/%o, ${SRC_DEFAULT}}
OBJ_DEBUG = ${patsubst %c, ${OBJ_DIR}/%o_debug, ${SRC}}
OBJ_DEBUG += ${patsubst %c, ${OBJ_DIR}/%o_debug, ${SRC_DEFAULT}}
OBJ_TEST = ${patsubst %c, ${OBJ_DIR}/%o, ${SRC_TEST}}

TEST_FLAG = -lcriterion -L. -lcstdnetwork

RM=rm -rf

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c -o $@ $<

${OBJ_DIR}/%.o_debug: %.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS_DEBUG} -c -o $@ $<

all: ${NAME}

${NAME}: ${OBJ}
	ar rc $(NAME) $^

debug: ${OBJ_DEBUG}
	ar rc ${NAME} $^

tests: debug unit_test
	gcc ${CFLAGS_DEBUG} tests/main.c -L. -lcstdnetwork -o default_server

unit_test: ${OBJ_TEST}
	gcc ${CFLAGS_DEBUG} ${OBJ_TEST} ${TEST_FLAG} -o unit_test

clean:
	${RM} ${OBJ} ${OBJ_DEBUG}

fclean: clean
	${RM} ${NAME} a.out unit_test default_server

re: fclean all

.PHONY: all ${NAME} debug tests clean re fclean unit_test
