.PHONY:	all clean fclean re

# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME		=	philo_bonus

# ---- Directories ---- #

DIR_OBJS	=	.build/

# ---- Files ---- #

SRCS		=	philo_bonus.c		msg_error_bonus.c		\
				utils_bonus.c		init_bonus.c			\
				get_time_bonus.c	philo_action_bonus.c	\
				ft_putstr_bonus.c

OBJS		=	${SRCS:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

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
