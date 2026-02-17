/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:45 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/17 14:48:40 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(t_game *game, char *msg)
{
	printf("Error\n");
	if (msg)
		printf("%s\n", msg);
	else
		perror("System Error");
	if (game)
		free_game(game);
	exit(1);
}
