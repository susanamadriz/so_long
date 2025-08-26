#include "MLX42/include/MLX42/MLX42.h"
#include "so_long.h"

int WIDTH = 650;

int HEIGHT = 480;

#include "so_long.h"

static mlx_image_t* img;

void ft_hook(void* param)
{
    mlx_t* mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W)) 
        img->instances[0].y -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
        img->instances[0].y += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
        img->instances[0].x -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
        img->instances[0].x += 5;
}

int32_t main(int argc, char **argv)
{
    printf("size de char ** %li", sizeof(char **));
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
    if (!mlx)
    {
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    mlx_texture_t* player = mlx_load_png("assets/player.png");
	mlx_texture_t* floor = mlx_load_png("assets/floor.png");
    if (!texture)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    img = mlx_texture_to_image(mlx, texture);
	mlx_image_t* img2 = mlx_texture_to_image(mlx, texture2);
    if (!img)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    if (mlx_image_to_window(mlx, img2, 0, 0) == -1)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }
    mlx_image_to_window(mlx, img, 0, 0);
    mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

// int main()
// {
// 	char **new_map;
// 	int i;
	
// 	i = 0;
// 	new_map = read_map("./maps/example.ber");
// 	while (new_map[i])
// 	{
// 		printf("%s", new_map[i]);
// 		i++;
// 	}
// 	printf("result: %i", char_check(new_map));
// 	free (new_map);
// 	return (0);
// }