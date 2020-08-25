/*Many ideas used in this status bar were borrowed from Trilby White dwm status bar:
https://github.com/TrilbyWhite/dwmStatus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <math.h>

//Info files to open
#define	        AC_FILE  "/sys/class/power_supply/AC/online"
#define	       BAT_FILE  "/sys/class/power_supply/BAT0/capacity"
#define 		 	 BAT_PNOW	 "/sys/class/power_supply/BAT0/charge_now"
#define 		 	 BAT_ENOW  "/sys/class/power_supply/BAT0/voltage_now"
#define	      WLAN_FILE  "/proc/net/wireless"
#define	       CPU_FILE  "/proc/stat"
#define         HDDPATH  "/"

//Status bar strings. "\x06a" etc are colors defined in dwm's config.h (statuscolor patch, required). Unconventional unicode symbols are Tamsynmod font icons. 
#define       AC_STRING  "\x06Â\x0don | " 
#define      BAT_STRING  "\x05ð\x0d%d%% (%.0f:%02.0f) | "
#define   UPTIME_STRING  "\x07È\x0d%d:%02d | "
#define     WLAN_STRING  "\x08¤\x0d%d%% | "
#define  HDDFREE_STRING  "\x09¨\x0d%.2f Gb | "
#define USEDSWAP_STRING  "\x0aÐ\x0d%.2f Gb | "
#define  USEDMEM_STRING  "\x0b×\x0d%.0f Mb | "
#define	 CPULOAD_STRING  "\x0cÑ\x0d%.1Lf%% | "
#define CURRTIME_STRING  "\x05É\x0d%a %b %d @ %H:%M | "

int main()
{
	    Display *dpy;
	    Window root;
	    time_t current;
	    FILE *infile;
	    int value, value2;
	    float fvalue, fvalue2; 
	    char itemstatus[20], bar[90];
	    long double a[4], b[4], loadavg;
	    const char *filename = HDDPATH;	    
	    const long  mbvalue = 1024*1024;
	    const float gbvalue = 0.000976563; 

	    //Setup X display and root window id:
	    dpy=XOpenDisplay(NULL);
	    if (dpy == NULL)
	    {
			fprintf(stderr, "ERROR: could not open display\n");
			exit(1);
	    }
	    root = XRootWindow(dpy,DefaultScreen(dpy)); 

	    //MAIN LOOP STARTS HERE:

	    for (;;)		
	    {
			bar[0]='\0';

			//AC ADAPTER AND BATTERY STATUS 
			infile = fopen(AC_FILE, "r");
			fscanf(infile, "%d", &value);
			fclose(infile);

			infile = fopen(BAT_FILE, "r");
			fscanf(infile, "%d", &value2);
			fclose(infile);
			//Calculates remaining battery time
			infile = fopen(BAT_PNOW, "r");
			fscanf(infile, "%f", &fvalue);
			fclose(infile);

			infile = fopen(BAT_ENOW, "r");
			fscanf(infile, "%f", &fvalue2);
			fclose(infile);

			fvalue = fvalue2 / fvalue;
			fvalue2 = floor(fvalue);
			fvalue2 = (fvalue - fvalue2) * 60;

			//if ACAD is online (1)
			if (value == 1)
			{
				    sprintf(itemstatus, AC_STRING);
			}
			//if ACAD is offline shows battery percentage
			else
			{
				    sprintf(itemstatus, BAT_STRING, value2, fvalue, fvalue2);
			}
			strcat(bar, itemstatus);

			//UPTIME STATUS
			struct sysinfo query;
			sysinfo(&query);
			value = ((query.uptime) / 60) - (((query.uptime) / 3600) * 60 );
			value2 = (query.uptime) / 3600;

			sprintf(itemstatus, UPTIME_STRING, value2, value);
			strcat(bar, itemstatus);


			//WIFI LINK QUALITY
			infile = fopen(WLAN_FILE, "r");
			fscanf(infile, "%*[^\n]\n%*[^\n]\nwlp3s0: %*d %d", &value);
			fclose(infile);
			sprintf(itemstatus, WLAN_STRING, value);
			strcat(bar, itemstatus);

			//FREE HDD SPACE
			struct statvfs info;
			if (!statvfs(filename, &info))
			{ 
				    unsigned long /*blocks,*/ blksize, freeblks, /*disk_size, used,*/ free; 

				    blksize = info.f_bsize;
				    // blocks = info.f_blocks;
				    freeblks = info.f_bavail;

				    // disk_size = blocks * blksize;
				    free = freeblks * blksize;
				    // used = disk_size - free;

				    fvalue = (free / mbvalue) * gbvalue; 

				    sprintf(itemstatus, HDDFREE_STRING, fvalue);  
				    strcat(bar, itemstatus); 		 
			}

			//Used swap space
			unsigned long swptotal, swpfree; 

			swptotal = query.totalswap;
			swpfree  = query.freeswap;
			fvalue = ((swptotal - swpfree) / mbvalue) * gbvalue;
			sprintf(itemstatus, USEDSWAP_STRING, fvalue);
			strcat(bar, itemstatus);

			//Used RAM
			unsigned long ramtotal, ramfree, rambuffr;

			ramtotal = query.totalram;
			ramfree  = query.freeram;
			fvalue   = (ramtotal - ramfree) / mbvalue;
			sprintf(itemstatus, USEDMEM_STRING, fvalue);
			strcat(bar, itemstatus);

			//CPU Load 
			infile = fopen(CPU_FILE, "r");
			fscanf(infile, "%*s %Lf %Lf %Lf %Lf", &a[0],&a[1],&a[2],&a[3]);
			fclose(infile);
			sleep(1);
			infile = fopen(CPU_FILE, "r");
			fscanf(infile, "%*s %Lf %Lf %Lf %Lf", &b[0],&b[1],&b[2],&b[3]);
			fclose(infile);

			loadavg = 100.0 * (((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3])));
			sprintf(itemstatus, CPULOAD_STRING, loadavg);
			strcat(bar, itemstatus);

			//Time
			struct tm *timeinfo;
			time(&current);
			timeinfo = localtime(&current);
			strftime(itemstatus, strlen(CURRTIME_STRING) + 2, CURRTIME_STRING, timeinfo); 
			strcat(bar, itemstatus); 

			//Set root window name (root window name == our status bar)
			XStoreName(dpy, root, bar);
			XFlush(dpy);
			//		 sleep(1); // The CPU load code above already has a sleep of 1 second. 

	    }
	    return 0;
}
