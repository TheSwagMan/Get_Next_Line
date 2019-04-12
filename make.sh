cp ../libft/srcs/*.c libft/srcs && cp ../libft/includes/*.h libft/includes/ && cp ../libft/Makefile libft/
make -C libft/ > /dev/null
norminette get_next_line.c get_next_line.h
clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
./test_gnl test.txt test2.txt & sleep 1; kill $!
make -C libft/ fclean > /dev/null
rm *.o test_gnl
