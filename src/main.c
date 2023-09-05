#include "cub3d.h"

int main(int argc, char **argv)
{
	int	fd;

	if (argc == 2)
	{
		fd = valid_file(argv[1]);
		if (fd == -1)
			printf("Invalid file\n");
		valid_elements(fd);
		// if (valid_elements(fd) == -1)
		// 	printf("Elements not valid\n");
	}
	return (0);
}
