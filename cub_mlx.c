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

int		keys(int keycode, t_parse *cub)
{
	// int moveSpeed;
	// moveSpeed = 0.05;
	ft_putnbr_fd(keycode, 1);
	write(1, "\n", 1);
	if (keycode == 65307 && LINUX == 1)	{							//for linux
		mlx_destroy_window(cub->vars.mlx, cub->vars.win);
		exit(1);
	}
	if (keycode == 53 && APPLE == 1)	{								//for apple
		mlx_destroy_window(cub->vars.mlx, cub->vars.win);
		exit(1);
	}
	// //move forward if no wall in front of you
    // if (keycode == 13)
    // {
    //   if(cub->map[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if (keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if (keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if (keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
	return(0);
}

//123 left 126 up 124 right 125 down
//0 a 13 w 2 d 1 s

int	render_next_frame(t_parse *cub)	
{
	mlx_calc(cub);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	return (1);
}

int draw(t_vars *vars)
{
	int     img_width;
    int		img_height;

	img_width = 1600;
	img_height = 800;
	t_data img;
	img.img = mlx_new_image(vars->mlx, 1600, 800);
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
    printf("!-drawstart=%d-!\n\n\n", drawStart);
    while (cub->vars.y < drawStart)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
        cub->vars.y++;
    }
	while (cub->vars.y < drawEnd)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0xc7adfb);
        cub->vars.y++;
    }
	while (cub->vars.y < cub->ry)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x97f36d);
        cub->vars.y++;
    }
}

