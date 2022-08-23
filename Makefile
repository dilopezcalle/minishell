# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 15:17:17 by dilopez-          #+#    #+#              #
#    Updated: 2022/08/20 12:42:56 by dilopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES =================================

NAME			=	minishell
LIBFT			=	libft.a
SRC_DIR			=	src
OBJ_DIR 		=	obj
INC_DIR			=	includes

RM				=	rm -rf
CC				=	gcc
CFLAGS			=	-I $(INC_DIR) -g -Wall -Werror -Wextra

SRCS			=	$(SRC_DIR)/main.c			\
					$(SRC_DIR)/parser.c			\
					$(SRC_DIR)/lexer.c			\

OBJS			=	$(SRCS:.c=.o)
PREFIXED		=	$(addprefix $(OBJ_DIR)/, $(OBJS))

GREEN			=	"\\x1b[32m"
RED				=	"\\x1b[31m"
YELLOW			=	"\\x1b[33m"
RESET			=	"\\x1b[37m"

# =================================== RULES ===================================

$(NAME) : print_init $(PREFIXED)
	@echo "\n$(YELLOW)----------- Compiling libft's files ----------$(RESET)\n"
	@make -C ./$(SRC_DIR)/libft
	@cp ./$(SRC_DIR)/libft/$(LIBFT) .
	@$(CC) $(CFLAGS) $(PREFIXED) $(LIBFT) -o $(NAME)
	@echo "\n${GREEN}---------- Mandatory part compiled! ----------${RESET}\n"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)/src/libft
	@echo "$(CC) $(CFLAGS) : \t $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# ================================= FUNCTIONS =================================

print_init:
	@echo "\n$(YELLOW)---------- Compiling project's files ---------$(RESET)\n"

all: $(NAME)

clean:
	@make -C ./src/libft clean
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo "\n${GREEN}------------------ Cleaned! ------------------${RESET}\n"

fclean: clean
	@make -C ./src/libft fclean
	@$(RM) $(NAME) $(LIBFT) minishell.dSYM

re: fclean all

.PHONY: all clean fclean re bonus