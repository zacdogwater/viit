#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "Provide an image\n");
		return 1;
	}

	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	int twidth = ws.ws_col;
	int theight = ws.ws_row;

	int iwidth, iheight, num_channels;	
	unsigned char *img_data = stbi_load(argv[1], &iwidth, &iheight, &num_channels, 0);

	printf("\e[?1049h");
	for (int y = 0; y < theight; y++) {
		printf("\e[%d;0H", y + 1);
		for (int x = 0; x < twidth; x++) {
			int imgy = y * iheight / theight;
			int imgx = x * iwidth / twidth;
			unsigned char *off = img_data + (imgy * iwidth + imgx) * num_channels;
			int r = off[0];
			int g = off[1];
			int b = off[2];
			printf("\x1b[48;2;%d;%d;%dm ", r, g, b);
		}
	}

	getchar();
	printf("\e[?1049l");

	stbi_image_free(img_data);
}
