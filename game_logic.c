/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:57:50 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/07 17:02:24 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"       ///LEVA I PRINTF

int ft_key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_closegame(data);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		ft_move_player(data, keysym);
	return (0);
}

void try_move(t_data *data, int y, int x)
{
	static int i = 0;
	static int j = 0;

	if (y < 0 || x < 0)
		return;
	if (data->map.matrix[y][x] == '0' || data->map.matrix[y][x] == 'C' || data->map.matrix[y][x] == 'E')
	{
		if (data->map.matrix[y][x] == 'C')
		{
			i++;
			charater_tranform_collect(data, i);
		}
		find_Player(data);
		if (j == 1)
			from_exit_to_grass(data, i, j);
		else
			data->map.matrix[data->img.character.y][data->img.character.x] = '0';
		printf("i = %d\n", i);
		if (data->map.matrix[y][x] == 'E')
			j = from_grass_to_exit(data, i); //per mettere 1
		data->map.matrix[y][x] = 'P';
		data->img.character.y = y;
		data->img.character.x = x;
		ft_print_matrix(data->map.matrix);
	}
}

void charater_tranform_collect(t_data *data, int i)
{
	if (i == 1)// senza parentesi funziona?
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
		data->img.character.imgbase = put_xmp(data->mlx,
											  "immage/1catcharacter.xpm", &data->img.character.with,
											  &data->img.character.height);
	else if (i == 2)
	{
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
		data->img.character.imgbase = put_xmp(data->mlx,
											  "immage/2catcharacter.xpm", &data->img.character.with,
											  &data->img.character.height);
	}
	else if (i == 3)
	{
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
		data->img.character.imgbase = put_xmp(data->mlx,
											  "immage/3catcharacter.xpm", &data->img.character.with,
											  &data->img.character.height);
	}
	if (i == data->map.countcoll)
	{
		mlx_destroy_image(data->mlx, data->img.exit.img);
		data->img.exit.img = put_xmp(data->mlx, "immage/exit.xpm",
									 &data->img.exit.with, &data->img.exit.height);
	}
}

int	from_exit_to_grass(t_data *data, int i, int j)
{
			mlx_destroy_image(data->mlx, data->img.character.imgbase);
			data->map.matrix[data->img.character.y][data->img.character.x] = 'E';
			j = 0;
			if (i == 0)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/basic_character.xpm", &data->img.character.with,
													  &data->img.character.height);
			else if (i == 1)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/1catcharacter.xpm", &data->img.character.with,
													  &data->img.character.height);
			else if (i == 2)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/2catcharacter.xpm", &data->img.character.with,
													  &data->img.character.height);
			else if (i >= 3)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/3catcharacter.xpm", &data->img.character.with,
													  &data->img.character.height);
			return (1);
}

void	from_grass_to_exit(t_data *data, int i)
{
	if (i == data->map.countcoll)
				ft_closegame(data);
			mlx_destroy_image(data->mlx, data->img.character.imgbase);
			if (i == 0)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/basic_character_exit.xpm",
													  &data->img.character.with, &data->img.character.height);
			else if (i == 1)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/1character_exit.xpm", &data->img.character.with,
													  &data->img.character.height);
			else if (i == 2)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/2character_exit.xpm", &data->img.character.with,
													  &data->img.character.height);
			else if (i >= 3)
				data->img.character.imgbase = put_xmp(data->mlx,
													  "immage/3character_exit.xpm", &data->img.character.with,
													  &data->img.character.height);
}

int ft_move_player(t_data *data, int keysym)
{
	int y;
	int x;

	y = data->img.character.y;
	x = data->img.character.x;
	if (keysym == KEY_W)
		try_move(data, y - 1, x);
	if (keysym == KEY_A)
		try_move(data, y, x - 1);
	if (keysym == 115)
		try_move(data, y + 1, x);
	if (keysym == 100)
		try_move(data, y, x + 1);
	return (0);
}

void ft_print_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		write(1, matrix[i], ft_strlen(matrix[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

int ft_closegame(t_data *data)
{
	int i;

	i = 0;
	if (data->map.matrix != NULL)
	{
		while (i != count_lines(data->map.matrix))
			free(i++, data->map.matrix[i]);
		free(data->map.matrix);
	}
	if (data->img.character.imgbase != NULL)
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
	if (data->img.wall.img != NULL)
		mlx_destroy_image(data->mlx, data->img.wall.img);
	if (data->img.exit.img != NULL)
		mlx_destroy_image(data->mlx, data->img.exit.img);
	if (data->img.collectible.img != NULL)
		mlx_destroy_image(data->mlx, data->img.collectible.img);
	if (data->img.grass.img != NULL)
		mlx_destroy_image(data->mlx, data->img.grass.img);
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx != NULL)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data); // da mettere nel free
	exit(1);
	return (0);
}

static char *ft_result(char *s1, size_t start, size_t end, int *trimmed)
{
	char *dst;
	size_t i;

	i = 0;
	if (!s1[start])
	{
		free(s1);
		return (NULL);
	}
	dst = ft_calloc((end - start + 2), sizeof(char));
	if (dst == NULL)
		return (free(dst), NULL);
	while (start <= end)
	{
		dst[i] = s1[start];
		start++;
		i++;
	}
	if (trimmed)
		*trimmed += ft_strlen(s1) - ft_strlen(dst);
	free(s1);
	if (ft_strlen(dst) == 0)
		return (free(dst), NULL);
	return (dst);
}

char *ft_strtrimfree(char *s1, char *set, int *trimmed)
{
	size_t start;
	size_t end;

	start = 0;
	end = 0;
	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_result(s1, 0, 0, trimmed));
	while (s1[start] && ft_isinset(s1[start], set) == 1)
		start++;
	while (s1[end])
		end++;
	if (start == end)
		return (ft_result(s1, start, end, trimmed));
	end--;
	while (ft_isinset(s1[end], set) == 1)
		end--;
	return (ft_result(s1, start, end, trimmed));
}

int ft_isinset(char c, char *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

void find_Player(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (data->map.matrix[y])
	{
		while (data->map.matrix[y][x])
		{
			if (data->map.matrix[y][x] == 'P')
			{
				data->img.character.x = x;
				data->img.character.y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
