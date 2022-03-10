NAME = minishell

SRC_DIR = src
INCLUDES = includes
HEADERS := $(INCLUDES)/minishell.h
INCLUDES := $(addprefix -I, $(INCLUDES))

SRC_FILES = main.c minishell.c  \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR	= obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFLAGS = -L$(LIBFT_DIR) -lft

RM = rm -f

CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFLAGS) -o $@
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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