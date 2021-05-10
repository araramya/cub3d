#include "mlx/mlx.h"
//#include "keys.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#define EVENT_KEY_PRESS 2
//#define EVENT_KEY_EXIT 17
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct s_info
{
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
/*
void my_mlx_pixel_put(t_data *data, int x, int y, int color) //more faster than mlx_pixel put function
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}*/

void verLine (t_info *info, int x, int drawStart, int drawEnd, int color)
{
    int y;
    y = drawStart;
    while(y < drawEnd)
    {
        mlx_pixel_put(info->mlx, info->win, x, y, color);
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
        if (side == 0)
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
int main_loop(t_info *info)
{
    calculation(info);
    return (0);
}
int main()
{
    t_info info;
    info.mlx = mlx_init();

    info.posX = 22;
    info.posY = 12;
    info.dirX = -1;
    info.dirY = 0;
    info.planeX = 0;
    info.planeY = 0.66;
    info.moveSpeed = 0.05;
    info.rotSpeed = 0.05;

    info.win = mlx_new_window(info.mlx, width, height, "cub3D");
    mlx_loop_hook(info.mlx, &main_loop, &info);
    mlx_loop(info.mlx);
}