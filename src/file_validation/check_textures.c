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
	// int i = -1;
	// while (++i < 2)
	// 	printf("splited line[%i] = %s\n", i, line_elem[i]);
	if (ft_strncmp_all(line_elem[0], "NO") == 0
		|| ft_strncmp_all(line_elem[0], "SO") == 0
		|| ft_strncmp_all(line_elem[0], "WE") == 0
		|| ft_strncmp_all(line_elem[0], "EA") == 0
		|| ft_strncmp_all(line_elem[0], "F") == 0
		|| ft_strncmp_all(line_elem[0], "C") == 0)
		put_elem_to_struct(line_elem, cub);
	printf("==============================================\n");
	free_char_array(line_elem);
	return (0);
}
/*Add check that elements are in right order!*/
int	valid_elements(int fd, t_cub *cub)
{
	char *line;
	char *trim_line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		return (0);
		// printf("error in get_next_line!\n");
		// return (-1);
	}
	trim_line = ft_strtrim(line, " \t");
	// if (line)
	free(line);
	printf("trim_line = %s\n", trim_line);
	if (ft_strncmp_all(trim_line, "\n") == 0)
		valid_elements(fd, cub);
	else
	{
		check_line(trim_line, cub);
		valid_elements(fd, cub);
	}
	// if (trim_line)
	// 	free(trim_line);
	// print_struct(cub);
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
