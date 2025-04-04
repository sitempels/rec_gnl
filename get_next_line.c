#include "get_next_line.h"

static char	*gnl_read(int fd, char *inreading, int lenght);
static char	*if_new_line(char *inreading, char *src, int length, int n);
static char	*gnl_cpy(char *dst, char *src, int end);
static char	*ft_free(int fd, char **to_free);
static int	ft_strlen(const char *str);

char	*get_next_line(int	fd)
{
	int			i;
	char		*new_line;
	char		*new_stash;
	static char	*stash[256 + 1];

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free(fd, stash));
	i = 0;
	if (!stash[fd])
		return (gnl_read(fd, stash[fd], i));
	while (stash[fd][i] != '\n')
		i++;	
	if (stash[fd][i] == '\n')
	{
		new_line = (char *) malloc(sizeof(char) * (i + 1));
		if (!new_line)
			return (ft_free(fd, stash));
		new_line[i + 1] = '\0';
		stash[fd] = if_new_line(new_line, stash[fd], i, ft_strlen(stash[fd]));
		if (i < ft_strlen(stash[fd]) - 1 && !stash[fd])
			return (ft_free(0, &new_line));
		return (new_line);
	}
	new_stash = stash[fd];
	stash[fd] = NULL;
	new_line = gnl_read(fd, stash[fd], i);
	new_line = gnl_cpy(new_line, new_stash, i);
	free(new_stash);
	return (new_line);
}

static char	*gnl_read(int fd, char *stash, int length)
{
	int		i;
	int		byte_read;
	char	*new_line;
	char	buffer[BUFFER_SIZE];

	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (length == 0 && byte_read < 0)
		return (NULL);
	i = 0;
	while (i < byte_read && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		new_line = (char *) malloc(sizeof(char) * (length + i + 1));
		if (!new_line)
			return (NULL);
		new_line[length + i + 1] = '\0';
		stash = if_new_line(&new_line[length], buffer, i, byte_read);
		if (i < byte_read - 1 && !stash)
			return (ft_free(0, &new_line));
		return (new_line);
	}
	new_line = gnl_read(fd, stash, length + byte_read);
	gnl_cpy(&new_line[length], buffer, byte_read);
	return (new_line);
}

static char	*if_new_line(char *new_line, char *src, int n, int length)
{
	char	*stash;

	gnl_cpy(new_line, src, n);
	stash = NULL;
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

	if (!src)
		return (NULL);
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
	if (fd == 0)
	{
		free((*to_free));
		(*to_free) = NULL;
	}
	if (to_free[fd])
	{	free(to_free[fd]);
		to_free[fd] = NULL;
	}
	return (NULL);
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
