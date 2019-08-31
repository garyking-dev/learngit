#ifndef _MPIX_
#define _MPIX_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "myobject.h"

#pragma pack(1)

struct bmp_file //BMP文件头结构
{
        char type[2];//位图文件的类型，必须为BM，我这里类型不对，所以显示有误。
        unsigned int size;//位图文件的大小，以字节为单位
        short rd1;// 位图文件保留字，必须为0
        short rd2;// 位图文件保留字，必须为0
        unsigned int offset;// 位图数据的起始位置，以相对于位图
};

struct bmp_info//图像信息区
{
        unsigned int bsize;//本结构体所占用字节数,即40个字节
        int width;// 位图的宽度，以像素为单位，像素数量是4字节对齐的
        int height;// 位图的高度，以像素为单位
        unsigned short planes;// 目标设备的级别，必须为1
        unsigned short count;// 每个像素所需的位数，必须是1(双色）// 4(16色)，8(256色)或24(真彩色)之一
        unsigned int compression;// 位图压缩类型，必须是 0(不压缩),// 1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
        unsigned int sizeimage;// 位图的大小，以字节为单位
        unsigned int xmeter;// 位图水平分辨率，每米像素数
        unsigned int ymeter;// 位图垂直分辨率，每米像素数
        unsigned int cused;// 位图实际使用的颜色表中的颜色数
        unsigned int cimportant;// 位图显示过程中重要的颜色数
};

struct bmp_head {
        struct bmp_file file;
        struct bmp_info info;

};



class MWindow;
class MPicture:public MObject{
public:
        MPicture(MWindow *parent, const char *filename, int x=0, int y=0, int w=5, int h=5, int ec=0, int bc=0)
        :MObject(parent, x, y, w, h, ec, bc) , filename(filename)
        {   
        }   

        void show(void)
	{   
		unsigned int *addr = getparent()->getaddr();
		int rwidth = getparent()->getrwidth();
		int vwidth = getparent()->getvwidth();
		int vheight = getparent()->getvheight();

		//width,hight,bpp
		struct bmp_head header = {0};
		int fd = open(filename, O_RDONLY);
		read(fd, &header, sizeof(header));
		int pwidth = header.info.width;
		int pheight = header.info.height;
		int pbpp = header.info.count;
		//RGB
		unsigned char RGB_[pwidth*pheight*pbpp/8];
		read(fd, RGB_, sizeof(RGB_));
		unsigned char *RGB = RGB_;

		unsigned int *p = addr+(rwidth*(gety()+pheight)+getx());
		int row = 0;
		int col = 0;
		for(;row<pheight; row++)
		{
			for(col=0; col<pwidth; col++)
			{
				*p++ = (*RGB) | (*(RGB+1)<<8) | *(RGB+2)<<16;
				//              *p = RED;
				RGB += 3;
			}
			p -= (rwidth+pwidth);
		}
		close(fd);


	}
private:
	const char *filename;

};

#endif

