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

int   destroy(t_parse *cub)
{
    mlx_destroy_window(cub->vars.mlx, cub->vars.win);
	exit(0);
    return (1);
}
//apple
//123 left 126 up 124 right 125 down
//0 a 13 w 2 d 1 s
//ubuntu
//a 97 w 119 d 100 s 115
int     key_pressed(int keycode, t_parse *cub)
{
    if ((keycode == 65307 && LINUX == 1) || (keycode == 53 && APPLE == 1))
    {							//for linux
		destroy(cub);
	}//printf("posX=%f && posY =%f dirX=%f && dirY=%f\n", cub->vars.posX, cub->vars.posY, cub->vars.dirX, cub->vars.dirY);
	//move forward if no wall in front of you
    if ((keycode == 13 && APPLE == 1) || (keycode == 119 && LINUX == 1))
    {//printf("check1\n");
        cub->vars.walksies[up] = 1;
    }
    if ((keycode == 1 && APPLE == 1) || (keycode == 115 && LINUX == 1))
    {
        cub->vars.walksies[down] = 1;
    }
     if ((keycode == 123 && APPLE == 1) || (keycode == 65361 && LINUX == 1))
    {
        cub->vars.walksies[turn_l] = 1;
    }
     if ((keycode == 124 && APPLE == 1) || (keycode == 65363 && LINUX == 1))
    {
        cub->vars.walksies[turn_r] = 1;
    }
    if ((keycode == 2 && APPLE == 1) || (keycode == 100 && LINUX == 1))
    {
        cub->vars.walksies[right] = 1;
    }
    if ((keycode == 0 && APPLE == 1) ||(keycode == 97 && LINUX == 1))
    {
        cub->vars.walksies[left] = 1;
    }
	return(0);
}
int     key_released(int keycode, t_parse *cub)
{
    if ((keycode == 65307 && LINUX == 1) || (keycode == 53 && APPLE == 1))
    {							//for linux
		destroy(cub);
	}//printf("posX=%f && posY =%f dirX=%f && dirY=%f\n", cub->vars.posX, cub->vars.posY, cub->vars.dirX, cub->vars.dirY);
	//move forward if no wall in front of you
    if ((keycode == 13 && APPLE == 1) || (keycode == 119 && LINUX == 1))
    {//printf("check2\n");
        cub->vars.walksies[up] = 0;
    }
    if ((keycode == 1 && APPLE == 1) || (keycode == 115 && LINUX == 1))
    {
        cub->vars.walksies[down] = 0;
    }
     if ((keycode == 123 && APPLE == 1) || (keycode == 65361 && LINUX == 1))
    {
        cub->vars.walksies[turn_l] = 0;
    }
     if ((keycode == 124 && APPLE == 1) || (keycode == 65363 && LINUX == 1))
    {
        cub->vars.walksies[turn_r] = 0;
    }
    if ((keycode == 2 && APPLE == 1) || (keycode == 100 && LINUX == 1))
    {
        cub->vars.walksies[right] = 0;
    }
    if ((keycode == 0 && APPLE == 1) ||(keycode == 97 && LINUX == 1))
    {
        cub->vars.walksies[left] = 0;
    }
	return(0);
}

