/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:59:13 by araramya          #+#    #+#             */
/*   Updated: 2021/04/25 02:59:15 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>

// typedef struct s_data
// {
//     void *img;
//     char *addr;
//     int bits_per_pixels;
//     int line_length;
//     int endian;
// }              t_data;

// int main()
// {
//     void *mlx;
//     t_data img;

//     mlx = mlx_init();
//     img.img = mlx_new_image(mlx, 1920, 1080);
//        /*
//     ** After creating an image, we can call `mlx_get_data_addr`, we pass
//     ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
//     ** then be set accordingly for the *current* data address.
//     */
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
// }

//formula for offset
//int offset = (y * line_lenght + x * (bits_per_pixel/8));


// typedef struct s_data
// {
//     void *img;
//     char *addr;
//     int bits_per_pixel;
//     int line_length;
//     int endian;
// }              t_data;

// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

#include <mlx.h>
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color) //more faster than mlx_pixel put function
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "MYwindow");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    my_mlx_pixel_put(&img, 20, 20, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}