#include "mlx/mlx.h"
//#include "keys.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define EVENT_KEY_PRESS 2
//#define EVENT_KEY_EXIT 17
#define mapWidth 24
#define mapHeight 24
#define width 1920
#define height 1080
#define texWidth 64
#define texHeight 64
//moving keys
#define k_w  13
#define k_a  0
#define k_s  1
#define k_d  2
//close key
#define k_esc  53
//arrow
#define arr_up  126
#define arr_dwn  125
#define arr_right  124
#define arr_legt  123


typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;

}           t_img;

typedef struct s_info
{
    t_img image;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    void *mlx;
    void *win;
    double moveSpeed;
    double rotSpeed;

}               t_info;



int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void verLine (t_info *info, int x, int drawStart, int drawEnd, int color)
{

    int y;
    y = drawStart;
    while(y < drawEnd)
    {
        
   
       my_mlx_pixel_put(&info->image, x, y, color);
        y++;
    }
    
}

// raycasting part 1 
void calculation(t_info *info)
{
    int x;
    x = 0;
    while(x < width)
    {
        // calculate ray position and direction
        double cameraX = 2 * x / (double)width - 1; // x-coordinate in camera space
        double rayDirX = info->dirX + info->planeX * cameraX;
        double rayDirY = info->dirY + info->planeY * cameraX;

         //which box of the map we are in
         int mapX = (int)info->posX;
         int mapY = (int)info->posY;

         //length of ray form current position to next x or y-side
         double sideDistX;
         double sideDistY;

         //length of ray from one x or y-side to next x or y -side
         double deltaDistX = fabs(1/rayDirX);
         double deltaDistY = fabs(1/rayDirY);
         double perpWallDist;
         
         //what direction to step in x or y-direction (either +1 or -1)
         int stepX;
         int stepY;

         int hit = 0 ;  //was there a wall hit ?
         int side ; //was NS or EW wall hit ?? 

         // calculate step and intial sideDist
         if(rayDirX < 0)
         {
             stepX = -1;
             sideDistX =(info->posX - mapX) * deltaDistX;
         }
         else
         {
             stepX = 1;
             sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
         }
         if(rayDirY < 0)
         {
             stepY = -1;
             sideDistY = (info->posY - mapY) * deltaDistY;
         }
         else
         {
             stepY = 1;
             sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
         }
         

         //perform DDA
         while(hit == 0)
         {
             // jump to next map square, Or in x-direction, Or in y-direction
             if(sideDistX < sideDistY)
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
             // Check if ray has hit a wall
             if(worldMap[mapX][mapY] > 0)
                hit = 1;
         }
         //calculate distance projected on camera direction (Eculidian fisheye effect)
        if (!side)
            perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

        // calculate height of line to draw on screen
        int lineHeight = (int)(height / perpWallDist);
       
        
        
        // calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight/2 + height/2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + height/2;
        if(drawEnd >= height)
            drawEnd = height - 1;
        
    
        //choose wall color
        int color; 
        if(worldMap[mapX][mapY] == 1)
            color = 0xFF0000;   //red
        else if(worldMap[mapX][mapY] == 2)
            color = 0x00FF00;  //green
        else if(worldMap[mapX][mapY] == 3)
            color = 0x0000FF;  //blue
        else if (worldMap[mapX][mapY] == 4)
            color = 0xFFFFFF;   //white
        else 
            color = 0xFFFF00;   // yellow 
        
        // give x and y sides differend brightness
        if (side == 1)
            color = color/2;
        //draw pixels  of the stripe as vertical line
        verLine(info, x, drawStart, drawEnd, color);
        x++;
    }
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int main_loop(t_info *info)
{
    calculation(info);
    return (0);
}

void	ft_clear(t_info *data) // paint all window BLACK
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			my_mlx_pixel_put(&data->image, j, i, create_rgb(0, 0, 0));
		}
	}
}


int key_pressed(int key, t_info *info)
{
	//move forward
	if(key == k_w)
	{
		if(!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)]) 
            info->posX += info->dirX * info->moveSpeed;
        if(!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)]) 
            info->posY += info->dirY * info->moveSpeed;
	}
    // move back
    if(key == k_s)
    {
        if(worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)] == 0) 
            info->posX -= info->dirX * info->moveSpeed;
        if(worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)] == 0) 
            info->posY -= info->dirY * info->moveSpeed;
    }
    // move right
    if(key == k_d)
    {
        //both camera direction and camera plane must be roted
        double oldDirX = info->dirX;
        info->dirX = info->dirX * cos(-(info->rotSpeed)) - info->dirY * sin(-(info->rotSpeed));
        info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-(info->rotSpeed));
        double oldPlaneX = info->planeX;
        info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
        info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
    }
   if(key == k_a)
   {
       //both camera direction and camera plane must be rotated
      double oldDirX = info->dirX;
      info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
      info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
      double oldPlaneX = info->planeX;
      info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
      info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);

   }
    if(key == k_esc)
        exit(0);
return 0;
}


int    ft_frame(t_info *data)
{
    ft_clear(data);
	//key_pressed(key, );
	calculation(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_do_sync(data->mlx);
	return (1);
}

int main()
{
    t_info info;
    t_img img;

    info.posX = 22;
    info.posY = 12;
    info.dirX = -1;
    info.dirY = 0;
    info.planeX = 0;
    info.planeY = 0.66;
    info.moveSpeed = 0.5;
    info.rotSpeed = 0.05;
    
    info.mlx = mlx_init();
    info.win = mlx_new_window(info.mlx, width, height, "cub3D");
    info.image.img = mlx_new_image(info.mlx, width, height);
    info.image.addr = mlx_get_data_addr(info.image.img, &info.image.bits_per_pixel, &info.image.line_length, &info.image.endian);


    mlx_loop_hook(info.mlx, &main_loop, &info);
    mlx_hook(info.win, EVENT_KEY_PRESS, 0, &key_pressed, &info); 
    mlx_loop_hook(info.mlx, ft_frame, &info);
    mlx_loop(info.mlx);
    
}
