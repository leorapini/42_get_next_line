gcc -Wall -Werror -Wextra -g -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c
echo "BUFFER 1"
./a.out ./test/plano_de_carreira.txt

gcc -Wall -Werror -Wextra -g -D BUFFER_SIZE=200 main.c get_next_line.c get_next_line_utils.c
echo "BUFFER 200"
./a.out ./test/plano_de_carreira.txt
