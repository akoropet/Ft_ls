# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:26:29 by akoropet          #+#    #+#              #
#    Updated: 2019/09/16 16:40:24 by akoropet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_ls

SRC_DIR =       ./source/
OBJ_DIR =       ./objective/
INC_DIR =       ./include/

SRC =			main.c 				\
				sort_files.c		\
				create_file_info.c	\
				read_data.c			\
				print_data.c		\
				open_dir.c			\
				add_data.c			\
				supporting.c

OBJ =           $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB = 			./lib/lib.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C lib
	@gcc $(FLAGS) $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -o $(NAME)
	@echo "\033[92m>>>ft_ls compiled<<<\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@make clean -C lib
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C lib
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)
