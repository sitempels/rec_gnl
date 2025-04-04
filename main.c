#include "get_next_line.h"

int	main()
{
	char	*line;
	int			fd;

	fd = open("get_next_line.c", 'r');
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}
