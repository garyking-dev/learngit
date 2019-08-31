#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>

#define DEV_NAME   "/dev/input/event3"

#define DBG_PRINTF printf
//#define DBG_PRINTF(...)

struct input_event input_mouse;

int mouse_open()
{
	int fd = open(DEV_NAME, O_RDONLY);
	if (fd < 0)
	{
		printf("can't open %s\n",DEV_NAME);
		return -1;
	}

	return fd;	
}

int readmouse(int fd)
{
	int retval;
	fd_set readfds;

	while(1)
	{
		FD_ZERO( &readfds );  
		FD_SET( fd, &readfds );    
		retval = select( fd+1, &readfds, NULL, NULL, NULL);  
		if(retval==0) 
		{  
			printf( "Time out!\n" );  
		}  
		if(FD_ISSET(fd, &readfds)) 
		{  
			read(fd, &input_mouse,sizeof(struct input_event)); 
			switch(input_mouse.type)
			{
			case EV_KEY:
				switch(input_mouse.code)
				{
				case BTN_LEFT:
					if(input_mouse.value==1)
						;//DBG_PRINTF("the left is pressed!\n");
						
					else
						;//DBG_PRINTF("the left is released!\n");
					break;
				case BTN_RIGHT:
					if(input_mouse.value==1)
						;//DBG_PRINTF("the right is press!\n");	
					break;
				case BTN_MIDDLE:
					if(input_mouse.value==1)
						;//DBG_PRINTF("the middle is press!\n");
					break;
				}
				break;

			case EV_REL:
				switch(input_mouse.code)
				{
				case REL_X:
					if(input_mouse.value>0)
						return 'r';//DBG_PRINTF("right!\n");
					else if(input_mouse.value<0)
						return 'l';//DBG_PRINTF("left!\n");
					break;
				case REL_Y:
					if(input_mouse.value<0)
						return 'u';//DBG_PRINTF("up!\n");
					else if(input_mouse.value>0)
						return 'd';//DBG_PRINTF("down!\n");
					break;
				}
				break;
			}
		}	
	}
}

void mouse_close(int fd)
{
	
	close(fd);
}