void	mlx_calc(t_parse *cub)
{
	while (cub->vars.x < cub->vars.w)
        {
			printf("VARSX=%d\n", cub->vars.x);
			printf("posx=%f && posy=%f && startx= %d && starty= %d\n", cub->vars.posX, cub->vars.posY, cub->startx, cub->starty);
			//calculate ray position and direction
            cub->vars.cameraX = 2 * cub->vars.x / (double)cub->vars.w - 1; //x-coordinate in camera space
            printf("cub->vars.camerax=%f\nplaneX=%f\n",cub->vars.cameraX, cub->vars.planeX);
            cub->vars.rayDirX = cub->vars.dirX + cub->vars.planeX * cub->vars.cameraX;
            cub->vars.rayDirY = cub->vars.dirY + cub->vars.planeY * cub->vars.cameraX;
	        // cub->vars.y = 0;
	        // cub->vars.x = 0;
            cub->vars.mapX = (int)cub->vars.posX;
            cub->vars.mapY = (int)cub->vars.posY;
			printf("cub->vars.raydirx=%f&&cub->vars.raydiry=%f\n", cub->vars.rayDirX, cub->vars.rayDirY);
            // deltaDistX = fabs(1 / cub->vars.rayDirX);
            // deltaDistY = fabs(1 / cub->vars.rayDirY);
			// if (cub->vars.rayDirX == 0 || cub->vars.rayDirY == 0)
			// 	return;
			cub->vars.deltaDistX = (cub->vars.rayDirY == 0) ? 0 : ((cub->vars.rayDirX == 0) ? 1 : fabs(1 / cub->vars.rayDirX));
      		cub->vars.deltaDistY = (cub->vars.rayDirX == 0) ? 0 : ((cub->vars.rayDirY == 0) ? 1 : fabs(1 / cub->vars.rayDirY));
            printf("deltadisx=%f&&deltadisy=%f\n", cub->vars.deltaDistX, cub->vars.deltaDistY);
            //how groot het eerst vakje/stapje is
            if (cub->vars.rayDirX < 0)
            {
                cub->vars.stepX = -1;
                cub->vars.sideDistX = (cub->vars.posX - cub->vars.mapX) * cub->vars.deltaDistX;
            }
            else
            {
                cub->vars.stepX = 1;
                cub->vars.sideDistX = (cub->vars.mapX + 1.0 - cub->vars.posX) * cub->vars.deltaDistX;
            }
            if (cub->vars.rayDirY < 0)
            {
                cub->vars.stepY = -1;
                cub->vars.sideDistY = (cub->vars.posY - cub->vars.mapY) * cub->vars.deltaDistY;
            }
            else
            {
                cub->vars.stepY = 1;
                cub->vars.sideDistY = (cub->vars.mapY + 1.0 - cub->vars.posY) * cub->vars.deltaDistY;
            }
			 printf("cub->vars.rayDirX= %f &&cub->vars.rayDirY= %f \nmpax= %d &&may= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", cub->vars.rayDirX, cub->vars.rayDirY, cub->vars.mapX, cub->vars.mapY, cub->vars.posX, cub->vars.posY, cub->vars.stepX, cub->vars.stepY);
            cub->vars.hit = 0;
			while (cub->vars.hit == 0)
            {
            //jump to next map square, OR in x-direction, OR in y-direction
                if (cub->vars.sideDistX < cub->vars.sideDistY)
                {
                    cub->vars.sideDistX += cub->vars.deltaDistX;
                    cub->vars.mapX += cub->vars.stepX;
                    cub->vars.side = 0;
                }
                else
                {
                   cub->vars.sideDistY += cub->vars.deltaDistY;
                    cub->vars.mapY += cub->vars.stepY;
                    cub->vars.side = 1;
                }
            //Check if ray has hit a wall
                if (cub->map[cub->vars.mapY][cub->vars.mapX] == '1') 
                    cub->vars.hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            printf("qqqqcub->vars.rayDirX= %f &&cub->vars.rayDirY= %f \nmapx= %d &&mapy= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", cub->vars.rayDirX, cub->vars.rayDirY, cub->vars.mapX, cub->vars.mapY, cub->vars.posX, cub->vars.posY, cub->vars.stepX, cub->vars.stepY);
			//exit(0);
            if (cub->vars.side == 0) 
                cub->vars.perpWallDist = (cub->vars.mapX - cub->vars.posX + (1 - cub->vars.stepX) / 2) / cub->vars.rayDirX;
            else
			{
				printf("BORISSSSSSSSSSS\n");
;				cub->vars.perpWallDist = (cub->vars.mapY - cub->vars.posY + (1 - cub->vars.stepY) / 2) / cub->vars.rayDirY;
			}           
            // if (perpWallDist <= 0)
			// 	perpWallDist = 0.01;

            //Calculate height of line to draw on screen
            printf("!-perpWallDist=%f-!\n", cub->vars.perpWallDist);
            cub->vars.lineHeight = (int)(cub->vars.h / cub->vars.perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            printf("!-lineheight=%d-!\n", cub->vars.lineHeight);
            cub->vars.drawStart = (-cub->vars.lineHeight / 2) + (cub->vars.h / 2);
            printf("!-drawstart0=%d-!\n", cub->vars.drawStart);
            if(cub->vars.drawStart < 0)
                cub->vars.drawStart = 0;

            cub->vars.drawEnd = (cub->vars.lineHeight / 2) + (cub->vars.h / 2);
            if(cub->vars.drawEnd >= cub->vars.h)
                cub->vars.drawEnd = cub->vars.h - 1;
           //draw the pixels of the stripe as a vertical line
            ft_verLine(cub->vars.drawStart, cub->vars.drawEnd, cub);
            
            cub->vars.x++;
        }
}

void	ft_mlx(t_parse *cub, char **argv, int argc)
{
	// t_data	img;
	// t_vars	vars;
    //--------------------
    cub->vars.cameraX = 0.0; //x-coordinate in camera space
    cub->vars.rayDirX = 0.0;
    cub->vars.rayDirY = 0.0;
    cub->vars.x = 0;
   	cub->vars.h = cub->ry;
    cub->vars.w = cub->rx;
    cub->vars.posX = (double)cub->startx + 0.5; //0.5
    cub->vars.posY = (double)cub->starty + 0.5;  //x and y start position
    cub->vars.dirX = -1.0;
    cub->vars.dirY = 0.0; //initial direction vector ;fix that with s e wetc.
    cub->vars.planeX = 0.0;
    cub->vars.planeY = -0.66; //the 2d raycaster version of camera plane
       //which box of the map we're in
    cub->vars.mapX = 0;
    cub->vars.mapY = 0;

      //length of ray from current position to next x or y-side
      cub->vars.sideDistX = 0.0;
      cub->vars.sideDistY = 0.0;

       //length of ray from one x or y-side to next x or y-side
      cub->vars.deltaDistX = 0.0;
      cub->vars.deltaDistY = 0.0;
      cub->vars.perpWallDist;

    cub->vars.lineHeight = 0;
    cub->vars.drawStart = 0;
    cub->vars.drawEnd = 0;

      //what direction to step in x or y-direction (either +1 or -1)
      cub->vars.stepX = 0;
      cub->vars.stepY = 0;

      cub->vars.hit = 0; //was there a wall hit?
      cub->vars.side = 0; //was a NS or a EW wall hit?

	// img_width = 1000;
	// img_height = 1000;
	
	cub->vars.mlx = mlx_init();
	cub->vars.win = mlx_new_window(cub->vars.mlx, 1600, 800, "🄲🅄🄱3🄳"); //fix window bitch
	cub->img.img = mlx_new_image(cub->vars.mlx, 1600, 800);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length,&cub->img.endian);
	cub->vars.y = 0;
    cub->vars.x = 0;
	mlx_calc(cub);
//         while (cub->vars.x < w)
//         {
// 			printf("VARSX=%d\n", cub->vars.x);
// 			printf("posx=%f && posy=%f && startx= %d && starty= %d\n", posX, posY, cub->startx, cub->starty);
// 			//calculate ray position and direction
//             cameraX = 2 * cub->vars.x / (double)w - 1; //x-coordinate in camera space
//             printf("camerax=%f\nplaneX=%f\n",cameraX, planeX);
//             rayDirX = dirX + planeX * cameraX;
//             rayDirY = dirY + planeY * cameraX;
// 	        // cub->vars.y = 0;
// 	        // cub->vars.x = 0;
//             mapX = (int)posX;
//             mapY = (int)posY;
// 			printf("raydirx=%f&&raydiry=%f\n", rayDirX, rayDirY);
//             // deltaDistX = fabs(1 / rayDirX);
//             // deltaDistY = fabs(1 / rayDirY);
// 			// if (rayDirX == 0 || rayDirY == 0)
// 			// 	return;
// 			deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
//       		deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
//             printf("deltadisx=%f&&deltadisy=%f\n", deltaDistX, deltaDistY);
//             //how groot het eerst vakje/stapje is
//             if (rayDirX < 0)
//             {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             }
//             else
//             {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if (rayDirY < 0)
//             {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             }
//             else
//             {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }
// 			 printf("rayDirX= %f &&rayDirY= %f \nmpax= %d &&may= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", rayDirX, rayDirY, mapX, mapY, posX, posY, stepX, stepY);
//             hit = 0;
// 			while (hit == 0)
//             {
//             //jump to next map square, OR in x-direction, OR in y-direction
//                 if (sideDistX < sideDistY)
//                 {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 }
//                 else
//                 {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//             //Check if ray has hit a wall
//                 if (cub->map[mapY][mapX] == '1') 
//                     hit = 1;
//             }
//             //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
//             printf("qqqqrayDirX= %f &&rayDirY= %f \nmapx= %d &&mapy= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", rayDirX, rayDirY, mapX, mapY, posX, posY, stepX, stepY);
// 			//exit(0);
//             if (side == 0) 
//                 perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//             else
// 			{
// 				printf("BORISSSSSSSSSSS\n");
// ;				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
// 			}           
//             // if (perpWallDist <= 0)
// 			// 	perpWallDist = 0.01;

//             //Calculate height of line to draw on screen
//             printf("!-perpWallDist=%f-!\n", perpWallDist);
//             lineHeight = (int)(h / perpWallDist);

//             //calculate lowest and highest pixel to fill in current stripe
//             printf("!-lineheight=%d-!\n", lineHeight);
//             drawStart = (-lineHeight / 2) + (h / 2);
//             printf("!-drawstart0=%d-!\n", drawStart);
//             if(drawStart < 0)
//                 drawStart = 0;

//             drawEnd = (lineHeight / 2) + (h / 2);
//             if(drawEnd >= h)
//                 drawEnd = h - 1;
//            //draw the pixels of the stripe as a vertical line
//             ft_verLine(drawStart, drawEnd, cub);
            
//             cub->vars.x++;
//         }


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
	mlx_key_hook(cub->vars.win, keys, cub);
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