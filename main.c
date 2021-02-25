#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.c"
#include <strings.h>

int     main(void)
{
	char    *line;
	int     fd = open("test.txt", O_RDONLY);

	if (fd <= 0)
	{
		printf("error\n");
		return (1);
	}
        
	while (get_next_line(fd, &line) != 0)
	{
		printf("\nOUTPUT:\n(%s)\n", line);
 	}
        
	if (close(fd) < 0)
        {
                printf("error\n");
                return (1);
	}
        free(line);
        return (0);     
}              
