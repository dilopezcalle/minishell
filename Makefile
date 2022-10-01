# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 15:17:17 by dilopez-          #+#    #+#              #
#    Updated: 2022/10/01 16:24:26 by dilopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES =================================

NAME			=	minishell
LIBFT			=	libft.a
SRC_DIR			=	src
OBJ_DIR 		=	obj
INC_DIR			=	includes
BUIL_DIR		=	$(SRC_DIR)/builtins
PARSER_DIR		=	$(SRC_DIR)/parser

RM				=	rm -rf
CC				=	gcc
CFLAGS			=	-I $(INC_DIR) -g3 -Wall -Werror -Wextra
RLFLAGS			=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
					-I /Users/$(USER)/.brew/opt/readline/include

SRCS			=	$(SRC_DIR)/minishell.c			\
					$(SRC_DIR)/executor.c			\
					$(SRC_DIR)/signals.c			\
					$(SRC_DIR)/utils.c				\
					$(SRC_DIR)/main.c				\
					$(BUIL_DIR)/builtin_parent.c	\
					$(BUIL_DIR)/builtin_child.c		\
					$(BUIL_DIR)/exit.c				\
					$(BUIL_DIR)/echo.c				\
					$(BUIL_DIR)/cd.c				\
					$(PARSER_DIR)/syntax_errors.c	\
					$(PARSER_DIR)/access_parser.c	\
					$(PARSER_DIR)/files_access.c	\
					$(SRC_DIR)/ft_getenv.c			\
					$(PARSER_DIR)/parser.c			\
					$(PARSER_DIR)/tokens.c			\
					$(PARSER_DIR)/lexer.c			\

OBJS			=	$(SRCS:.c=.o)
PREFIXED		=	$(addprefix $(OBJ_DIR)/, $(OBJS))

RED				=	"\\x1b[31m"
GREEN			=	"\\x1b[32m"
YELLOW			=	"\\x1b[33m"
RESET			=	"\\x1b[37m"

# =================================== RULES ===================================

$(NAME):	$(PREFIXED)
	@printf \
	"$(YELLOW)------------ Project's files compiled ------------\n$(RESET)\n%-33.33s\r"
	@make -C ./$(SRC_DIR)/libft
	@cp ./$(SRC_DIR)/libft/$(LIBFT) .
	@$(CC) $(CFLAGS) $(PREFIXED) $(RLFLAGS) $(LIBFT) -o $(NAME)
	@echo "\n${GREEN}------------ Mandatory part compiled! ------------${RESET}\n"

$(OBJ_DIR)/%.o:	%.c
	@mkdir -p $(OBJ_DIR)/$(PARSER_DIR) $(OBJ_DIR)/$(BUIL_DIR)
	@printf "$(YELLOW)Compiling project's file -> $(RESET)%-33.33s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# ================================= FUNCTIONS =================================

all:	$(NAME)

clean:
	@make -C ./src/libft clean
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo "\n${GREEN}-------------------- Cleaned! --------------------${RESET}\n"

fclean:	clean
	@make -C ./src/libft fclean
	@$(RM) $(NAME) $(LIBFT) minishell.dSYM

re:		fclean all

.PHONY: all clean fclean re bonus print_init
