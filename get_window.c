/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:20:11 by araramya          #+#    #+#             */
/*   Updated: 2021/04/25 02:20:14 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int main()
{
    void *mlx;
    void *mlx_window;

    mlx  = mlx_init();
    mlx_window = mlx_new_window(mlx, 1920, 1080, "Hello Window:)");
    mlx_loop(mlx);
}