// int		keys(int keycode, t_parse *cub)
// {
// 	cub->vars.moveSpeed = 0.05;
//     cub->vars.rotSpeed = 0.05;
//     cub->vars.oldDirX = 0;
//     cub->vars.oldPlaneX = 0;
//     printf("walksies0=%d\n && lemaoX=%d\n && lemaoY=%d\n", cub->vars.walksies[up], ((int)(cub->vars.posX + cub->vars.dirX * cub->vars.moveSpeed)), ((int)(cub->vars.posY + cub->vars.dirY * cub->vars.moveSpeed)));
// 	ft_putnbr_fd(keycode, 1);
// 	write(1, "\n", 1);
// 	if ((keycode == 65307 && LINUX == 1) || (keycode == 53 && APPLE == 1))
//     {							//for linux
// 		destroy(cub);
// 	}//printf("posX=%f && posY =%f dirX=%f && dirY=%f\n", cub->vars.posX, cub->vars.posY, cub->vars.dirX, cub->vars.dirY);
// 	//move forward if no wall in front of you
//     if ((keycode == 13 && APPLE == 1) || (keycode == 119 && LINUX == 1))
//     {
//       if(cub->map[(int)(cub->vars.posY)][(int)(cub->vars.posX + cub->vars.dirX * cub->vars.moveSpeed)] != '1')
//         {
//             cub->vars.posX += cub->vars.dirX * cub->vars.moveSpeed;
//         }//printf("lemmmmau\n");
//         //printf("BORIS2ND\n");
//       if(cub->map[(int)(cub->vars.posY + cub->vars.dirY * cub->vars.moveSpeed)][(int)(cub->vars.posX)] != '1')
//         cub->vars.posY += cub->vars.dirY * cub->vars.moveSpeed;
//     }
//     //move backwards if no wall behind you
//     if ((keycode == 1 && APPLE == 1) || (keycode == 115 && LINUX == 1))
//     {
//       if(cub->map[(int)(cub->vars.posY)][(int)(cub->vars.posX - cub->vars.dirX * cub->vars.moveSpeed)] != '1')
//         cub->vars.posX -= cub->vars.dirX * cub->vars.moveSpeed;
//       if(cub->map[(int)(cub->vars.posY - cub->vars.dirY * cub->vars.moveSpeed)][(int)(cub->vars.posX)] != '1')
//         cub->vars.posY -= cub->vars.dirY * cub->vars.moveSpeed;
//     }
//     //rotate to the rleft
//     if ((keycode == 2 && APPLE == 1) || (keycode == 37 && LINUX == 1))
//     {
//       //both camera direction and camera plane must be rotated
//       cub->vars.oldDirX = cub->vars.dirX;
//       cub->vars.dirX = cub->vars.dirX * cos(-cub->vars.rotSpeed) - cub->vars.dirY * sin(-cub->vars.rotSpeed);
//       cub->vars.dirY = cub->vars.oldDirX * sin(-cub->vars.rotSpeed) + cub->vars.dirY * cos(-cub->vars.rotSpeed);
//       cub->vars.oldPlaneX = cub->vars.planeX;
//       cub->vars.planeX = cub->vars.planeX * cos(-cub->vars.rotSpeed) - cub->vars.planeY * sin(-cub->vars.rotSpeed);
//       cub->vars.planeY = cub->vars.oldPlaneX * sin(-cub->vars.rotSpeed) + cub->vars.planeY * cos(-cub->vars.rotSpeed);
//     }
//     //rotate to the lright
//     if ((keycode == 0 && APPLE == 1) ||(keycode == 39 && LINUX == 1))
//     {
//       //both camera direction and camera plane must be rotatedWil jij jouw onderzoeksskills inzetten om ons en de wereld te vertellen wat de effecten zijn van private financieringsvormen op (private) scholing en de ontwikkelingskansen van kwetsbare studenten? Laat van je horen via de link in de comments!
//       cub->vars.oldDirX = cub->vars.dirX;
//       cub->vars.dirX = cub->vars.dirX * cos(cub->vars.rotSpeed) - cub->vars.dirY * sin(cub->vars.rotSpeed);
//       cub->vars.dirY = cub->vars.oldDirX * sin(cub->vars.rotSpeed) + cub->vars.dirY * cos(cub->vars.rotSpeed);
//       cub->vars.oldPlaneX = cub->vars.planeX;
//       cub->vars.planeX = cub->vars.planeX * cos(cub->vars.rotSpeed) - cub->vars.planeY * sin(cub->vars.rotSpeed);
//       cub->vars.planeY = cub->vars.oldPlaneX * sin(cub->vars.rotSpeed) + cub->vars.planeY * cos(cub->vars.rotSpeed);
//     }

// 	return(0);
// }
//apple
//123 left 126 up 124 right 125 down
//0 a 13 w 2 d 1 s
//ubuntu
//a 97 w 119 d 100 s 115
// void    ft_verLine(int  drawStart, int   drawEnd, t_parse *cub)
// {
//     //int y;

//     cub->vars.y = 0;
//     // printf("5verline!-drawstart=%d && drawend=%i && ry=%d !\n\n\n",cub->vars.drawStart, cub->vars.drawEnd, cub->ry);
//     while (cub->vars.y < drawStart)
//     {
//         my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
//         cub->vars.y++;
//     }
// 	while (cub->vars.y < drawEnd)
//     {
//         my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, cub->vars.colorwall);//0xc7adfb
//         cub->vars.y++;
//     }
// 	while (cub->vars.y < cub->ry)
//     {
//         my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x97f36d);
//         cub->vars.y++;
//     }
// }

