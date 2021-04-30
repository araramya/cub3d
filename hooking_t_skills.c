#include <mlx.h>
#include <stdio.h>

typedef struct s_vars
{
    void *mlx;
    void *win;
}               t_vars;

int key_hook(int keycode, t_vars *vars)
{
    printf("Its HOOKING bitch\n");
}

int key_hook1(int keycode, t_vars *vars) //a key is pressed and it will print keycode 
{
    printf("%d\n", keycode);
}

//int mouse_hook()
int main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640,480, "Heloo Window");
   // mlx_key_hook(vars.win, key_hook, &vars);
    mlx_key_hook(vars.win, key_hook1, &vars);
    printf("printing, ending");
    mlx_key_hook(vars.win, key_hook, &vars);
    //mlx_mouse_hook(vars.win, mouse_hook, &vars)
    mlx_loop(vars.mlx);
}