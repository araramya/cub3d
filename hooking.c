/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 10:15:48 by araramya          #+#    #+#             */
/*   Updated: 2021/04/25 10:16:09 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main()
{
    t_vars vars;
    
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello Window :)");
    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);
}