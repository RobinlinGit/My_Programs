#include "init_All.h"

void init_image()
{
	PIMAGE image[8];
	for(int i=0;i<=7;i++)
		image[i]=newimage();
	getimage(image[bomb-1],"Õ¨µ¯.png");
	getimage(image[wood-1],"Ä¾¿é.png");
	getimage(image[rock-1],"rock.png");
	getimage(image[floor-1],"¿éÔ´.png");
	getimage(image[shoe-1],"Ð¬.png");
	getimage(image[medicine-1],"Ò©.png");
	getimage(image[powder-1],"Ç¿Á¦Ò©.png");
	getimage(image[diaosu-1],"µñÏñ.png");
}