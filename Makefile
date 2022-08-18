# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 15:17:17 by dilopez-          #+#    #+#              #
#    Updated: 2022/08/16 19:28:15 by dilopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES =================================

NAME			=	minishell
SRC_DIR			=	src
OBJ_DIR 		=	obj
INC_DIR			=	includes

RM				=	rm -rf
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra

SRCS			=	$(SRC_DIR)/test.c		\
					$(SRC_DIR)/print.c		\

OBJS			=	$(SRCS:.c=.o)
PREFIXED		=	$(addprefix $(OBJ_DIR)/, $(OBJS))

GREEN			=	"\\x1b[32m"
RED				=	"\\x1b[31m"
YELLOW			=	"\\x1b[33m"
RESET			=	"\\x1b[37m"

# =================================== RULES ===================================

$(NAME) : print_init $(PREFIXED) print_finish
	@$(CC) $(CFLAGS) $(PREFIXED) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)/src
	@echo "$(CC) $(CFLAGS) : \t $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

# ================================= FUNCTIONS =================================

print_init:
	@echo "\n$(YELLOW)---------- Compiling project's files ---------$(RESET)\n"

print_finish:
	@echo "\n${GREEN}---------- Mandatory part compiled! ----------${RESET}\n"

print_nl:
	@echo ""

all: $(NAME)

clean:
	@rm -rf $(OBJ) $(DIR_OBJ)
	@echo "\n${GREEN}------------------ Cleaned! ------------------${RESET}\n"

fclean: clean
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus