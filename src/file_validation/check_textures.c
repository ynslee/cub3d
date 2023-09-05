#include "../../include/file_validation.h"

int	valid_file(char *file_name)
{
	if (ft_strnstr(file_name, ".cub", ft_strlen(file_name)) == NULL)
		return (-1);
	return (0);
}
