# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 19:22:31 by  rleite-s         #+#    #+#              #
#    Updated: 2023/08/13 16:07:58 by  rleite-s        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	0_philo 1_init 2_dinner 3_death_functions 4_philo_actions \
			5_forks 6_feeding 7_global_functions

PATH_O	=	objs/
OBJS	=	$(addprefix $(PATH_O), $(addsuffix .o, $(SRC)))

CFLAGS	=	-pthread -g -Wall -Wextra -Werror

RM		=	rm -f

$(PATH_O)%.o: %.c philo.h
	cc -c $(CFLAGS) $< -o $@

all: $(PATH_O) $(NAME) 

$(PATH_O):
	mkdir -p $(PATH_O)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS) valgs -r $(PATH_O)

fclean: clean
	$(RM) $(NAME)

re: fclean all

normi:
	norminette -R CheckHeader -R CheckForbbidenSourceHeader $(addsuffix .c, $(SRC))

w:
	watch -n0 norminette -R CheckHeader -R CheckForbbidenSourceHeader $(addsuffix .c, $(SRC))

h: all
	@clear
	@valgrind --log-file=valgs --tool=helgrind --history-level=approx -s ./philo   5 600 150 150 50
#	@valgrind --log-file=valgs --tool=helgrind -s ./philo "    4 "  410 200 200

d: all
	clear
	valgrind --log-file=valgs --tool=drd  -s ./philo	 5 800 200 200 7

v: all
	@valgrind --log-file=valgs --leak-check=full --show-leak-kinds=all ./philo "    7 "  5000 400 100 3

.PHONY: all clean fclean re objs h d v
