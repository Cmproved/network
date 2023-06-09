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
	 src/search_client.c\
	 src/start_server.c\

SRC_DEFAULT = src/default/default_client_connected.c\
	 src/default/default_client_disconnected.c\
	 src/default/default_receive.c\
	 src/default/default_send.c\


CFLAGS 	+= -O3 -Ofast -Wall

CFLAGS_DEBUG += -Wall -g2 -Wextra -Wundef

OBJ_DIR = .obj
OBJ = ${patsubst %c, ${OBJ_DIR}/%o, ${SRC}}
OBJ += ${patsubst %c, ${OBJ_DIR}/%o, ${SRC_DEFAULT}}
OBJ_DEBUG = ${patsubst %c, ${OBJ_DIR}/%o_debug, ${SRC}}
OBJ_DEBUG += ${patsubst %c, ${OBJ_DIR}/%o_debug, ${SRC_DEFAULT}}

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

tests: debug
	gcc ${CFLAGS_DEBUG} tests/main.c -L. -lcstdnetwork

clean:
	${RM} ${OBJ} ${OBJ_DEBUG}

fclean: clean
	${RM} ${NAME} a.out

re: fclean all

.PHONY: all ${NAME} debug tests clean re fclean
