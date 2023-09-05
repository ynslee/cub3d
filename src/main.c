#include "cub3d.h"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (valid_file(argv[1]) == -1)
			printf("Invalid file\n");
	}
	return (0);
}
