
#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*map_line;
	int		height;

	height = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (-1);
		line = get_next_line(fd);
		map_line = ft_strdup(line);
		free(line);
		while (++height)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			map_line = ft_strjoin_gnl(map_line, line);
			free(line);
		}
		if (map_check(map_line) < 0)
			printf("map_validation_error\n");
		free(map_line);
	}
	return (0);
}
