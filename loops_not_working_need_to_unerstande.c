/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 04:50:59 by araramya          #+#    #+#             */
/*   Updated: 2021/04/27 04:51:07 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <mlx.h>

// typedef struct  s_data {
//     void        *img;
//     char        *addr;
//     int         bits_per_pixel;
//     int         line_length;
//     int         endian;
// }               t_data;
// void my_mlx_pixel_put(t_data *data, int x, int y, int color) //more faster than mlx_pixel put function
// {
//     char *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// int             main()
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "MYwindow");
//     img.img = mlx_new_image(mlx, 1920, 1080);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//                                  &img.endian);
//     my_mlx_pixel_put(&img, 20, 20, 0x00FF0000);
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx);
// }
#include <mlx.h>
#include <stdio.h>

typedef struct s_vars
{
    void *mlx;
    void *win;
}              t_vars;

int key_hook(int keycode, t_vars *vars)
{
    printf("You pressed the key\n");
}
int     render_next_frame(void *vars);

int main()
{
    t_vars vars;
    
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello Window :)");
   // mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop_hook(vars.mlx, render_next_frame, &vars);
    mlx_loop(vars.mlx);
}