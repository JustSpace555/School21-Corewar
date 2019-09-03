SRC_FOLDER = Src/
SRC =	$(SRC_FOLDER)main.c \
		$(SRC_FOLDER)players_parser_help.c \
		$(SRC_FOLDER)players_parser.c \
		$(SRC_FOLDER)print_any.c \
		$(SRC_FOLDER)virtual_machine.c

INCLUDE_FOLDER = Headers/
INCLUDE =	$(INCLUDE_FOLDER)virtual_header.h \
			$(INCLUDE_FOLDER)op.h

EXEC = corewar

all:
	@echo Compiling virtual machine ...
	@gcc $(SRC) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)

debug: fclean
	@echo Compiling virtual machine ...
	@gcc -g $(SRC) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)
	@mv $(EXEC).dSYM ../$(EXEC).dSYM

fclean:
	@rm -rf ../$(EXEC).dSYM
	@rm -rf ../$(EXEC)

re: fclean all
