#ifndef _MW_
#define _MW_


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


#include <iostream>
#include <vector>
#include <memory>
#include <vector>
#include "myobject.h"
//#include "mypicture.h"

extern int mouse_open(void);
extern void mouse_close(int);
extern int readmouse(int);

class MPicture;
using namespace std;
class MWindow{

public:
	MWindow()
	{
		mfd = mouse_open();

		int fd , ret ;
		struct fb_var_screeninfo fbi_var;//定义可变参数
		struct fb_fix_screeninfo fbi_fix;//定义固定参数
		struct fb_cmap cmap;
		fd = open("/dev/fb0",O_RDWR);
		if(fd < 0){
			perror("open");
			close(fd);
		}
#if 1
		ret = ioctl(fd,FBIOGET_VSCREENINFO,&fbi_var);
		if(ret < 0){
			perror("ioctl");
			exit(-1);
		}

		vwidth = fbi_var.xres;
		vheight = fbi_var.yres;

		ret = ioctl(fd,FBIOGET_FSCREENINFO,&fbi_fix);
		if(ret < 0){
			perror("ioctl");
			exit(-1);
		}
		rwidth = fbi_fix.line_length/4;
#endif
		addr = (unsigned int *)mmap(NULL,fbi_fix.smem_len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(addr == NULL){
			perror("mmap");
			ret = munmap(addr, fbi_fix.smem_len);
			exit(-1);
		}
		addrlen = fbi_fix.smem_len;
#if 0
		//put a mouse in
		pmouse = new MPicture(this, "1.bmp", vwidth/2, vheight/2, 300, 300, 0x3433, 0x543454);
	        addObject(pmouse);
#endif	
	}

	~MWindow()
	{
		mouse_close(mfd);
        	munmap(addr, addrlen);
	}

	void clear(int color=0xffffffff)
	{
		unsigned int *p = addr;

		int row = 0;
		int col = 0;
		for(;row<vheight; row++)
		{
			for(col=0; col<vwidth; col++)
			{
				*p++ = color;
			}
			p += (rwidth-vwidth);
		}

	}

	int xx, yy;
	void show(void)
	{
#if 1
		while(1)
		{

			clear();
			for(int i = 0; i<objs.size(); i++)
			{
				//		cout << i <<endl;
				//		cout << (int*)objs[i] <<endl;

				objs[i]->show();
				if(objs[i]->isfocus())
					pmouse = objs[i];
			}

			char c = readmouse(mfd);
			int dt = 5;
			xx = pmouse->getx();
			yy = pmouse->gety();
		//	cout<< xx <<endl;
		//	cout<< yy <<endl;

			switch(c)
			{   
				case 'u': yy -= dt; break;
				case 'd': yy += dt; break;
				case 'l': xx -= dt; break;
				case 'r': xx += dt; break;

			}   	
			pmouse->setpos(xx, yy);
		}
#endif
	}

	void addObject(MObject *ob)
	{
		objs.push_back(ob);
	}

	unsigned int *getaddr(void)
	{
		return addr;
	}

	int getvwidth()
	{
		return vwidth;
	}

	int getvheight()
	{
		return vheight;
	}

	int getrwidth()
	{
		return rwidth;
	}
private:
	vector<MObject *> objs;
	
	unsigned int *addr;
	int addrlen;

        int vwidth;
        int vheight;

        int rwidth;

	int mfd;
//	MPicture *pmouse;
	MObject *pmouse;
};

#endif

