/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:12:45 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 14:34:02 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H

# define CUB_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "minilibx-linux/mlx.h"
# define BUFFER_SIZE 32

typedef struct			s_data
{
	void				*mlx_ptr;
	void				*mlx_win;
}						t_data;

typedef struct			s_event
{
	int					esc;
	int					left;
	int					right;
	int					forward;
	int					back;
	int					turn_l;
	int					turn_r;
	double				ms;
	double				rt;
}						t_event;

typedef struct			s_parse
{
	int					r_x;
	int					r_y;
	int					w;
	int					h;
	char				*path_tn;
	char				*path_ts;
	char				*path_tw;
	char				*path_te;
	char				*path_sprite;
	unsigned int		color_f;
	unsigned int		color_c;
	int					index_get;
}						t_parse;

typedef struct			s_map
{
	int					w;
	int					h;
	char				**map;
	int					start_x;
	int					start_y;
	char				direction;
	int					nbsprite;
}						t_map;

typedef union			u_color
{
	unsigned int		color;
	struct				s_argb
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					argb;
}						t_color;

typedef struct			s_ray
{
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				camerax;
	double				raydirx;
	double				raydiry;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	int					mapx;
	int					mapy;
	int					stepx;
	int					stepy;
	double				perwalldist;
	int					side;
	int					hit;
}						t_ray;

typedef struct			s_text_rsc
{
	int					lineheight;
	int					drawstart;
	int					drawend;
	double				wallx;
	int					x;
	int					y;
	int					w;
	int					h;
}						t_text_rsc;

typedef	struct			s_text
{
	void				*ptr;
	char				*img;
	int					bpp;
	int					sl;
	int					end;
}						t_text;

typedef struct			s_sprite
{
	double				x;
	double				y;
}						t_sprite;

typedef	struct			s_sprite_rsc
{
	int					i;
	int					d;
	int					nb;
	double				x;
	double				y;
	double				inv_det;
	double				transformx;
	double				transformy;
	int					screenx;
	int					h;
	int					w;
	int					drawstartx;
	int					drawendx;
	int					drawstarty;
	int					drawendy;
	int					textw;
	int					texth;
	int					texx;
	int					texy;
	int					text;
}						t_sprite_rsc;

typedef	struct			s_camera
{
	int					lineheight;
	int					drawstart;
	int					drawend;
}						t_camera;

typedef struct			s_image
{
	char				*ptr;
	char				*adr;
	int					bpp;
	int					sl;
	int					end;
}						t_image;

typedef struct			s_save
{
	int					fd;
	int					size;
	int					unused;
	int					offset_begin;
	int					head_bytes;
	short int			plane;
	short int			bpp;
}						t_save;

typedef struct			s_cub
{
	t_map				*m;
	t_parse				*p;
	t_data				*d;
	t_ray				*r;
	t_camera			*cam;
	t_image				*im;
	t_event				*e;
	t_text				*t;
	t_sprite			s[50];
	double				*buff;
	int					save;
	int					text;
}						t_cub;

void					ft_read_map(char *line, int fd, t_parse *parse);
int						ft_position_player(t_cub *c);
int						ft_check_extend(char *str);
char					*ft_texture(char *str);
int						ft_malloc_maps(t_map *maps);
int						ft_check(t_parse *parse);
int						ft_check_error_map_v2(char **maps, t_cub *c);
int						check_around(char **map, int i, int j, int h);
int						ft_main_error(int id, char *str, t_cub *c);
void					ft_error_parse_map(int id);
int						check_info(t_cub *c);
int						chrd(char c);
void					ft_resolution(t_parse *parse, char *str);
void					ft_init_parse_maps(t_parse *parse, t_map *maps);
void					ft_init_event(t_cub *c);
void					ft_init_ray(t_cub *c);
void					ft_init_dir_pos(t_cub *c);
void					ft_init_image(t_cub *c);
void					ft_get_map(t_map *maps, char *line, int i, t_cub *c);
void					ft_affiche_map(t_map *maps);
int						ft_parcing(t_parse *parse, char *line, t_map *maps);
unsigned int			ft_color_fc(char *str);
int						ft_press(int key, t_cub *c);
int						ft_staypress(int key, t_cub *c);
void					ft_move(t_cub *c);
void					ft_move2(t_cub *c);
void					ft_rota(t_cub *c);
int						ft_close(t_cub *c);
void					ft_ray(t_cub *c);
int						ft_screen(t_cub *c);
void					ft_side_step(t_cub *c);
void					ft_dda(t_cub *c, int x);
void					ft_wall(t_cub *c, int x);
void					ft_wall_we(t_cub *c, int x);
void					ft_wall_ns(t_cub *c, int x);
void					ft_wall_text_ns(t_cub *c, t_text_rsc *trsc, int x);
void					ft_wall_text_we(t_cub *c, t_text_rsc *trsc, int x);
void					ft_wall_texture(t_cub *c, int x);
void					ft_initvaltext(t_cub *c, t_text_rsc *trsc);
int						ft_init_text(t_cub *c, t_text *text, int w, int h);
int						ft_init_text2(t_text *text, t_cub *c);
void					ft_sprite(t_cub *c);
void					ft_texture_sprite(t_cub *c, t_sprite_rsc *srsc);
void					ft_dsprite(t_sprite_rsc *srsc, int *sp_order, t_cub *c);
void					ft_sp_rk(int *sp_order, double *sp_dist, int nbsprite);
void					ft_init_sp(t_cub *c, int *sp_order, double *sp_dist);
void					ft_pos_sprite(t_cub *c);
void					ft_init_save(t_cub *c, t_save *sv);
void					ft_write_text_bmp_file(t_cub *c, int fd);
void					ft_wrt_bmp_file(t_cub *c);
void					ft_save(t_cub *c);
int						ft_init_cub(t_cub *cube, char **av);
void					ft_gnl_cub(t_cub *cube, char *av);
void					ft_gnl_cub2(t_cub *cube, char *av);
int						ft_cubed(t_cub *cube);
void					ft_putstr(char *s);
void					ft_free_error(t_cub *c, int id);
void					ft_check_resolution(t_cub *c);
int						ft_atoi(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strchr(const char *s, char c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						get_next_line(int fd, char **line);
char					*ft_substr(char *s, unsigned int start, size_t len);
char					*ft_strjoin(char *s1, char *s2);
int						ft_checkerror(int fd, char **line, char **str);
char					*ft_strdup(char *s);
size_t					ft_strlen(char *str);
int						get_next_line_2(int ret, char **str, size_t i);
#endif
