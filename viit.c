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

	printf("\e[?1049h\e[?25l");
	for (int y = 0; y < theight; y++) {
		printf("\e[%d;0H", y + 1);
		for (int x = 0; x < twidth; x++) {
			int imgx = x * iwidth / twidth;
			int timgy = (y * 2 + 0) * iheight / (theight * 2);
			int bimgy = (y * 2 + 1) * iheight / (theight * 2);
			unsigned char *offt = img_data + (timgy * iwidth + imgx) * num_channels;
			unsigned char *offb = img_data + (bimgy * iwidth + imgx) * num_channels;
			int rt = offt[0];
			int gt = offt[1];
			int bt = offt[2];
			int rb = offb[0];
			int gb = offb[1];
			int bb = offb[2];
			printf("\e[48;2;%d;%d;%dm\e[38;2;%d;%d;%dm\u2584", rt, gt, bt, rb, gb, bb);
		}
	}

	getchar();
	printf("\e[?1049l\e[?25h");

	stbi_image_free(img_data);
}

