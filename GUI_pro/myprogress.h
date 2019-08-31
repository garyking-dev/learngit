/*===============================================================
*   Copyright (C) 2019 All rights reserved.
*   
*   文件名称：myprogress.h
*   创 建 者：燕灵诀
*   创建日期：2019年08月30日
*   描    述：
*
*   更新日志：
*
================================================================*/
#ifndef _MYP_
#define _MYP_

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
#include <iostream>
using namespace std;

class MWindows;
class MProgress:public MObject{
public:
	MProgress(MWindow *parent,int x=0, int y=0, int w=5, int h=5, int ec=0, int bc=0,int pr=50)
	:MObject(parent, x, y, w, h, ec, bc),pro(pr)	
	{
	
	}
	void show(void){
		unsigned int *addr = getparent()->getaddr();
		int rwidth = getparent()->getrwidth();
		int vwidth = getparent()->getvwidth();
		int vheight = getparent()->getvheight();
		
		addr += (gety()*rwidth+getx());
		int row = 0;
		int col = 0;
		for(;row<getheight(); row++)
		{
			for(col=0; col<set(getwidth()); col++)
			{
				*addr++ = getbcolor();
			}
			addr += (rwidth-set(getwidth()));
		}

		addr = getparent()->getaddr() + (gety()*rwidth+getx());
		for(col=0; col<getwidth(); col++)
			*addr++ = getecolor();
		addr = getparent()->getaddr() + ((gety()+getheight())*rwidth+getx());
		for(col=0; col<getwidth(); col++)
			*addr++ = getecolor();

		addr = getparent()->getaddr() + (gety()*rwidth+getx());
		for(row=0; row<getheight(); row++)
		{
			*addr = getecolor();
			addr += rwidth;
		}
		addr = getparent()->getaddr() + (gety()*rwidth+getx()+getwidth());
		for(row=0; row<getheight(); row++)
		{
			*addr = getecolor();
			addr += rwidth;
		}
		
	

	}
	int set(int width){
		return width =width*pro/100;
	}
private:
	int pro;
};

#endif
