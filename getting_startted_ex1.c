//ex1 Print squares, circles, triangles and hexagons on the screen by writing the pixels accordingly
#include <mlx.h>
#include <math.h>

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main()
{
    void *mlx;
    void *mlx_win;
    t_data img;
    int x = 4;
    int y = 4;

        
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920,1080, "Getting started");
    img.img = mlx_new_image(mlx,1920,1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
/*
    //print tringle 


    //print horizontal
    while(y++ <= 300 )
        my_mlx_pixel_put(&img, x, y, 0x00FF0000);
    //print vertical
    while(x++ <= 301)
        my_mlx_pixel_put(&img,x,y, 0x00FF0000);
    //print en myus koxmy 
    while(x-- >= 5 && y-- >= 5 )
    {
       my_mlx_pixel_put(&img,x,y, 0x00FF0000);
    }
    */
    
    //print empty square 

/*
    while(y <= 300)
        my_mlx_pixel_put(&img, x, ++y, 0x00FF0000);
    while(x <= 300)
         my_mlx_pixel_put(&img, ++x, y, 0x00FF0000);
    while(y >= 5)
        my_mlx_pixel_put(&img, x, --y, 0x00FF0000);
    while(x >= 5)
        my_mlx_pixel_put(&img, --x, y, 0x00FF0000);
    
*/
/*
   //print full square


   while(y <= 300)
   {
       x = 4;
       while(x <= 300)
       {
           my_mlx_pixel_put(&img, x, y, 0x00FF0000);
           x++;
       }
       y++;
   }
*/

//print circle name (x-h)^2 + (y-k)^2 = r^2
    int x_c = 960;
    int y_c = 540; // center
    my_mlx_pixel_put(&img, x_c, y_c, 0x00FF0000);

    int radius = 200;
    y = y_c - radius; //puteing xy in the right place to print
    x = x_c - radius;
    my_mlx_pixel_put(&img, x, y, 0x0000FF00);
    int y_cpy = y;
    int x_cpy = x;
    while(y <= (y_c + radius)  ) 
    {
        while(x <= x_cpy *  2)
        {
            if(((x-x_c)*(x-x_c) + (y-y_c)*(y-y_c)) == radius*radius)
                my_mlx_pixel_put(&img, x, y, 0x0000FF00);
            x++;
        }
        x= x_c -radius;
        y++;
    }
  //  my_mlx_pixel_put(&img, x, y, 0x0000FF00);
  
    mlx_put_image_to_window(mlx, mlx_win,img.img, 0,0);
    mlx_loop(mlx);
}