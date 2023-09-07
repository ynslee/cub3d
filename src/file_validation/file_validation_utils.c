#include "file_validation.h"

int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
		return (1); //if is map
	return (0); //if its not map
}
