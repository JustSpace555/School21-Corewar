# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/18 12:51:51 by eskeleto          #+#    #+#              #
#    Updated: 2019/10/16 13:44:34 by qmebble          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

LIB_FILE = libft.a

CFILES = main.c get_next_line.c read_file.c init.c name_and_comment.c free.c \
	label.c operation_code.c arg_is.c find_arguments.c check_args.c \
	check_file.c size_instructions.c reverse.c header_to_bytes.c \
	args_to_bytes.c number_to_bytes.c instruction_to_bytes.c comment.c \
	prog_name.c check_labels_on_duplicate.c multiple_files.c

OFILES = ${CFILES:.c=.o}

FLAGS = -Wextra -Werror -Wall

HFILES = -I ./libft

all: $(NAME)

$(NAME):
	@echo Compiling assembler ...
	@gcc $(FLAGS) $(HFILES) -c $(CFILES)
	@gcc $(FLAGS) $(OFILES) -L./libft -lft -o $(NAME)
	@mv $(NAME) ../$(NAME)

debug:
	@echo Compiling assembler for debug ...
	@gcc -g $(FLAGS) $(OFILES) -L./libft -lft -o $(NAME)
	@mv $(NAME) ../$(NAME)
	@mv $(NAME).dSYM ../$(NAME).dSYM

clean:
	@/bin/rm -f $(OFILES)

fclean: clean
	@/bin/rm -f ../$(NAME)

re: fclean all

