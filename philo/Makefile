.PHONY:	all clean fclean re

# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME		=	philo

# ---- Directories ---- #

DIR_OBJS	=	.build/

# ---- Files ---- #

SRCS		=	philo.c			utils.c			\
				msg_error.c		linked_list.c	\
				init.c			philo_action.c	\
				get_time.c		ft_putstr.c		\
				init_list.c		mutex.c			\
				death.c

OBJS		=	${SRCS:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror #-fsanitize=thread

# ---- Commands ---- #

RM		=	rm -rf
MKDIR	=	mkdir -p

# ********* RULES ******** #

all				:	${NAME}

# ---- Variables Rules ---- #

${NAME}			:	${OBJS} Makefile
					${CC} ${CFLAGS} -pthread -o ${NAME} ${OBJS}

# ---- Compiled Rules ---- #

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
					${CC} ${CFLAGS} -pthread -MMD -I. -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}

-include ${DIR_OBJS}/*.d

# ---- Usual Commands ---- #

clean			:
					${RM} ${DIR_OBJS}

fclean			:	clean
					${RM} ${NAME}

re				:	fclean all
