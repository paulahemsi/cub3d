/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:01:46 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/13 04:46:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	init_header(t_configs *cub, t_bmp_header *header)
{
	header->type = 0x4D42;
	header->size = ((cub->screen_width + cub->screen_height) * 4) + 54;
	header->reserved = 0x0;
	header->offset = 54;
	header->dib_header_size = 40;
	header->width_px = cub->screen_width;
	header->height_px = cub->screen_height;
	header->num_planes = 1;
	header->bits_per_pixel = 32;
	header->compression = 0;
	header->image_size_bytes = ((cub->screen_width + cub->screen_height) * 4);
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

static void	fill_bmp(int fd, t_data *img)
{
	int line;

	line = img->cub->screen_height;
	while (line >= 0)
	{
		if (write(fd, &img->data[line * img->line_length], img->line_length) <= 0)
			return_error(-11);
		line--;
	}
}

static char	*define_name(t_configs *cub)
{
	char	*name;
	char	*aux;

	if (!(cub->bmp_id))
		return ("./bmp_images/cub.bmp");
	else
	{
		name = ft_itoa(cub->bmp_id);
		aux = ft_strjoin("./bmp_images/cub", name);
		free(name);
		name = ft_strjoin(aux, ".bmp");
		free(aux);
		return (name);
	}
}

void	save_bmp(t_data *img)
{
	t_bmp_header	header;
	int				fd;
	char			*file_name;

	//TODO colocar limitador de arquivos que pessoa pode salvar
	file_name = define_name(img->cub);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!(fd))
		return_error(-11);
	init_header(img->cub, &header);
	fill_bmp_header(fd, header);
	fill_bmp(fd, img);
	close(fd);
	if (!(img->cub->bmp_id))
	{
		printf("cub.bmp created\n");
		exit(0);
	}
	free(file_name);
}