#include "file_validation.h"

int	valid_file(char *file_name)
{
	char *ret;

	ret = ft_strnstr(file_name, ".cub", ft_strlen(file_name));
	if (ret == NULL)
		return (-1);
	if (ft_strlen(ret) != 4)
		return (-1);
	if (open(file_name, O_RDONLY) == -1)
		return (-1);
	return (0);
}
