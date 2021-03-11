#include <fcntl.h>
#include <stdio.h>
#include <strings.h>

#include "get_next_line.h"

int     main(int ac, char **av)
{
	int     fd;
	char	*line;
	
	
	if (ac < 2)
	{
		printf("missing file name\n");
	}
	
	
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
		free(line);
	}
		
	close(fd);     
        return (0);     
}              
