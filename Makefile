# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 13:47:53 by yechoi            #+#    #+#              #
#    Updated: 2021/05/20 13:56:07 by yechoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= clang++ -std=c++98
FLAGS	= -Wall -Wextra -Werror
SRCS	= test/main.cpp
OBJS	= $(SRCS:.cpp=.o)

NAME	= ft_container

all		: $(NAME)

$(NAME)	: $(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean	: 
		rm $(OBJS)

fclean	: clean
		rm $(NAME)
	
re		: fclean $(NAME)

.PHONY	: all clean fclean re 
