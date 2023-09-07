#include "file_validation.h"

// static void	print_struct(t_cub *cub)
// {
// 	// printf("*****************************\n");
// 	if (cub->no)
// 		printf("cub->no = %s\n", cub->no);
// 	if (cub->so)
// 		printf("cub->so = %s\n", cub->so);
// 	if (cub->we)
// 		printf("cub->we = %s\n", cub->we);
// 	if (cub->ea)
// 		printf("cub->ea = %s\n", cub->ea);
// 	if (cub->f_color)
// 		printf("cub->f_color = %s\n", cub->f_color);
// 	if (cub->c_color)
// 		printf("cub->c_color = %s\n", cub->c_color);
// 	printf("*****************************\n");
// }

void	put_elem_to_struct(char **element, t_cub *cub)
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
	// free_char_array(element);
}

int	check_line(char *line, t_cub *cub)
{
	char **line_elem;

	line_elem = ft_split(line, ' ');
	free(line);
	int i = -1;
	while (++i < 2)
		// printf("splited line[%i] = %s\t%p\n", i, line_elem[i], line_elem[i]);
	if (ft_strncmp_all(line_elem[0], "NO") == 0
		|| ft_strncmp_all(line_elem[0], "SO") == 0
		|| ft_strncmp_all(line_elem[0], "WE") == 0
		|| ft_strncmp_all(line_elem[0], "EA") == 0
		|| ft_strncmp_all(line_elem[0], "F") == 0
		|| ft_strncmp_all(line_elem[0], "C") == 0)
		put_elem_to_struct(line_elem, cub);
	// printf("==============================================\n");
	cub->id_flag++;
	// printf("cub->id_flag = %i\n", cub->id_flag);
	free_char_array(line_elem);
	return (0);
}
/*Add check that elements are in right order!*/
int	valid_elements(int fd, t_cub *cub)
{
	(void)cub;
	char *line;
	char *trim_line;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6)
		{
			trim_line = ft_strtrim(line, " \t");
			// printf("trim_line = %s\t%p\n", trim_line, trim_line);
			check_line(trim_line, cub);
			// free(trim_line);
		}
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag == 6)
		{
			if (!cub->map_str)
				cub->map_str = ft_strdup(line);
			else
				cub->map_str = ft_strjoin_gnl(cub->map_str, line);
		}
		// free(line);
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
