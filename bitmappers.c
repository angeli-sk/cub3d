#include "./libft/libft.h"
#include "cub3d.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
//#include <sys/stat.h>

void	bitmap(t_parse *cub)
{
	int fd;
	int padding;
	char *color;
	char header[54];
	int y;
	int x;

	y = cub->ry - 1;
	x = 0;
	//cub->vars.mlx = mlx_init();
	cub->img.img = mlx_new_image(cub->vars.mlx, cub->rx, cub->ry);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length,&cub->img.endian);
	mlx_calc(cub);
	mlx_sprite(cub);
	
	
	//cub->vars.win = mlx_new_window(cub->vars.mlx, cub->rx, cub->ry, "screenshot");
	//mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	//mlx_loop(cub->vars.mlx);
	ft_bzero(header, 54);
	fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0777); //check
	header[0] = 'B';
	header[1] = 'M';
	padding = 4 - ((cub->rx * 3) % 4);
	if (padding == 4)
		padding = 0;
	header[2] = ((cub->rx * (cub->ry + padding) * 3) + 54);
	//if(padding != 0)
	header[6] = 0;
	header[10] = 54;
	header[14] = 40;
	// header[18] = cub->rx;
	// header[24] = cub->ry;
	ft_memcpy(header + 18, &cub->rx, 4);
	ft_memcpy(header + 22, &cub->ry, 4);
	header[26] = 1;
	header[28] = 24;
	int z = write(fd, header, 54);

	printf("y=%d\n", y);
	while(y >= 0)
	{
		x = 0;
		while (x < cub->rx)
		{
			color = (cub->img.addr + ((cub->img.line_length * y) + (x * (cub->img.bits_per_pixel / 8))));
			//printf("coolr=%x\n", (int)color);
			write(fd, color, 3);
			//printf("p=%d ", p);
			x++;
		}
		write(fd, "/0/0/0", padding);
		y--;
	}
	printf("z=%d\n", z);
	close(fd);
	exit(0);
}