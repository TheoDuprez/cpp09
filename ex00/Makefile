# VARIABLE DECLARATION ############################################################################

NAME =			btc

CC =			c++

CFLAGS =		-Wall -Werror -Wextra -std=c++98 -MD

BLACK	= 		\033[0;30m
RED		= 		\033[0;91m
GREEN	= 		\033[0;92m
YELLOW	= 		\033[0;93m
BLUE	= 		\033[0;94m
PURPLE	= 		\033[0;35m
CYAN	= 		\033[0;96m
WHITE	= 		\033[0;37m

SRCS =			main \
				BitcoinExchange \

OBJS =			$(addsuffix .o, $(addprefix .objs/, $(SRCS)))
D_OBJS =		$(addsuffix .d, $(addprefix .objs/, $(SRCS)))

# RULES ###########################################################################################

$(NAME): $(OBJS)
	@echo "$(CYAN)Compiling btc :$(WHITE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)btc successfully compiled !$(WHITE)"

all: $(NAME)

./.objs/%.o: ./srcs/%.cpp
	@mkdir -p .objs
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Deleting all files exept binaries$(WHITE)"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(PURPLE)Deleting binaries$(WHITE)"
	@rm -rf $(NAME)
	@rm -rf .objs

re:
	make -s fclean
	make -s all

.SILENT:

.PHONY: all clean fclean re

-include $(D_OBJS)
