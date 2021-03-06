/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:01:46 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/01 01:42:53 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	init_header(int *screen, t_bmp_header *header)
{
	header->type = 0x4D42;
	header->size = ((screen[WIDTH] + screen[HEIGHT]) * 4) + 54;
	header->reserved = 0x0;
	header->offset = 54;
	header->dib_header_size = 40;
	header->width_px = screen[WIDTH];
	header->height_px = screen[HEIGHT];
	header->num_planes = 1;
	header->bits_per_pixel = 32;
	header->compression = 0;
	header->image_size_bytes = ((screen[WIDTH] + screen[HEIGHT]) * 4);
	header->x_resolution_ppm = 3200;
	header->y_resolution_ppm = 3200;
	header->num_colors = 0;
	header->important_colors = 0;
}

static void	fill_bmp_header(int fd, t_bmp_header header)
{
	write(fd, &header.type, 2);
	write(fd, &header.size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &header.dib_header_size, 4);
	write(fd, &header.width_px, 4);
	write(fd, &header.height_px, 4);
	write(fd, &header.num_planes, 2);
	write(fd, &header.bits_per_pixel, 2);
	write(fd, &header.compression, 4);
	write(fd, &header.image_size_bytes, 4);
	write(fd, &header.x_resolution_ppm, 4);
	write(fd, &header.y_resolution_ppm, 4);
	write(fd, &header.num_colors, 4);
	write(fd, &header.important_colors, 4);
}

static void	fill_bmp(t_cub *cub, int fd, t_data *img, int *screen)
{
	int	line;
	int	index;

	line = screen[HEIGHT];
	while (line >= 0)
	{
		index = line * img->line_length;
		if (write(fd, &img->data[index], img->line_length) <= 0)
			return_error(cub, -111);
		line--;
	}
}

void	save_bmp(t_cub *cub)
{
	t_bmp_header	header;
	int				fd;
	char			*file_name;

	file_name = "./bmp_images/cub.bmp";
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!(fd))
		return_error(cub, -111);
	init_header(cub->settings.screen, &header);
	fill_bmp_header(fd, header);
	fill_bmp(cub, fd, &cub->img, cub->settings.screen);
	close(fd);
	printf("cub.bmp created\n");
	exit(0);
}
