
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
	if (!stash[fd])
		return (gnl_read(fd, stash[fd], i));
	while (stash[fd][i])
	{
		if (stash[fd][i] == "\n")
			new_line = (char *) malloc(sizeof(char) * (i + 1));
			if (!new_line)
				return (ft_free(fd, &stash));
			new_line[i + 1] = '\0';
			stash[fd] = if_new_line(&new_line[i], stash[fd], i, ft_strlen(stash[fd]));
			if (i < ft_strlen(stash[fd]) - 1 && !stash)
				return (free(new_line);
			return (new_line);
		}
		i++;
	}
	new_stash = stash[fd];
	stash[fd] = NULL;
	new_line = gnl_read(fd, stash[fd], i);
	new_line = gnl_cpy(new_line, new_stash, 0, i);
	free(new_stash);
	return (new_line);
}

static char	*gnl_read(int fd, char *stash, int lenght)
{
	int		i;
	int		byte_read;
	char	*new_line;
	char	buffer[BUFFER_SIZE];

	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (lenght == 0 && byte_read < 0)
		return (NULL);
	i = 0;
	while (i < byte_read)
	{
		if (buffer[i] == "\n")
		{
			new_line = (char *) malloc(sizeof(char) * (length + n + 1));
			if (!new_line)
				return (NULL);
			new_line[length + n + 1] = '\0';
			stash = if_new_line(&new_line[length], buffer, i, byte_read);
			if (i < byte_read - 1 && !stash)
				return (free(new_line);
			return (new_line);
		}
		i++;
	}
	new_line = gnl_read(fd, inreading, length + byte_read);
	gnl_cpy(&new_line[length], buffer, byte_read);
	return (new_line);
}

static char	*if_new_line(char *new_line, char *src, int n, int length)
{
	char	*stash;

	gnl_cpy(new_line, src, n);
	if (n < length - 1)
	{
		stash = (char *) malloc(sizeof(char) * (length - n + 1));
		if (!stash)
			return (NULL);
		stash[length - n + 1] = '\0';
		stash = gnl_cpy(stash, &src[n + 1], length - n);
	}
	return (stash);
}

static char	*gnl_cpy(char *dst, char *src, int end)
{
	int	i;

	if (!dst)
		return (NULL);
	i = 0;
	while (i < end)
	{
		dst[i] = src[i];
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
