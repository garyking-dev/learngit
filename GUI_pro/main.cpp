#include "mywindow.h"
#include "mypoint.h"
#include "mypicture.h"
#include "myprogress.h"
#include <iostream>

using namespace std;


int main()
{
	MWindow w;
#if 0
	MPoint *pt = new MPoint(&w, 200, 200, 50, 50, 0xff00ff00, 88883);
	w.addObject(pt);

	MPoint *pt1 = new MPoint(&w, 100, 100, 100, 100, 0, 0xffff0000);
	pt1->setfocus(true);
	w.addObject(pt1);

	MPicture *pc = new MPicture(&w, "1.bmp", 300, 300, 300, 300, 0x3433, 0x543454);
	w.addObject(pc);

	MPicture *pc1 = new MPicture(&w, "1.bmp", 100, 400, 300, 300, 0x3433, 0x543454);
	w.addObject(pc1);

//	MButton *bt = new MButton;
//	w.addObject(bt);
#else   
	int i=0;
	while(1){
	MProgress *pg = new MProgress(&w, 0, 0, 100, 50, 0xffff0000, 0xff00ff00, i+50);
//	MProgress *pg = new MProgress(&w);
	w.addObject(pg);
#endif  
	w.show();
	sleep(1);
	cout<<++i<<endl;}
}
