#include "file_validation.h"

static void	put_elem_to_struct(char **element, t_cub *cub)
{
	if (ft_strncmp_all(element[0], "NO") == 0)
		cub->no = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "SO") == 0)
		cub->so = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "WE") == 0)
		cub->we = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "EA") == 0)
		cub->ea = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "F") == 0)
		cub->f_color = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "C") == 0)
		cub->c_color = ft_strdup(element[1]);
}

static int	check_line(char *line, t_cub *cub)
{
	char	**line_elem;
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t");
	line_elem = ft_split(trim_line, ' ');
	if (ft_strncmp_all(line_elem[0], "NO") == 0
		|| ft_strncmp_all(line_elem[0], "SO") == 0
		|| ft_strncmp_all(line_elem[0], "WE") == 0
		|| ft_strncmp_all(line_elem[0], "EA") == 0
		|| ft_strncmp_all(line_elem[0], "F") == 0
		|| ft_strncmp_all(line_elem[0], "C") == 0)
		put_elem_to_struct(line_elem, cub);
	cub->id_flag++;
	free(trim_line);
	free_char_array(line_elem);
	return (0);
}

int	valid_elements(int fd, t_cub *cub)
{
	char *line;

	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6 && !is_map(line))
			check_line(line, cub);
		else if (is_map(line) && cub->id_flag != 6)
		{
			printf("Elements in wrong order!\n");
			free(line);
			return (-1);
		}
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag == 6)
		{
			if (!cub->map_str)
				cub->map_str = ft_strdup(line);
			else
				cub->map_str = ft_strjoin_gnl(cub->map_str, line);
		}
		free(line);
	}
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
