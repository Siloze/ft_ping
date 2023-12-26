SRCS_DIR		=	src/
OBJS_DIR		=	obj/
LIB_DIR			=	libft/
BIN_DIR			=	bin/

LIBFT_SRCS		=	bin/libft.a
LIB_PATH		=	$(addprefix $(LIB_DIR), $(LIBFT_SRCS))

SRCS			=	main.c clock.c signal.c headers.c utils.c
SRCS_PATH		=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS			=	${SRCS_PATH:.c=.o}
OBJS_PATH		=	$(subst $(SRCS_DIR),$(OBJS_DIR), $(OBJS))

NAME			=	ft_ping
NAME_PATH		=	$(addprefix $(BIN_DIR), $(NAME))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

$(OBJS_DIR)%.o	: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o ${addprefix $(OBJS_DIR), ${<:$(SRCS_DIR)%.c=%.o}}

${NAME_PATH}	: ${OBJS_PATH}
				cd $(LIB_DIR) && make
				$(CC) $(CFLAGS)  ${LIB_PATH} $(OBJS_PATH) -o $(NAME_PATH)

all		: $(NAME_PATH)

clean			:
				rm -f $(OBJS_PATH)

fclean			: clean
				rm -f $(NAME_PATH)

re				: fclean all

.PHONY			: all clean fclean re
