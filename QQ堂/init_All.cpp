#include "init_All.h"

void init_image()
{
	PIMAGE image[8];
	for(int i=0;i<=7;i++)
		image[i]=newimage();
	getimage(image[bomb-1],"ը��.png");
	getimage(image[wood-1],"ľ��.png");
	getimage(image[rock-1],"rock.png");
	getimage(image[floor-1],"��Դ.png");
	getimage(image[shoe-1],"Ь.png");
	getimage(image[medicine-1],"ҩ.png");
	getimage(image[powder-1],"ǿ��ҩ.png");
	getimage(image[diaosu-1],"����.png");
}