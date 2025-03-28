char	*get_next_line(int	fd)
{
	int			i;
	char		*new_line;
	static char	*inreading[OPEN_MAX + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) <= 0)
		return (ft_free(inreading[fd]));
	if (!inreading)
		inreading[fd] = NULL;
/*	i = 0;
	if (inreading[fd])
	{
		while (inreading[fd][i])
		{
			if (inreading[fd][i] == "\n")
			{
				new_line = if_new_line(inreading[fd], inreading[fd], 0, i);
				if (!new_line)
					return (ft_free(inreading[fd]));
				if (i < ft_strlen(inreading[fd]))
				{
					inreading[fd] = if_new_line(inreading[fd], &inreading[fd][i], 0, ft_strlen(inreading[fd]) - i);
					if (!inreading[fd])
						return (ft_free(new_line);
				}
				return (new_line);
			}
			i++;
		}
	}*/
	new_line = gnl_read(fd, inreading[fd], 0);
/*	if (inreading[fd] && new_line)
		new_line = gnl_cpy(new_line, inreading[fd], 0, i);*/
	return (new_line);
}

char	*gnl_read(int fd, char *inreading, int lenght)
{
	int		i;
	int		byte_read;
	char	*new_line;
	char	buffer[BUFFER_SIZE];

	if (lenght == 0 && inreading)
	{
		buffer = inreading;
		byte_read = ft_strlen(inreading);
	}
	else
		byte_read = read(fd, buffer, BUFFER_SIZE);
	if (lenght != 0 && byte_read < 0)
		return (ft_free(inreading));
	i = 0;
	while (i < byte_read)
	{
		if (buffer[i] == "\n")
		{
			new_line = if_new_line(new_line, buffer, lenght, lenght + i);
			if (!new_line)
				return (ft_free(inreading));
			if (i != byte_read - 1)
			{
				inreading = if_new_line(inreading, &buffer[i], 0, byte_read - i);
				if (!inreading)
					return (ft_free(new_line));
			}
			return (new_line);
		}
		i++;
	}
	new_line = gnl_read(fd, inreading, lenght + byte_read);
	return (gnl_cpy(new_line, buffer, lenght, byte_read));
}

char	*if_new_line(char *dst, char *src, int start, int end)
{
	dst = (char *) malloc(sizeof(char) * (end + 1));
	if (!dst)
		return (NULL);
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