void    ft_verLine(int  drawStart, int   drawEnd, t_parse *cub)
{
    //int y;
     cub->vars.y = 0;
	 int  tex;
     char *test;
     unsigned int color;

	tex = 0;
		if (cub->vars.side == 1 && cub->vars.rayDirY > 0)
	   		tex = 0;
		if (cub->vars.side == 1 && cub->vars.rayDirY < 0)
			tex = 1;
		if (cub->vars.side == 0 && cub->vars.rayDirX > 0)
			tex = 2;
		if (cub->vars.side == 0 && cub->vars.rayDirX < 0)
			tex = 3;
    while (cub->vars.y < drawStart)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
        cub->vars.y++;
    }
      //calculate value of wallX
      if (cub->vars.side == 0)
        cub->vars.wallX = cub->vars.posY + cub->vars.perpWallDist * cub->vars.rayDirY;
      else
        cub->vars.wallX = cub->vars.posX + cub->vars.perpWallDist * cub->vars.rayDirX;
      cub->vars.wallX -= floor((cub->vars.wallX));

      //x coordinate on the texture
      cub->vars.texX = (int)(cub->vars.wallX * (double)(cub->tex[tex].x));//change 0 to variable
      if(cub->vars.side == 0 && cub->vars.rayDirX > 0)
        cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;
      if(cub->vars.side == 1 && cub->vars.rayDirY < 0)
        cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;

           // How much to increase the texture coordinate per screen pixel
      cub->vars.step = 1.0 * cub->tex[tex].y / cub->vars.lineHeight;
      // Starting texture coordinate
      cub->vars.texPos = (cub->vars.drawStart - cub->vars.h / 2 + cub->vars.lineHeight / 2) * cub->vars.step;
      cub->vars.y = drawStart;
	   cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;
      while(cub->vars.y < drawEnd)
      {
        // Cast the texture coordinate to integer, and mask with (cub->tex[tex].y - 1) in case of overflow
        cub->vars.texY = (int)cub->vars.texPos & (cub->tex[tex].y - 1);
        cub->vars.texPos += cub->vars.step;

        // printf("texx=%f & texy=%f\n", cub->vars.texX, cub->vars.texY);
        // printf("step = %f, texPos = %f\n", cub->vars.step, cub->vars.texPos);
       // printf("x=%d & y=%d\n", cub->tex[0].x, cub->tex[0].y);
	  	//printf("addr=%p & line_length=%i & txY = %i & txX = %i bpp = %i\n ", cub->tex[tex].addr, cub->tex[tex].line_length, (int)cub->vars.texY, (int)cub->vars.texX, cub->tex[tex].bits_per_pixel);
	 	if (cub->tex[tex].x > cub->rx || cub->tex[tex].y > cub->ry)
	  		 cub->vars.texY = ((int)cub->vars.texPos) & (cub->tex[tex].line_length - 1) * 4;
		else			
			cub->vars.texY = ((int)cub->vars.texPos) & ((cub->tex[tex].line_length) - 1);
		if (cub->vars.texY >= 0 && cub->vars.texX >= 0)
            color = *(unsigned int *)(cub->tex[tex].addr + ((cub->tex[tex].line_length * (int)cub->vars.texY) + (int)cub->vars.texX \
            * (cub->tex[tex].bits_per_pixel / 8)));
		else
			color = 0;
		if (color < 0)
			color = 0;
        //color = *((unsigned int *) test);
       // printf("color:%u\n", color);
        // printf("x: %d, y: %d, color: %u\n", cub->vars.x, cub->vars.y, color);
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, color);
        cub->vars.y++;
      }
    //   cub->vars.y = 0;
   // printf("5verline!-drawstart=%d && drawend=%i && ry=%d !\n\n\n",cub->vars.drawStart, cub->vars.drawEnd, cub->ry);

	// while (cub->vars.y < drawEnd)
    // {
    //     my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, cub->vars.colorwall);//0xc7adfb
    //     cub->vars.y++;
    // }
	while (cub->vars.y < cub->ry)
    {
        my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x97f36d);
        cub->vars.y++;
    }
}

int    ft_checkposition(t_parse *cub, int x, int y)
{
    if ((x > 0 && x < cub->maxstrlen) || (y > 0 && y < cub->max_y)
        || (cub->vars.posX > 0 && cub->vars.posX < cub->maxstrlen)
        || (cub->vars.posY > 0 && cub->vars.posY < cub->max_y))
        return (1);
    else
        return (0);
}

