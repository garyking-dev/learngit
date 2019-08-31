#include "myobject.h"

class MWindow;
class MPoint:public MObject{
public:
	MPoint(MWindow *parent, int x=0, int y=0, int w=5, int h=5, int ec=0, int bc=0)
	:MObject(parent, x, y, w, h, ec, bc)
	{
	}

	void show(void)
	{
		unsigned int *addr = getparent()->getaddr();
		int rwidth = getparent()->getrwidth();
		int vwidth = getparent()->getvwidth();
		int vheight = getparent()->getvheight();


		addr += (gety()*rwidth+getx());
		int row = 0;
		int col = 0;
		for(;row<getheight(); row++)
		{
			for(col=0; col<getwidth(); col++)
			{
			   	*addr++ = getbcolor();
			}
			addr += (rwidth-getwidth());
		}

		/////////////////////////////////////////////
		if(isfocus() )
		{
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
	}
};
