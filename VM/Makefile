SRC_FOLDER = Src/
SRC =	$(SRC_FOLDER)main.c \
		$(SRC_FOLDER)players_parser_help.c \
		$(SRC_FOLDER)players_parser.c \
		$(SRC_FOLDER)print_any.c \
		$(SRC_FOLDER)virtual_machine.c \
		$(SRC_FOLDER)args_parser.c \
		$(SRC_FOLDER)initializer.c \
		$(SRC_FOLDER)extra_functions.c

INCLUDE_FOLDER = Headers/
INCLUDE =	$(INCLUDE_FOLDER)virtual_header.h \
			$(INCLUDE_FOLDER)op.h

LIB_FOLDER = ../libft/SRC/
SRC_FOR_DEBUG = $(LIB_FOLDER)main_functions/ft_strlen.c

EXEC = corewar

all:
	@echo Compiling virtual machine ...
	@gcc $(SRC) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)

debug: fclean
	@echo Compiling virtual machine ...
	@gcc -g $(SRC) $(SRC_FOR_DEBUG) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)
	@mv $(EXEC).dSYM ../$(EXEC).dSYM

fclean:
	@rm -rf ../$(EXEC).dSYM
	@rm -rf ../$(EXEC)

re: fclean all
