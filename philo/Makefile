.PHONY:	all clean fclean re fclean_lib fclean_all

# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME		=	philo

# ---- Directories ---- #

DIR_OBJS	=	.objs/

# ---- Files ---- #

SRCS		=	philo.c		utils.c	\
				msg_error.c

OBJS		=	${SRCS:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread

# ---- Commands ---- #

RM		=	rm -rf
MKDIR	=	mkdir -p

# ********* RULES ******** #

all				:	${NAME}

# ---- Variables Rules ---- #

${NAME}			:	${OBJS} Makefile
					${CC} ${CFLAGS} -o ${NAME} ${OBJS}

# ---- Compiled Rules ---- #

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
					${CC} ${CFLAGS} -MMD -I. -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}

-include ${DIR_OBJS}/*.d

# ---- Usual Commands ---- #

clean			:
					${RM} ${DIR_OBJS}

fclean			:	clean
					${RM} ${NAME}

re				:	fclean all
