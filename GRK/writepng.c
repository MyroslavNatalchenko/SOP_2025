/*
 * Copyright 2002-2008 Guillaume Cottenceau, 2015 Aleksander Denisiuk
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>


#define OUT_FILE "initials.png"
#define WIDTH 600
#define HEIGHT 600
#define COLOR_TYPE PNG_COLOR_TYPE_RGB
#define BIT_DEPTH 8


void abort_(const char * s, ...)
{
	va_list args;
	va_start(args, s);
	vfprintf(stderr, s, args);
	fprintf(stderr, "\n");
	va_end(args);
	abort();
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void create_png_file()
{
	width = WIDTH;
	height = HEIGHT;
        bit_depth = BIT_DEPTH;
        color_type = COLOR_TYPE;

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (y=0; y<height; y++)
		row_pointers[y] = (png_byte*) malloc(width*bit_depth*3);


}


void write_png_file(char* file_name)
{
	/* create file */
	FILE *fp = fopen(file_name, "wb");
	if (!fp)
		abort_("[write_png_file] File %s could not be opened for writing", file_name);


	/* initialize stuff */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		abort_("[write_png_file] png_create_write_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		abort_("[write_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		abort_("[write_png_file] Error during init_io");

	png_init_io(png_ptr, fp);


	/* write header */
	if (setjmp(png_jmpbuf(png_ptr)))
		abort_("[write_png_file] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, width, height,
		     bit_depth, color_type, PNG_INTERLACE_NONE,
		     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);


	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr)))
		abort_("[write_png_file] Error during writing bytes");

	png_write_image(png_ptr, row_pointers);


	/* end write */
	if (setjmp(png_jmpbuf(png_ptr)))
		abort_("[write_png_file] Error during end of write");

	png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
	for (y=0; y<height; y++)
		free(row_pointers[y]);
	free(row_pointers);

        fclose(fp);
}

void write_pixel(int x, int y,
                 png_byte cr, png_byte cg, png_byte cb){
    png_byte* row = row_pointers[y];
    png_byte* ptr = &(row[x*3]);

    ptr[0] = cr;
    ptr[1] = cg;
    ptr[2] = cb;
}

void bresenham(int i1, int j1, int i2, int j2,
               png_byte cr, png_byte cg, png_byte cb) {
    int m, b, j, P, i;

    if (j2 > j1 && i2 >= i1 && i2 - i1 <= j2 - j1) { // 2: вправо-вверх, угол больше 45°
        printf("Przyp 2\n");
        m = 2 * (i2 - i1);
        b = 0;
        write_pixel(i1, j1, cr, cg, cb);
        i = i1;
        P = j2 - j1;
        for (j = j1 + 1; j <= j2; j++) {
            b = b + m;
            if (b > P) {
                i = i + 1;
                b = b - 2 * P;
            }
            write_pixel(i, j, cr, cg, cb);
        }
    }
    else if (i2 > i1 && j2 >= j1 && j2 - j1 <= i2 - i1) { // 1: вправо-вверх, угол меньше 45°
        printf("Przyp 1\n");
        m = 2 * (j2 - j1);
        b = 0;
        write_pixel(i1, j1, cr, cg, cb);
        j = j1;
        P = i2 - i1;
        for (i = i1 + 1; i <= i2; i++) {
            b = b + m;
            if (b > P) {
                j = j + 1;
                b = b - 2 * P;
            }
            write_pixel(i, j, cr, cg, cb);
        }
    }
    else if (i2 > i1 && -j2 >= -j1 && -j2 + j1 <= i2 - i1) { // 3: вправо-вниз, угол меньше 45°
        printf("Przyp 3\n");
        m = 2 * (-j2 + j1);
        b = 0;
        write_pixel(i1, j1, cr, cg, cb);
        j = j1;
        P = i2 - i1;
        for (i = i1 + 1; i <= i2; i++) {
            b = b + m;
            if (b > P) {
                j = j - 1;
                b = b - 2 * P;
            }
            write_pixel(i, j, cr, cg, cb);
        }
    }
    else if (j1 > j2 && i2 >= i1 && i2 - i1 <= j1 - j2) { // 4: вправо-вниз, угол больше 45°
        printf("Przyp 4\n");
        m = 2 * (i2 - i1);
        b = 0;
        write_pixel(i1, j1, cr, cg, cb);
        i = i1;
        P = j1 - j2;
        for (j = j1 - 1; j >= j2; j--) {
            b = b + m;
            if (b > P) {
                i = i + 1;
                b = b - 2 * P;
            }
            write_pixel(i, j, cr, cg, cb);
        }
    }
    else { printf("broken\n");}
}