int	render_next_frame(t_parse *cub)
{
	if (cub->vars.walksies[up] == 0 && cub->vars.walksies[left] == 0 && cub->vars.walksies[down] == 0 \
		&& cub->vars.walksies[right] == 0 && cub->vars.walksies[turn_l] == 0 && cub->vars.walksies[turn_r] == 0 && cub->loop == 1)
		return (1);
	cub->img.img = mlx_new_image(cub->vars.mlx, cub->rx, cub->ry);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length,&cub->img.endian);
	//mlx_calc(cub);
    //printf("hoi ik ben rotzooi :) ");
    //printf("je moeder\n");//mlx_hook(cub->vars.win, 2, 1L << 0, key_pressed, cub);
    //printf("efbuiegfu34gf20j3dwqedo2h3eihf3i4hf34h0hf34hg34hghihgihg");
    //printf("hoi ik ben kjuwb drie dee^C");
    // printf("walksies0=%d\n && lemaoX=%d\n && lemaoY=%d\n", cub->vars.walksies[up], ((int)(cub->vars.posX + cub->vars.dirX * cub->vars.moveSpeed)), ((int)(cub->vars.posY + cub->vars.dirY * cub->vars.moveSpeed)));
    int y_up;
    int y_down;
    int y_left;
    int y_right;
    int x_up;
    int x_down;
    int x_left;
    int x_right;
    // printf("posX=%f && posY=%f\n", cub->vars.posX, cub->vars.posY);
    x_up = (int)(cub->vars.posX + (cub->vars.dirX * cub->vars.moveSpeed));
    y_up = (int)(cub->vars.posY + (cub->vars.dirY * cub->vars.moveSpeed));
    x_down = (int)(cub->vars.posX - (cub->vars.dirX * cub->vars.moveSpeed));
    y_down = (int)(cub->vars.posY - (cub->vars.dirY * cub->vars.moveSpeed));
    x_left = (int)(cub->vars.posX - (cub->vars.dirY * cub->vars.moveSpeed));
    y_left = (int)(cub->vars.posY + (cub->vars.dirX * cub->vars.moveSpeed));
    x_right = (int)(cub->vars.posX + (cub->vars.dirY * cub->vars.moveSpeed));
    y_right = (int)(cub->vars.posY - (cub->vars.dirX * cub->vars.moveSpeed));
    // printf("maxstrlen=%d\n", cub->maxstrlen);
    // printf("x=%d && y=%d && dirx=%f && movespeed=%f && chposx=%d && chposy=%d\n", x_up, y_up, cub->vars.dirX, cub->vars.moveSpeed, ft_checkposition(cub, x_up, x_down), ft_checkposition(cub, y_up, y_down) );
    if(cub->vars.walksies[up] == 1)
    {
      if(cub->map[(int)(cub->vars.posY)][x_up] != '1' && ft_checkposition(cub, x_up, y_up) == 1)
            cub->vars.posX += cub->vars.dirX * cub->vars.moveSpeed;
      if(cub->map[y_up][(int)(cub->vars.posX)] != '1' && ft_checkposition(cub, x_up, y_up) == 1)
        cub->vars.posY += cub->vars.dirY * cub->vars.moveSpeed;
    }
    if(cub->vars.walksies[down] == 1)
    {
        if(cub->map[(int)(cub->vars.posY)][x_down] != '1' && ft_checkposition(cub, x_down, y_down) == 1)
         cub->vars.posX -= cub->vars.dirX * cub->vars.moveSpeed;
         if(cub->map[y_down][(int)(cub->vars.posX)] != '1' && ft_checkposition(cub, x_down, y_down) == 1)
         cub->vars.posY -= cub->vars.dirY * cub->vars.moveSpeed;
    }
    if(cub->vars.walksies[left] == 1)
    {
        if(cub->map[(int)(cub->vars.posY)][x_right] != '1' && ft_checkposition(cub, x_right, y_right) == 1)
            cub->vars.posX += cub->vars.dirY * cub->vars.moveSpeed;
        if(cub->map[y_right][(int)(cub->vars.posX)] != '1' && ft_checkposition(cub, x_right, y_right) == 1)
             cub->vars.posY -= cub->vars.dirX * cub->vars.moveSpeed;
    }
    if(cub->vars.walksies[right] == 1)
    {
        if(cub->map[(int)(cub->vars.posY)][x_left] != '1' && ft_checkposition(cub, x_left, y_left) == 1)
            cub->vars.posX -= cub->vars.dirY * cub->vars.moveSpeed;
        if(cub->map[y_left][(int)(cub->vars.posX)] != '1' && ft_checkposition(cub, x_left, y_left) == 1)
            cub->vars.posY += cub->vars.dirX * cub->vars.moveSpeed;
    }
    if(cub->vars.walksies[turn_l] == 1)
    {
        //both camera direction and camera plane must be rotated
      cub->vars.oldDirX = cub->vars.dirX;
      cub->vars.dirX = cub->vars.dirX * cos(-cub->vars.rotSpeed) - cub->vars.dirY * sin(-cub->vars.rotSpeed);
      cub->vars.dirY = cub->vars.oldDirX * sin(-cub->vars.rotSpeed) + cub->vars.dirY * cos(-cub->vars.rotSpeed);
      cub->vars.oldPlaneX = cub->vars.planeX;
      cub->vars.planeX = cub->vars.planeX * cos(-cub->vars.rotSpeed) - cub->vars.planeY * sin(-cub->vars.rotSpeed);
      cub->vars.planeY = cub->vars.oldPlaneX * sin(-cub->vars.rotSpeed) + cub->vars.planeY * cos(-cub->vars.rotSpeed);
    }
    if(cub->vars.walksies[turn_r] == 1)
    {
    //both camera direction and camera plane must be rotatedWil jij jouw onderzoeksskills inzetten om ons en de wereld te vertellen wat de effecten zijn van private financieringsvormen op (private) scholing en de ontwikkelingskansen van kwetsbare studenten? Laat van je horen via de link in de comments!
      cub->vars.oldDirX = cub->vars.dirX;
      cub->vars.dirX = cub->vars.dirX * cos(cub->vars.rotSpeed) - cub->vars.dirY * sin(cub->vars.rotSpeed);
      cub->vars.dirY = cub->vars.oldDirX * sin(cub->vars.rotSpeed) + cub->vars.dirY * cos(cub->vars.rotSpeed);
      cub->vars.oldPlaneX = cub->vars.planeX;
      cub->vars.planeX = cub->vars.planeX * cos(cub->vars.rotSpeed) - cub->vars.planeY * sin(cub->vars.rotSpeed);
      cub->vars.planeY = cub->vars.oldPlaneX * sin(cub->vars.rotSpeed) + cub->vars.planeY * cos(cub->vars.rotSpeed);
    }
    // //ft_verLine(cub->vars.drawStart, cub->vars.drawEnd, cub);
    // printf("walksies0=%d\n && lemaoX=%d\n && lemaoY=%d\n", cub->vars.walksies[up], ((int)(cub->vars.posX + cub->vars.dirX * cub->vars.moveSpeed)), ((int)(cub->vars.posY + cub->vars.dirY * cub->vars.moveSpeed)));
    // printf("yoyo\n");
    // exit(1);
    mlx_calc(cub);
    mlx_sprite(cub);
	//mlx_do_sync(cub->vars.mlx);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->vars.mlx, cub->img.img);
	cub->loop = 1;
	return (1);
}

