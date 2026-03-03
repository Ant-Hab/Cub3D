/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:13:14 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/03 18:06:00 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void print_sep(char *title)
{
    printf("\n\033[1;34m--- %s ---\033[0m\n", title);
}

void    print_textures(t_game *game)
{
    print_sep("TEXTURES & COLORS");
    if (!game || !game->texture)
    {
        printf("Error: Texture struct is NULL\n");
        return ;
    }
    printf("NO: [%s]\n", game->texture->no ? game->texture->no : "NULL");
    printf("SO: [%s]\n", game->texture->so ? game->texture->so : "NULL");
    printf("WE: [%s]\n", game->texture->we ? game->texture->we : "NULL");
    printf("EA: [%s]\n", game->texture->ea ? game->texture->ea : "NULL");
    printf("Floor:   RGB(%d,%d,%d)\n",
        game->floor.r, game->floor.g, game->floor.b);
    printf("Ceiling: RGB(%d,%d,%d)\n",
        game->ceiling.r, game->ceiling.g, game->ceiling.b);
}

void    print_map(t_game *game)
{
    int i;
    int j;

    print_sep("MAP GRID");
    if (!game || !game->map || !game->map->grid)
    {
        printf("Error: Map grid is NULL\n");
        return ;
    }
    i = 0;
    while (game->map->grid[i])
    {
        printf("[%d] ", i);
        j = 0;
        while (game->map->grid[i][j])
        {
            if (game->map->grid[i][j] == 'N' || game->map->grid[i][j] == 'S' ||
                game->map->grid[i][j] == 'E' || game->map->grid[i][j] == 'W')
                printf("\033[1;32m%c\033[0m", game->map->grid[i][j]);
            else
                printf("%c", game->map->grid[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("Dimensions: %d x %d\n", game->map->width, game->map->height);
    printf("Player Start: [%d, %d] Direction: \033[1;32m%c\033[0m\n", 
        game->map->p_x, game->map->p_y, game->map->start_dir);
}

void    debug_validate_parsing(t_game *game)
{
    char    **tmp;

    print_sep("VALIDATION CHECK");
    if (!game || !game->map || !game->map->grid)
    {
        printf("Error: Cannot validate - Map/Grid NULL\n");
        return ;
    }
    tmp = copy_grid(game->map->grid, game->map->height);
    if (!tmp)
    {
        printf("Error: copy_grid failed\n");
        return ;
    }
    
    /* Using is_closed instead of the removed flood_fill */
    if (is_closed(tmp, game->map->p_x, game->map->p_y, game->map->height))
        printf("\033[1;32mMap Integrity: CLOSED (Valid)\033[0m\n");
    else
        printf("\033[1;31mMap Integrity: INVALID (Leaking)\033[0m\n");
    
    free_tab(tmp);
}
