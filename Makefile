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
TEST_D = tests

SRC = $(SRC_D)/hash.c\
	$(SRC_D)/new_node.c\
	$(SRC_D)/add_node_to_history.c\
	$(SRC_D)/history_destroy.c\
	$(SRC_D)/hm_new.c\
	$(SRC_D)/hm_destroy.c\
	$(SRC_D)/find_node_by_key.c\
	$(SRC_D)/node_remove_from_list.c\
	$(SRC_D)/hm_remove.c\
	$(SRC_D)/hm_add_new_key.c\
	$(SRC_D)/hm_find_existing_node_and_replace_value.c\
	$(SRC_D)/hm_insert_node.c\
	$(SRC_D)/hm_handle_collision.c\
	$(SRC_D)/hm_set.c\
	$(SRC_D)/hm_get_seq.c\
	$(SRC_D)/hm_get.c\
	$(SRC_D)/hm_get_collision_count.c
	

INC = $(INC_D)/hashmap.h

OBJ := $(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

LIBFT = $(LIB_D)/libft/libft.a
LIBPAIR = $(LIB_D)/pair/pair.a

LIB_INC = $(LIB_D)/libft/inc
LIB_INC_PAIR = $(LIB_D)/pair/inc

CC = clang
LD = ar

CC_FLAGS = -Wall -Werror -Wextra
#CC_FLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LD_FLAGS = -rcs

all: $(NAME)

$(NAME): $(LIBFT) $(LIBPAIR) $(OBJ_D) $(OBJ) $(INC_D) $(INC)
	@$(LD) $(LD_FLAGS) $(NAME) $(OBJ)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -I$(LIB_INC_PAIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_D)/libft

$(LIBPAIR):
	@make -C $(LIB_D)/pair
	
clean:
	@rm -rf $(OBJ_D)
	@rm	-rf *.dSYM
	@make -C $(LIB_D)/libft clean
	@make -C $(LIB_D)/pair clean

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@make -C $(LIB_D)/libft fclean
	@make -C $(LIB_D)/pair fclean

submodule:
	@git submodule init
	@git submodule update

test: $(NAME)
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -I$(LIB_INC_PAIR) -o test $(TEST_D)/main.c $(NAME) $(LIBFT)
	@./test
	
re: fclean all
