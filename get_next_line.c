
static char	*gnl_read(int fd, char *inreading, int lenght);
static char	*if_new_line(char *inreading, char *src, int length, int n);
static char	*gnl_cpy(char *dst, char *src, int start, int end);
static char	*ft_free(int fd, char **to_free);

char	*get_next_line(int	fd)
{
	int			i;
	char		*new_line;
	char		*new_stash;
	static char	*stash[OPEN_MAX + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) <= 0)
		return (ft_free(fd, stash));
	i = 0;
	if (stash[fd])
	{
		while (stash[fd][i])
		{
			if (stash[fd][i] == "\n")
			{	new_line = if_new_line(stash[fd], stash[fd], 0, i);
				if (i < ft_strlen(stash[fd]))
				{
					stash = if_new_line(stash, &stash[i + 1], 0, ft_strlen(stash[fd]));
					if (!stash)
						return (NULL);
				}
				return (new_line);
			}
			i++;
		}
		new_stash = stash[fd];
		stash[fd] = NULL;
		new_line = gnl_read(fd, stash[fd], i);
		new_line = gnl_cpy(new_line, new_stash, 0, i);
		free(new_stash);
	}
	else
		new_line = gnl_read(fd, stash[fd], i);
	return (new_line);
}

static char	*gnl_read(int fd, char *inreading, int lenght)
{
	int		i;
	int		byte_read;
	char	*new_line;
	char	buffer[BUFFER_SIZE];

	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (lenght == 0 && byte_read < 0)
		return (ft_free(fd, &inreading));
	i = 0;
	while (i < byte_read)
	{
		if (buffer[i] == "\n")
		{
			new_line = if_new_line(inreading, buffer, length, i);
			if (!new_line)
				return (ft_free(fd, &inreading));
			if (i < byte_read - 1)
			{
				inreading = if_new_line(inreading, &buffer[i + 1], 0, byte_read - i);
				if (!inreading)
					return (ft_free(fd, &new_line));
			}
		}
		i++;
	}
	new_line = gnl_read(fd, inreading, length + byte_read);
	return (gnl_cpy(new_line, buffer, length, byte_read));
}

static char	*if_new_line(char *inreading, char *src, int length, int n)
{
	char	*new_line;

	new_line = (char *) malloc(sizeof(char) * (length + n + 1));
	if (!new_line)
		return (NULL);
	new_line[length + n + 1] = '\0';
	new_line = gnl_cpy(new_line, src, length, n);
	return (new_line);
}

static char	*gnl_cpy(char *dst, char *src, int start, int end)
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

static char	*ft_free(int fd, char **to_free)
{
	if (fd < 0)
		fd = -1 * fd;
	if (to_free[fd])
		free(to_free[fd]);
	to_free[fd] = NULL;
	return (to_free[fd]);
}
