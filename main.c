#include <fcntl.h>
#include <stdio.h>
#include <strings.h>

#include "get_next_line.h"

int     main(void)
{
	int     fd = open("test.txt", O_RDONLY);
	char	*line;

	if (fd <= 0)
	{
		printf("error\n");
		return (1);
	}
	
	while (get_next_line(fd, &line) == 1)
	{
		printf("(%s)\n", line);
		free(line);
	}
		
      
	if (close(fd) < 0)
	{
                printf("error\n");
                return (1);
	}
        return (0);     
}              
