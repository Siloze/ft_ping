# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/24 04:01:57 by mbastard          #+#    #+#              #
#    Updated: 2022/10/01 13:30:03 by mbastard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	bin/libft.a
MAKEFLAGS		+=	-s

#				DIRECTORIES

BIN_DIR			:=	bin/
OBJ_DIR			:=	obj/
SRC_DIR			:=	src/

#				COMPILATION

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror

#				SOURCES

FIND_SRC		=	$(shell find $(SRC_DIR)*.c)
SRC				:=	$(call FIND_SRC,)

#				OBJECTS

OBJ				:=	${SRC:.c=.o}
OBJ_PATH		:= $(subst $(SRC_DIR),$(OBJ_DIR), $(OBJ))

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
				mkdir -p $(BIN_DIR)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o ${addprefix $(OBJ_DIR), ${<:$(SRC_DIR)%.c=%.o}}
				ar rc $(NAME) ${addprefix $(OBJ_DIR), ${<:$(SRC_DIR)%.c=%.o}}

#				RULES

${NAME}			: $(OBJ_PATH)
				ranlib $(NAME)

all				: $(NAME)

clean			:
				rm -rf $(OBJ_DIR)

fclean			: clean
				rm -rf $(BIN_DIR)

re				: clean all

.PHONY			: all clean fclean re
