NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFLAGS = -L$(LIBFT_DIR) -lft

SRC_FILES =	main.c \
			hello.c \
			data_handler.c \
			minishell.c \
			prompt_take_input.c \
			history.c \
			lexer.c \
			parser.c \
			expand_variables.c \
			sorting.c \
			executor.c \
			exit.c \
			help.c \
			echo.c \
			str_tools.c

SRC_DIR = src
OBJ_DIR	= obj
HEADERS := minishell.h

#OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o) $(SRC_DIR) # main.o minishell.o parse_token.o prompt_take_input.o
OBJ =	main.o \
		hello.o \
		data_handler.o \
		minishell.o \
		prompt_take_input.o \
		history.o \
		lexer.o \
		parser.o \
		expand_variables.o \
		sorting.o \
		executor.o \
		exit.o \
		help.o \
		echo.o \
		str_tools.o
#INCLUDES = includes
#HEADERS := $(INCLUDES)/minishell.h

#INCLUDES := $(addprefix -I, $(INCLUDES))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline #-g -fsanitize=address

VPATH = src src/CORE src/PROMPT src/LEX \
		src/PARSE src/EXPAND src/EXEC \
		src/BUILTINS src/TOOLS

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

install:
	sudo apt-get install libreadline-dev

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git