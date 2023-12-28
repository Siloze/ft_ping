
SRCS_DIR	=	src/

LIB_DIR		=	libft/
LIB_SRCS	=	ft_atoi.c			ft_bzero.c			ft_calloc.c			\
				ft_isalnum.c		ft_isalpha.c		ft_isascii.c		\
				ft_isdigit.c		ft_isprint.c		ft_itoa.c			\
				ft_memchr.c			ft_memcmp.c			ft_memcpy.c			\
				ft_memmove.c		ft_memset.c			ft_putchar_fd.c		\
				ft_putendl_fd.c		ft_putnbr_fd.c		ft_putstr_fd.c		\
				ft_split.c			ft_strchr.c			ft_strdup.c			\
				ft_striteri.c		ft_strjoin.c		ft_strlcat.c		\
				ft_strlcpy.c		ft_strlen.c			ft_strmapi.c		\
				ft_strncmp.c		ft_strnstr.c		ft_strrchr.c		\
				ft_strtrim.c		ft_substr.c			ft_tolower.c		\
				ft_toupper.c		ft_printf/ft_printf.c	ft_tabadd.c		\
				ft_printf/ft_utils.c	ft_strcmp.c		ft_strchrstr.c		\
				ft_tabtrim.c

				LIB_DIR		=	libft/

GNL_DIR		=	getnextline/
GNL_SRCS	=	get_next_line.c get_next_line_utils.c

LIB_PATH	=	$(addprefix $(SRCS_DIR)$(LIB_DIR), $(LIB_SRCS))
GNL_PATH	=	$(addprefix $(SRCS_DIR)$(GNL_DIR), $(GNL_SRCS))


SRCS_PATH	=	$(LIB_PATH) $(GNL_PATH)
OBJS		=	${SRCS_PATH:.c=.o}

NAME		=	libft

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

.c.o		:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
			
${NAME}		:	$(OBJS)
			ar rc libft.a $(OBJS)
			ranlib libft.a

clean		:
			rm -f $(OBJS)

all			:	${NAME} clean
				
fclean		:	clean
			rm -f libft.a

re			: 	fclean libft

.PHONY		:	clean all fclean re
