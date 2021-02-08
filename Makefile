#**************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: haachtch <haachtch@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/28 20:22:26 by haachtch      #+#    #+#                  #
#    Updated: 2020/09/03 14:14:42 by haachtch      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libhashmap.a

SRC_D  = src
INC_D = inc
OBJ_D = obj
LIB_D = lib

SRC = $(SRC_D)/hash_map.c

INC = $(INC_D)/hashmap.h

OBJ := $(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

LIBFT = $(LIB_D)/libft/libft.a

LIB_INC = $(LIB_D)/libft/inc

CC = clang
LD = ar

CC_FLAGS = -Wall -Werror -Wextra
#CC_FLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LD_FLAGS = -rcs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_D) $(OBJ) $(INC_D) $(INC)
	@$(LD) $(LD_FLAGS) $(NAME) $(OBJ)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_D)/libft

clean:
	@rm -rf $(OBJ_D)
	@rm	-rf *.dSYM
	@make -C $(LIB_D)/libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@make -C $(LIB_D)/libft fclean

submodule:
	@git submodule init
	@git submodule update

test: $(NAME)
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -o test tests/main.c $(NAME) lib/libft/libft.a 
	@./test
	
re: fclean all
