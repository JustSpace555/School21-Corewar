SRC_FOLDER = Src/
SRC =	$(SRC_FOLDER)main.c \
		$(SRC_FOLDER)players_parser_help.c \
		$(SRC_FOLDER)players_parser.c \
		$(SRC_FOLDER)print_any.c \
		$(SRC_FOLDER)virtual_machine.c \
		$(SRC_FOLDER)args_parser.c \
		$(SRC_FOLDER)initializer.c \
		$(SRC_FOLDER)extra_functions.c \
		$(SRC_FOLDER)virtual_machine_help.c \
		$(SRC_FOLDER)cursors_commands_pt1.c \
		$(SRC_FOLDER)cursors_commands_pt2.c \
		$(SRC_FOLDER)cursors_commands_pt3.c \
		$(SRC_FOLDER)operations_help_pt1.c \
		$(SRC_FOLDER)operations_help_pt2.c

SRC_VIS_FOLDER = ../visualisator/
SRC_VIS =	$(SRC_VIS_FOLDER)visualisator.c \
			$(SRC_VIS_FOLDER)push_info.c \
			$(SRC_VIS_FOLDER)visualisator_help.c

INCLUDE_FOLDER = Headers/
INCLUDE =	$(INCLUDE_FOLDER)virtual_header.h \
			$(INCLUDE_FOLDER)op.h \
			$(SRC_VIS_FOLDER)visualisator.h

LIB_FOLDER = ../libft/Src/
SRC_FOR_DEBUG = $(LIB_FOLDER)main_functions/ft_itoa.c

FLAGS = -Wall -Wextra -Werror

FRAMEWORKS =	-I/Library/Frameworks/SDL2.framework/Headers -F ~/Library/Frameworks -framework SDL2 \
				-I/Library/Frameworks/SDL2_ttf.framework/Headers -F ~/Library/Frameworks -framework SDL2_ttf

EXEC = corewar

all:
	@echo Compiling virtual machine ...
	@bash /Users/qmebble/Git/corewar/visualisator/script.bash
	@gcc $(FLAGS) $(SRC) $(SRC_VIS) $(FRAMEWORKS) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)

debug: fclean
	@echo Compiling virtual machine for debug ...
	@gcc -g $(FLAGS) $(SRC) $(SRC_VIS) $(SRC_FOR_DEBUG) $(FRAMEWORKS) -I $(INCLUDE_FOLDER) ../libft.a -o $(EXEC)
	@mv $(EXEC) ../$(EXEC)
	@mv $(EXEC).dSYM ../$(EXEC).dSYM

fclean:
	@rm -rf ../$(EXEC).dSYM
	@rm -rf ../$(EXEC)

re: fclean all
