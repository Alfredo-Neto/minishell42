NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFLAGS = -L$(LIBFT_DIR) -lft

SRC_FILES = main.c minishell.c parse_token.c prompt_take_input.c  \

SRC_DIR = src
OBJ_DIR	= obj
HEADERS := minishell.h
#OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o) $(SRC_DIR) # main.o minishell.o parse_token.o prompt_take_input.o
OBJ = main.o minishell.o parse_token.o prompt_take_input.o
#INCLUDES = includes
#HEADERS := $(INCLUDES)/minishell.h

#INCLUDES := $(addprefix -I, $(INCLUDES))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline

VPATH = src src/parse src/prompt

RM = rm -f

$(OBJ_DIR)/%.o: /%.c $(HEADERS) #$(SRC_DIR)
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFLAGS) -o $@
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

$(LIBFT):
		make -C $(LIBFT_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:
	make -C $(LIBFT_DIR) fclean
	@echo ""
	@echo "|		minishell deleted		|"
	@echo ""

fclean: clean
	$(RM) $(OBJ)
	$(RM) $(NAME)

install:
	@sudo apt-get -y install libreadline-dev

re: fclean all

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git