// int draw(t_vars *vars)
// {
// 	int     img_width;
//     int		img_height;

// 	img_width = 1920;//1600
// 	img_height = 1080;//800
// 	t_data img;
// 	img.img = mlx_new_image(vars->mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
// 								&img.line_length,&img.endian);
// 	img.img = mlx_xpm_file_to_image(vars->mlx, "./yolanda.xpm", &img_width, &img_height);
// 	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
// 	return (1);
// }

void    ft_sort(t_parse *cub)
{
    int i;
	int temp;
	double tempp;

    i = 0;
	temp = 0;
	tempp = 0.0;
	//printf("i = %d\ncubobj = %d\n", i, cub->objects - 1);
	
    while(i + 1 < cub->objects)
    {//printf("i = %d\ncubobj = %d\ndis = %fd\ndis+1 = %f\n", i, cub->objects - 1,cub->arr[cub->spriteOrder[i]].distance, cub->arr[i + 1].distance);
	//usleep (150000);
	//printf("distance=%f && \n", cub->arr[i].distance);
        if (cub->arr[i].distance < cub->arr[i + 1].distance)
        {
			//printf("2=====i = %d\ncubobj = %d\n", i, cub->objects - 1);
			temp = cub->spriteOrder[i];
			tempp = cub->arr[i].distance;
			cub->spriteOrder[i] = cub->spriteOrder[i + 1];
			cub->arr[i].distance = cub->arr[i + 1].distance;
			cub->spriteOrder[i + 1] = temp;
			cub->arr[i + 1].distance = tempp;
			i = 0;
        }
		else
			i++;
		
    }
}