void draw_circle(int xc, int yc, int R, png_byte cr, png_byte cg, png_byte cb) {
    int i = 0;
    int j = R;
    int f = 5 - 4 * R;

    void draw_symmetric_pixels(int xc, int yc, int x, int y, png_byte cr, png_byte cg, png_byte cb) {
        write_pixel(xc + x, yc + y, cr, cg, cb);
        write_pixel(xc - x, yc + y, cr, cg, cb);
        write_pixel(xc + x, yc - y, cr, cg, cb);
        write_pixel(xc - x, yc - y, cr, cg, cb);
        write_pixel(xc + y, yc + x, cr, cg, cb);
        write_pixel(xc - y, yc + x, cr, cg, cb);
        write_pixel(xc + y, yc - x, cr, cg, cb);
        write_pixel(xc - y, yc - x, cr, cg, cb);
    }

    draw_symmetric_pixels(xc, yc, i, j, cr, cg, cb);

    while (i<j) {
        if (f > 0) {
            f=f+8*i-8*j+20;
            j=j-1;
        } else {
            f=f+8*i+12;
        }
        i=i+1;
        draw_symmetric_pixels(xc, yc, i, j, cr, cg, cb);
    }
}

void process_file(void)
{
	for (y=0; y<height; y++) {
		png_byte* row = row_pointers[y];
		for (x=0; x<width; x++) {
			png_byte* ptr = &(row[x*3]);
			ptr[0] = 255;
			ptr[1] = 255;
            ptr[2] = 200;
		}
	}

    float scale = 2;
    int dx = 130;
    int dy = 200;

    // Функция для преобразования координат
    #define TRANSFORM(X) (int)(scale*(X) + dx)
    #define TRANSFORM_Y(Y) (int)(scale*(Y) + dy)

    bresenham(TRANSFORM(15), TRANSFORM_Y(10), TRANSFORM(15), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(15), TRANSFORM_Y(80), TRANSFORM(25), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(25), TRANSFORM_Y(80), TRANSFORM(25), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(15), TRANSFORM_Y(10), TRANSFORM(25), TRANSFORM_Y(10), 255, 0, 0);

    bresenham(TRANSFORM(25), TRANSFORM_Y(10), TRANSFORM(25), TRANSFORM_Y(20), 255, 0, 0);
    bresenham(TRANSFORM(25), TRANSFORM_Y(20), TRANSFORM(50), TRANSFORM_Y(40), 255, 0, 0);
    bresenham(TRANSFORM(50), TRANSFORM_Y(40), TRANSFORM(50), TRANSFORM_Y(30), 255, 0, 0);
    bresenham(TRANSFORM(25), TRANSFORM_Y(10), TRANSFORM(50), TRANSFORM_Y(30), 255, 0, 0);

    bresenham(TRANSFORM(75), TRANSFORM_Y(10), TRANSFORM(75), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(75), TRANSFORM_Y(80), TRANSFORM(85), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(85), TRANSFORM_Y(80), TRANSFORM(85), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(75), TRANSFORM_Y(10), TRANSFORM(85), TRANSFORM_Y(10), 255, 0, 0);

    bresenham(TRANSFORM(75), TRANSFORM_Y(10), TRANSFORM(75), TRANSFORM_Y(20), 255, 0, 0);
    bresenham(TRANSFORM(50), TRANSFORM_Y(40), TRANSFORM(75), TRANSFORM_Y(20), 255, 0, 0);
    bresenham(TRANSFORM(50), TRANSFORM_Y(40), TRANSFORM(50), TRANSFORM_Y(30), 255, 0, 0);
    bresenham(TRANSFORM(50), TRANSFORM_Y(30), TRANSFORM(75), TRANSFORM_Y(10), 255, 0, 0);

    bresenham(TRANSFORM(100), TRANSFORM_Y(80), TRANSFORM(100), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(100), TRANSFORM_Y(10), TRANSFORM(110), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(110), TRANSFORM_Y(10), TRANSFORM(110), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(100), TRANSFORM_Y(80), TRANSFORM(110), TRANSFORM_Y(80), 255, 0, 0);

    bresenham(TRANSFORM(140), TRANSFORM_Y(80), TRANSFORM(140), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(140), TRANSFORM_Y(10), TRANSFORM(150), TRANSFORM_Y(10), 255, 0, 0);
    bresenham(TRANSFORM(150), TRANSFORM_Y(10), TRANSFORM(150), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(140), TRANSFORM_Y(80), TRANSFORM(150), TRANSFORM_Y(80), 255, 0, 0);

    bresenham(TRANSFORM(110), TRANSFORM_Y(10), TRANSFORM(110), TRANSFORM_Y(25), 255, 0, 0);
    bresenham(TRANSFORM(110), TRANSFORM_Y(25), TRANSFORM(140), TRANSFORM_Y(80), 255, 0, 0);
    bresenham(TRANSFORM(140), TRANSFORM_Y(80), TRANSFORM(140), TRANSFORM_Y(65), 255, 0, 0);
    bresenham(TRANSFORM(110), TRANSFORM_Y(10), TRANSFORM(140), TRANSFORM_Y(65), 255, 0, 0);

    draw_circle(300,300,200,0,0,0);
}


int main(int argc, char **argv)
{
	create_png_file();
	process_file();
	write_png_file(OUT_FILE);

        return 0;
}
