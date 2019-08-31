#ifndef _MO_
#define _MO_

//#include "mywindow.h"

class MWindow;
class MObject{
public:
	MObject(MWindow *parent, int x=0, int y=0, int w=20, int h=10, int ec=0, int bc=0)
	:parent(parent),x(x), y(y), width(w), height(h), edgecolor(ec), brushcolor(bc)
	{
		focus = false;
	}

	virtual void show(void) = 0;

	void setfocus(bool x=true)
	{
		focus = x;
	}

	bool isfocus()
	{
		return focus;
	}

	void setpos(int a, int b)
	{
		x = a;
		y = b;
	}

	int getx()
	{
		return x;
	}

	int gety()
	{
		return y;
	}
	
	void setsize(int w, int h)
	{
		width = w;
		height = h;
	}
	
	int getecolor(void)
	{
		return edgecolor;
	}
	
	int getbcolor(void)
	{
		return brushcolor;
	}
	
	void setecolor(int color)
	{
		edgecolor = color;
	}

	void setbcolor(int color)
	{
		brushcolor = color;
	}

	MWindow * getparent()
	{
		return parent;
	}

	void setparent(MWindow *parent)
	{
		this->parent = parent;
	}

	int getwidth()
	{
		return width;
	}

	int getheight()
	{
		return height;
	}
	
private:
	int x;
	int y;
	int width;
	int height;

	int edgecolor;
	int brushcolor; 
	
	MWindow *parent;
	bool focus;
};

#endif

