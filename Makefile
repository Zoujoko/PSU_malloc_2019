##
## EPITECH PROJECT, 2020
## PSU_2019_malloc
## File description:
## Makefile
##

LIB_DIR	=	lib/
TESTS_DIR	=	tests/

SRC	=	$(LIB_DIR)malloc.c \
		$(LIB_DIR)my_others.c

SRC_TESTS	=	$(TESTS_DIR)criterion.c

CFLAGS	=	-Wall -Wextra -fpic -shared -I ./include

OBJ =	$(SRC:.c=.o)

OBJ_TESTS	=	$(SRC_TETS:.c=.o)

RM	=	rm -f

NAME	=	libmy_malloc.so

TESTS	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

tests_run: $(OBJ_TESTS)
	make re -s
	$(CC) -o $(TESTS) $(SRC_TESTS) -I ./include -lcriterion --coverage -ldl
	./unit_tests

debug:	$(OBJ)
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g3

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTS)
	$(RM) *.gcno
	$(RM) *.gcda

re: fclean all

.PHONY: all clean re fclean