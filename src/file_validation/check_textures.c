#include "file_validation.h"

int	valid_elements(int fd)
{
	char *line;

	line = get_next_line(fd);
	// check  if line is empty -> read next line
	// if not empty go check if line is valid
	printf("line = %s\n", line);
	return (0);
}

int	valid_file(char *file_name)
{
	char	*ret;
	int		fd;

	ret = ft_strnstr(file_name, ".cub", ft_strlen(file_name));
	if (ret == NULL)
		return (-1);
	if (ft_strlen(ret) != 4)
		return (-1);
	fd = open(file_name, O_RDONLY);
		return (fd);
	return (fd);
}
