# Name
NAME = cub3D

# Directories
SRC_DIR = srcs/
BLD_DIR = build/
LIBMLX = ./libraries/MLX42/
LIBFTDR = ./libraries/libft/
OBJ_DIR = ./build/objects/
INC = -I ./include -I $(LIBMLX)include

# MLX42 Repository
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
MLX42_DIR = ./libraries/MLX42

# Compiler and CFlags
CC = cc
CFLAGS = -g -Wall -Wextra #-Werror#-g -fsanitize=address
LIBFT = ./libraries/libft/libft.a
MLXFLAGS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Source Files
MAIN_DIR = $(SRC_DIR)main.c $(SRC_DIR)init.c $(SRC_DIR)render.c $(SRC_DIR)input.c $(SRC_DIR)fps.c
PARSER_DIR = $(SRC_DIR)parser/parse_map.c \
			$(SRC_DIR)parser/parse_utils.c
CLOSING_DIR = $(SRC_DIR)close_program/error_handler.c \
			$(SRC_DIR)close_program/close_program.c

# Concatenate all source files
SRCS = $(MAIN_DIR) $(PARSER_DIR) $(CLOSING_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Check if git is available
GIT := $(shell command -v git 2> /dev/null)

# Build rules
start:
	@make all

$(LIBFT):
	@make -C ./libraries/libft

all: check-mlx $(NAME)

# Check and clone MLX42 if needed
check-mlx:
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "MLX42 not found. Cloning repository..."; \
		mkdir -p ./libraries; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	fi
	@make libmlx

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) $(INC) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "Compiling ${notdir $<}"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleanups
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BLD_DIR)
#	@rm -rf $(LIBMLX)/build
#	@make clean -C ./libraries/libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@echo "All clean"

re: fclean all

# Phony targets represent actions not files
.PHONY: start all clean fclean re libmlx check-mlx