BIN				:=	bin/
NAME			:=	ft_ping
NAME_PATH		:=	$(addprefix $(BIN), $(NAME))
MAKEFLAGS		+=	--silent

SDIR			:=	src/
SRC				:=	$(shell find src -name "*.c")

ODIR			:=	obj/
OBJ				:=	$(subst $(SDIR),$(ODIR), ${SRC:.c=.o})

LFT_DIR			:=	Lib/
LFT				:=	$(addprefix $(LFT_DIR), libft.a)

CC				:=	gcc
CFLG			:=	-Wall -Wextra -Werror
LFLG			:=	-lm

$(ODIR)%.o		: $(SDIR)%.c
				mkdir -p $(subst $(SDIR),$(ODIR), $(shell dirname $<)/)
				$(CC) $(CFLG) -c $< -o ${addprefix $(ODIR), ${<:$(SDIR)%.c=%.o}}

${NAME_PATH}	: $(OBJ)
				mkdir -p $(BIN)
				cd $(LFT_DIR) && make all
				$(CC) $(OBJ) -o $(NAME_PATH) $(LFT) $(LFLG)

all				: $(NAME_PATH)

clean			:
				cd $(LFT_DIR) && make clean
				rm -rf $(ODIR)

fclean			: clean
				cd $(LFT_DIR) && make fclean
				rm -rf $(BIN)

re				: fclean all


.PHONY			: all clean fclean re