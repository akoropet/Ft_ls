# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:26:29 by akoropet          #+#    #+#              #
#    Updated: 2019/04/30 18:19:39 by akoropet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c 				\
		sort_files.c		\
		create_file_info.c	\
		read_data.c			\
		print_data.c		\
		open_dir.c			\
		add_data.c			\
		supporting.c

LIB = ./lib/lib.a

OB = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OB)
	@make -C lib
	@gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@echo "\033[92m>>>ft_ls compiled<<<\033[0m"

%.o : %.c
	@gcc $(FLAGS) -c -o $@ $<

clean:
	@make clean -C lib
	@rm -f $(OB)

fclean: clean
	@make fclean -C lib
	@rm -f $(NAME)

re: fclean all
