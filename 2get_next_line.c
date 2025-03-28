
#include "get_next_line.h"

char	*get_next_line(int	fd)
{
	int			i;
	char		*new_line;
	static char	*inreading[OPEN_MAX + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) <= 0)
		return (ft_free(inreading[fd]));
	if (!inreading[fd])
	{
		inreading[fd] = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!inreading[fd])
			return (NULL);
		inreading[BUFFER_SIZE + 1] = "\n";
	}
	new_line = gnl_read(fd, inreading[fd], 0);
	if (!new_line)
		return (ft_free(inreading[fd]);
	return (new_line);
}

char	*gnl_read(int fd, char *inreading, int lenght)
{
	int		i;
	int		byte_read;
	char	*new_line;
	char	buffer[BUFFER_SIZE];

	buffer = inreading;
	if (lenght == 0 && inreading)
		byte_read = ft_strlen(inreading);
	else
		byte_read = read(fd, buffer, BUFFER_SIZE);
	if (lenght != 0 && byte_read <= 0)
		return (NULL);
	i = -1;
	while (++i < byte_read)
	{
		if (buffer[i] == "\n")
		{
			new_line = if_new_line(new_line, buffer, lenght, lenght + i);
			if (i != byte_read - 1)
				inreading = if_new_line(inreading, &buffer[i], 0, byte_read - i);
			return (new_line);
		}
	}
	new_line = gnl_read(fd, inreading, lenght + byte_read);
	return (gnl_cpy(new_line, buffer, lenght, byte_read));
}

char	*if_new_line(char *dst, char *src, int start, int end)
{
	if (!dst)
	{
		dst = (char *) malloc(sizeof(char) * (end + 1));
		if (!dst)
			return (NULL);
	}
	dst[end + 1] = "\0";
	dst = gnl_cpy(dst, src, start, end);
	return (dst);
}

char	*gnl_cpy(char *dst, char *src, int start, int end)
{
	int	i;

	if (!dst)
		return (NULL);
	i = 0;
	while (i < end)
	{
		dst[start + i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_free(char *to_free)
{
	if (to_free)
		free(to_free);
	to_free = NULL;
	return (to_free);
}
