#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>

#include "get_next_line.c"

//#include "get_next_line2.c"
//#include "get_next_line_utils.c"

int     main(void)
{
	int     fd = open("plano_de_carreira.txt", O_RDONLY);
	int	counter;
	//char	*line;

	counter = 7;
	if (fd <= 0)
	{
		printf("error\n");
		return (1);
	}
	
	
	while (get_next_line(fd) == 1)
		;
      
/* 
	while (counter-- > 0)
		get_next_line(fd);
*/      
	if (close(fd) < 0)
	{
                printf("error\n");
                return (1);
	}
        return (0);     
}              
