SRCS = main.c
INCLUDE = virtual_header.h
EXEC = corewar

all:
	@echo Compiling virtual machine ...
	@gcc $(SRCS) -I $(INCLUDE) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)

debug: fclean
	@echo Compiling virtual machine ...
	@gcc -g $(SRCS) -I $(INCLUDE) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)
	@mv $(EXEC).dSYM ../$(EXEC).dSYM

fclean:
	@rm -rf ../$(EXEC).dSYM
	@rm -rf ../$(EXEC)

re: fclean all
