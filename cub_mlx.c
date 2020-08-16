#include "./cub3d.h"
#define LINUX 0
#define APPLE 0
#ifdef __linux__
#undef LINUX 
# define LINUX 1
#else
#undef APPLE
# define APPLE 1
#endif
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd(-2, fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		keys(int keycode, t_vars *vars)
{
	ft_putnbr_fd(keycode, 1);
	write(1, "\n", 1);
	if (keycode == 65307 && LINUX == 1)	{							//for linux
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	if (keycode == 9 && APPLE == 1)	{								//for apple
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return(0);
}

int	render_next_frame()	
{
	return (0);
}

int draw(t_vars *vars)
{
	int     img_width;
    int		img_height;

	img_width = 1000;
	img_height = 1000;
	t_data img;
	img.img = mlx_new_image(vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								&img.line_length,&img.endian);
	img.img = mlx_xpm_file_to_image(vars->mlx, "./yolanda.xpm", &img_width, &img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

double  ft_abs(double n)
{
    if (n < 0)
        n = n * -1;
    return (n);
}

void    ft_verLine(int  drawStart, int   drawEnd, t_parse *cub)
{
    //int y;

    cub->vars.y = 0;
    printf("!-drawstart=%d-!\n", drawStart);
    while (cub->vars.y < drawStart)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
        cub->vars.y++;
    }
}

void	ft_mlx(t_parse *cub, char **argv, int argc)
{
	// t_data	img;
	// t_vars	vars;
	int     img_width;
	int     img_height;
    //--------------------
    double cameraX = 0.0; //x-coordinate in camera space
    double rayDirX = 0.0;
    double rayDirY = 0.0;
    int x;
    int w;
    int h;
    x = 0;
    h = cub->ry;
    w = cub->rx;
    double posX = (double)cub->startx;
    double posY = (double)cub->starty;  //x and y start position
    double dirX = 0.0;
    double dirY = -1.0; //initial direction vector ;fix that with s e wetc.
    double planeX = 0.66;
    double planeY = 0.0; //the 2d raycaster version of camera plane
       //which box of the map we're in
    int mapX = 0;
    int mapY = 0;

      //length of ray from current position to next x or y-side
      double sideDistX = 0.0;
      double sideDistY = 0.0;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = 0.0;
      double deltaDistY = 0.0;
      double perpWallDist;

    int lineHeight = 0;
    int drawStart = 0;
    int drawEnd = 0;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX = 0;
      int stepY = 0;

      int hit = 0; //was there a wall hit?
      int side = 0; //was a NS or a EW wall hit?

	img_width = 1000;
	img_height = 1000;
	cub->vars.mlx = mlx_init();
	cub->vars.win = mlx_new_window(cub->vars.mlx, 1920, 1080, "🄲🅄🄱3🄳");
	cub->img.img = mlx_new_image(cub->vars.mlx, 1920, 1080);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length,&cub->img.endian);
	cub->vars.y = 0;
    cub->vars.x = 0;
        while (cub->vars.x < w)
        {//calculate ray position and direction
            cameraX = 2 * cub->vars.x / (double)w - 1; //x-coordinate in camera space
            printf("camerax=%f\nplaneX=%f\n",cameraX, planeX);
            rayDirX = dirX + planeX * cameraX;
            rayDirY = dirY + planeY * cameraX;
	        // cub->vars.y = 0;
	        // cub->vars.x = 0;
            mapX = (int)posX;
            mapY = (int)posY;
            deltaDistX = fabs(1 / rayDirX);
            deltaDistY = fabs(1 / rayDirY);
            printf("deltadisx=%f&&deltadisy=%f\n", deltaDistX, deltaDistY);
            //how groot het eerst vakje/stapje is
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            while (hit == 0)
            {
            //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
            //Check if ray has hit a wall
                if (cub->map[mapY][mapX] == '1') 
                    hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            printf("rayDirX=%f&&rayDirY=%f\nmpax=%d&&may=%d\nposX=%f&&posY=%f\nstepx=%d&&stepy=%d\n", rayDirX, rayDirY, mapX, mapY, posX, posY, stepX, stepY);
            if (side == 0) 
                perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else           
                perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            //Calculate height of line to draw on screen
            printf("!-perpWallDist=%f-!\n", perpWallDist);
            lineHeight = (int)(h / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            printf("!-linehieght=%d-!\n", lineHeight);
            drawStart = (-lineHeight / 2) + (h / 2);
            printf("!-drawstart0=%d-!\n", drawStart);
            if(drawStart < 0)
                drawStart = 0;

            drawEnd = (lineHeight / 2) + (h / 2);
            if(drawEnd >= h)
                drawEnd = h - 1;
           //draw the pixels of the stripe as a vertical line
            ft_verLine(drawStart, drawEnd, cub);
            
            cub->vars.x++;
        }


    // while (cub->vars.y < 1080)
	// {
	// 	cub->vars.x = 0;
	// 	while (cub->vars.x < 1920)
	// 	{
	// 		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
	// 		cub->vars.x++;
	// 	}
	// 	cub->vars.y++;
	// }
	mlx_key_hook(cub->vars.win, keys, &cub->vars);
	// cub->vars.y = 200;
	// while (cub->vars.y < 700)
	// {
	// 	cub->vars.x = 500;
	// 	while (cub->vars.x < 1000)
	// 	{
	// 		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0xf8c275);
	// 		cub->vars.x++;
	// 	}
	// 	cub->vars.y++;
	// }
	// cub->vars.y = 400;
	// while (cub->vars.y < 600)
	// {
	// 	cub->vars.x = 800;
	// 	while (cub->vars.x < 1000)
	// 	{
	// 		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0xc7adfb);
	// 		cub->vars.x++;
	// 	}
	// 	cub->vars.y++;
	// }
	// cub->vars.y = 300;
	// cub->vars.xmax = 1000;
	// while (cub->vars.y < 600)
	// {
	// 	cub->vars.x = 500;
	// 	while (cub->vars.x < cub->vars.xmax)
	// 	{
	// 		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x97f36d);
	// 		cub->vars.x++;
	// 	}
	// 	if(cub->vars.xmax > 0)
	// 		cub->vars.xmax--;
	//  	cub->vars.y++;
	// }
	//mlx_loop_hook(cub->vars.mlx, draw, &cub->vars.mlx);
    mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	mlx_loop(cub->vars.mlx);
}