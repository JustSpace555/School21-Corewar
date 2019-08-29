all:
	@make -C ./libft/
	@make -C ./VM/

fclean:
	@make -C ./libft/ fclean
	@make -C ./VM/ fclean

new:
	@make -C ./VM/ re

debug:
	@make -C ./VM/ debug

re: fclean all