void mlx_sprite(t_parse *cub)
{
		//ft_bzero(&cub->sprite, sizeof(t_jonas));
    int i;
    unsigned int color;
    i = 0;
    color = 0;
    //cub->vars.x = 0;
    //cub->vars.y = 0;
	
	while(i < cub->objects)
    {
      	cub->spriteOrder[i] = i;
      	cub->arr[cub->spriteOrder[i]].distance = ((cub->vars.posX - cub->arr[cub->spriteOrder[i]].x) * (cub->vars.posX - cub->arr[cub->spriteOrder[i]].x) \
		  + (cub->vars.posY - cub->arr[cub->spriteOrder[i]].y) * (cub->vars.posY - cub->arr[cub->spriteOrder[i]].y)); //sqrt not taken, unneeded
		i++;
	}
	ft_sort(cub);
	i = 0;
    while (i < cub->objects)
    {
      //translate sprite position to relative to camerasprite
      cub->sprite.spriteX = cub->arr[cub->spriteOrder[i]].x -  cub->vars.posX; //cub->spriteOrder[i]
      cub->sprite.spriteY = cub->arr[cub->spriteOrder[i]].y - cub->vars.posY;
	cub->sprite.spriteX += 0.5;
	cub->sprite.spriteY += 0.5;
      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      cub->sprite.invDet = 1.0 / (cub->vars.planeX * cub->vars.dirY - cub->vars.dirX * cub->vars.planeY); //required for correct matrix multiplication

      cub->sprite.transformX = cub->sprite.invDet * (cub->vars.dirY * cub->sprite.spriteX - cub->vars.dirX * cub->sprite.spriteY);
      cub->sprite.transformY = cub->sprite.invDet * (-cub->vars.planeY * cub->sprite.spriteX + cub->vars.planeX * cub->sprite.spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

      cub->sprite.spriteScreenX = (int)((cub->rx / 2) * (1 + cub->sprite.transformX / cub->sprite.transformY));
      //calculate height of the sprite on screen
      cub->sprite.spriteHeight = abs((int)(cub->ry / (cub->sprite.transformY))); //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      cub->sprite.drawStartY = -cub->sprite.spriteHeight / 2 + cub->ry / 2;//vMoveScreen
      if(cub->sprite.drawStartY < 0)
        cub->sprite.drawStartY = 0;
      cub->sprite.drawEndY = cub->sprite.spriteHeight / 2 + cub->ry / 2;
      if(cub->sprite.drawEndY >= cub->ry)
        cub->sprite.drawEndY = cub->ry - 1;

      //calculate width of the sprite
      cub->sprite.spriteWidth = abs((int)(cub->ry / (cub->sprite.transformY)));//(int)
      cub->sprite.drawStartX = -(cub->sprite.spriteWidth) / 2 + cub->sprite.spriteScreenX;
      if(cub->sprite.drawStartX < 0)
        cub->sprite.drawStartX = 0;
      cub->sprite.drawEndX = cub->sprite.spriteWidth / 2 + cub->sprite.spriteScreenX;
      if(cub->sprite.drawEndX >= cub->rx)
        cub->sprite.drawEndX = cub->rx - 1;

        cub->sprite.stripe = cub->sprite.drawStartX;
       // printf("stripe: %i | drawend: %i\n", cub->sprite.stripe, cub->sprite.drawEndX);
      //loop through every vertical stripe of the sprite on screen
      while (cub->sprite.stripe <= cub->sprite.drawEndX)
      {//printf("stripe:%d\n",cub->sprite.stripe);
        cub->vars.texX = (int)(256 * (cub->sprite.stripe - (-cub->sprite.spriteWidth / 2 + cub->sprite.spriteScreenX)) * cub->tex[4].x / cub->sprite.spriteWidth) / 256; //texwidth
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(cub->sprite.transformY > 0 && cub->sprite.stripe > 0 && cub->sprite.stripe < cub->vars.w && cub->sprite.transformY < cub->vars.ZBuffer[cub->sprite.stripe])//perpendicular distance is usedstripe > 0 && cub->sprite.stripe < cub->vars.w && cub->sprite.transformY < ZBuffer[stripe])
    		cub->vars.y = cub->sprite.drawStartY;
        while (cub->vars.y < cub->sprite.drawEndY && cub->sprite.stripe > 0 && cub->sprite.stripe < cub->rx)  //for every pixel of the current stripe
            {
                cub->vars.texX = (int)(256 * (cub->sprite.stripe - (-cub->sprite.spriteWidth / 2 + cub->sprite.spriteScreenX)) * cub->tex[4].x / cub->sprite.spriteWidth) / 256; //texwidth
                cub->sprite.d = (cub->vars.y) * 256 - cub->ry * 128 + cub->sprite.spriteHeight * 128; //256 and 128 factors to avoid floats
                cub->vars.texY = ((cub->sprite.d * cub->tex[4].x) / cub->sprite.spriteHeight) / 256; //texwidth
                // color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
                // if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
              	 color = *(unsigned int *)(cub->tex[4].addr + (cub->tex[4].line_length * (int)cub->vars.texY + (int)cub->vars.texX \
                * (cub->tex[4].bits_per_pixel / 8)));
                if(color > 0)
                    my_mlx_pixel_put(&cub->img, cub->sprite.stripe, cub->vars.y, color);
                cub->vars.y++;
            }
        cub->sprite.stripe++;
      }
      i++;
    }
}

void	mlx_calc(t_parse *cub)
{
    // int i;
    // i = 0;
    cub->vars.x = 0;
	while (cub->vars.x < cub->vars.w)
    {
        cub->vars.colorwall = 13086203;
        //printf("VARSX=%d\n", cub->vars.x);
        //printf("posx=%f && posy=%f && startx= %d && starty= %d\n", cub->vars.posX, cub->vars.posY, cub->startx, cub->starty);
        //calculate ray position and direction
        cub->vars.cameraX = 2 * cub->vars.x / (double)cub->vars.w - 1; //x-coordinate in camera space
        //printf("cub->vars.camerax=%f\nplaneX=%f\n",cub->vars.cameraX, cub->vars.planeX);
        cub->vars.rayDirX = cub->vars.dirX + cub->vars.planeX * cub->vars.cameraX;
        cub->vars.rayDirY = cub->vars.dirY + cub->vars.planeY * cub->vars.cameraX;
        // cub->vars.y = 0;
        // cub->vars.x = 0;
        cub->vars.mapX = (int)cub->vars.posX;
        cub->vars.mapY = (int)cub->vars.posY;
        //printf("cub->vars.raydirx=%f&&cub->vars.raydiry=%f\n", cub->vars.rayDirX, cub->vars.rayDirY);
        // deltaDistX = fabs(1 / cub->vars.rayDirX);
        // deltaDistY = fabs(1 / cub->vars.rayDirY);
        // if (cub->vars.rayDirX == 0 || cub->vars.rayDirY == 0)
        // 	return;
        cub->vars.deltaDistX = (cub->vars.rayDirY == 0) ? 0 : ((cub->vars.rayDirX == 0) ? 1 : fabs(1 / cub->vars.rayDirX));
        cub->vars.deltaDistY = (cub->vars.rayDirX == 0) ? 0 : ((cub->vars.rayDirY == 0) ? 1 : fabs(1 / cub->vars.rayDirY));
        // printf("1deltadisx=%f&&deltadisy=%f\n", cub->vars.deltaDistX, cub->vars.deltaDistY);
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
        //  printf("2cub->vars.rayDirX= %f &&cub->vars.rayDirY= %f \nmpax= %d &&may= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", cub->vars.rayDirX, cub->vars.rayDirY, cub->vars.mapX, cub->vars.mapY, cub->vars.posX, cub->vars.posY, cub->vars.stepX, cub->vars.stepY);
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
        // printf("3qqqqcub->vars.rayDirX= %f &&cub->vars.rayDirY= %f \nmapx= %d &&mapy= %d \nposX= %f &&posY= %f \nstepx= %d &&stepy= %d\n", cub->vars.rayDirX, cub->vars.rayDirY, cub->vars.mapX, cub->vars.mapY, cub->vars.posX, cub->vars.posY, cub->vars.stepX, cub->vars.stepY);
        //exit(0);
        if (cub->vars.side == 0)
            cub->vars.perpWallDist = (cub->vars.mapX - cub->vars.posX + (1 - cub->vars.stepX) / 2) / cub->vars.rayDirX;
        else
        {
            //printf("BORISSSSSSSSSSS\n");
;				cub->vars.perpWallDist = (cub->vars.mapY - cub->vars.posY + (1 - cub->vars.stepY) / 2) / cub->vars.rayDirY;
        }
        // if (perpWallDist <= 0)
        // 	perpWallDist = 0.01;

        //Calculate height of line to draw on screen
        //printf("!-perpWallDist=%f-!\n", cub->vars.perpWallDist);
        cub->vars.lineHeight = (int)(cub->vars.h / cub->vars.perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        //printf("!-lineheight=%d-!\n", cub->vars.lineHeight);
        cub->vars.drawStart = (-cub->vars.lineHeight / 2) + (cub->vars.h / 2);
        // printf("4!-drawstart0=%d-!\n", cub->vars.drawStart);
        if(cub->vars.drawStart < 0)
            cub->vars.drawStart = 0;

        cub->vars.drawEnd = (cub->vars.lineHeight / 2) + (cub->vars.h / 2);
        if(cub->vars.drawEnd >= cub->vars.h)
            cub->vars.drawEnd = cub->vars.h - 1;
            //give x and y sides different brightness
        if(cub->vars.side == 1)
            cub->vars.colorwall = cub->vars.colorwall / 2;
        //draw the pixels of the stripe as a vertical line



        ft_verLine(cub->vars.drawStart, cub->vars.drawEnd, cub);
        cub->vars.ZBuffer[cub->vars.x] = cub->vars.perpWallDist; //perpendicular distance is used
       // printf("zbuffer:%f\n", cub->vars.ZBuffer[cub->vars.x]);
        cub->vars.x++;
    }
}

void	ft_mlx(t_parse *cub, char **argv, int argc)
{
	// t_data	img;
	// t_vars	vars;
    //--------------------
    cub->vars.moveSpeed = 0.1; //make define
    cub->vars.rotSpeed = 0.05;
    cub->vars.oldDirX = 0;
    cub->vars.oldPlaneX = 0;
    cub->vars.colorwall = 255;
    cub->vars.cameraX = 0.0; //x-coordinate in camera space
    cub->vars.rayDirX = 0.0;
    cub->vars.rayDirY = 0.0;
    cub->vars.x = 0;
   	cub->vars.h = cub->ry;
    cub->vars.w = cub->rx;
    cub->vars.posX = (double)cub->startx + 0.5; //0.5
    cub->vars.posY = (double)cub->starty + 0.5;  //x and y start position
	//mlx_get_screen_size(cub->vars.mlx, &cub->maxrx, &cub->maxry);
    cub->vars.ZBuffer = malloc(sizeof(double) * cub->rx);
	cub->spriteOrder = malloc(sizeof(int) * cub->objects);
    printf("ltr=%c\nzbuf=%p\nspriteor=%p\n", cub->ltr, cub->vars.ZBuffer, cub->spriteOrder);
    if (cub->ltr == 'S')
    {
        cub->vars.dirX = 0.0;
        cub->vars.dirY = 1.0; //initial direction vector ;fix that with s e wetc.
        cub->vars.planeX = -0.66;
        cub->vars.planeY = 0; //the 2d raycaster version of camera plane
    }
    if (cub->ltr == 'W')
    {
        cub->vars.dirX = -1.0;
        cub->vars.dirY = 0.0; //initial direction vector ;fix that with s e wetc.
        cub->vars.planeX = 0;
        cub->vars.planeY = -0.66; //the 2d raycaster version of camera plane
    }
    if (cub->ltr == 'N')
    {
        cub->vars.dirX = 0.0;
        cub->vars.dirY = -1.0; //initial direction vector ;fix that with s e wetc.
        cub->vars.planeX = 0.66;
        cub->vars.planeY = 0; //the 2d raycaster version of camera plane
    }
    if (cub->ltr == 'E')
    {
        cub->vars.dirX = 1.0;
        cub->vars.dirY = 0.0; //initial direction vector ;fix that with s e wetc.
        cub->vars.planeX = 0;
        cub->vars.planeY = 0.66; //the 2d raycaster version of camera plane
    }

       //which box of the map we're in
    cub->vars.mapX = 0;
    cub->vars.mapY = 0;

      //length of ray from current position to next x or y-side
      cub->vars.sideDistX = 0.0;
      cub->vars.sideDistY = 0.0;

       //length of ray from one x or y-side to next x or y-side
      cub->vars.deltaDistX = 0.0;
      cub->vars.deltaDistY = 0.0;
      //cub->vars.perpWallDist;

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
	if (cub->save == 0)
		cub->vars.win = mlx_new_window(cub->vars.mlx, cub->rx, cub->ry, "🄲🅄🄱3🄳"); //fix window bitch
	// s
	cub->vars.y = 0;
    cub->vars.x = 0;
    cub->vars.walksies[up] = 0;
    cub->vars.walksies[down] = 0;
    cub->vars.walksies[left] = 0;
    cub->vars.walksies[right] = 0;
    cub->vars.walksies[turn_r] = 0;
    cub->vars.walksies[turn_l] = 0;


    //open(cub->fd, O_RDONLY);
    cub->tex[0].img = mlx_png_file_to_image(cub->vars.mlx, cub->no, &cub->tex[0].x, &cub->tex[0].y);
    //close(cub->fd);
    cub->tex[0].addr = mlx_get_data_addr(cub->tex[0].img, &cub->tex[0].bits_per_pixel, &cub->tex[0].line_length, &cub->tex[0].endian);
      //open(cub->fd, O_RDONLY);
    cub->tex[1].img = mlx_png_file_to_image(cub->vars.mlx, cub->so, &cub->tex[1].x, &cub->tex[1].y);
    //close(cub->fd);
    cub->tex[1].addr = mlx_get_data_addr(cub->tex[1].img, &cub->tex[1].bits_per_pixel, &cub->tex[1].line_length, &cub->tex[1].endian);
      //open(cub->fd, O_RDONLY);
    cub->tex[2].img = mlx_png_file_to_image(cub->vars.mlx, cub->we, &cub->tex[2].x, &cub->tex[2].y);
    //close(cub->fd);
    cub->tex[2].addr = mlx_get_data_addr(cub->tex[2].img, &cub->tex[2].bits_per_pixel, &cub->tex[2].line_length, &cub->tex[2].endian);
      //open(cub->fd, O_RDONLY);
    cub->tex[3].img = mlx_png_file_to_image(cub->vars.mlx, cub->ea, &cub->tex[3].x, &cub->tex[3].y);
    //close(cub->fd);
    cub->tex[3].addr = mlx_get_data_addr(cub->tex[3].img, &cub->tex[3].bits_per_pixel, &cub->tex[3].line_length, &cub->tex[3].endian);
      //open(cub->fd, O_RDONLY);
    cub->tex[4].img = mlx_png_file_to_image(cub->vars.mlx, cub->s, &cub->tex[4].x, &cub->tex[4].y);
    //close(cub->fd);
    cub->tex[4].addr = mlx_get_data_addr(cub->tex[4].img, &cub->tex[4].bits_per_pixel, &cub->tex[4].line_length, &cub->tex[4].endian);

    //mlx_key_hook(cub->vars.win, keys, &cub->vars);
	if (cub->save == 1)
	{
		bitmap(cub);
	}
    mlx_hook(cub->vars.win, 2, 1L << 0, key_pressed, cub);
    mlx_hook(cub->vars.win, 3, 2L << 0, key_released, cub);
	mlx_hook(cub->vars.win, 17, 1L << 17, destroy, cub);

    //mlx_hook(cub->vars.win, 17, 0, destroy ,cub);
	mlx_loop_hook(cub->vars.mlx, render_next_frame, cub);
	//printf("\nlemao\n");
    //mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	mlx_loop(cub->vars.mlx);
	if (cub->vars.ZBuffer)
		free(cub->vars.ZBuffer);
	if (cub->spriteOrder)
	free(cub->spriteOrder);
}

//make it norm
//bmp image resizing
//max int rx ry (kijk of het onder 0 komt)
//koelr$d 