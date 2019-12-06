// A simple homebrew to eject the disc tray of a PS2
// PS2Eject v0.3 Written by VTSTech (veritas@vts-tech.org)

// v0.3 12/6/2019 5:33:45 PM
// Now waits for button press to exit
// Otherwise exits in 10s if no controller present/ready

// v0.2 11/29/2019 3:09:20 PM
// Code optimizations

// v0.1 11/29/2019 11:44:31 AM
// First release

#include <debug.h>
#include <unistd.h>
#include <libcdvd.h>
#include <libpad.h>
#include <time.h>
#include <loadfile.h>

#include "eject.h"

extern u64 WaitTime;
extern u64 CurrTime;

u64 Timer(void);

u64 WaitTime;
u64 CurrTime;
u64 init_delay_start;
u64 timeout_start;

u64 Timer(void)
{
	return (clock() / (CLOCKS_PER_SEC / 1000));
}

int DriveState()
{
  int CdStatus;
  sleep(1);
  CdStatus = sceCdStatus();
  if (CdStatus == 0) {
  	scr_printf("* sceCdvdDriveState: (00) SCECdStatStop \n");
  } else if (CdStatus == 1) {
  		scr_printf("* sceCdvdDriveState: (01) SCECdStatShellOpen \n");
  } else if (CdStatus == 10) {
  		scr_printf("* sceCdvdDriveState: (10) SCECdStatSpin \n");
  } else {
  		scr_printf("* sceCdvdDriveState: (%d) Unknown \n",CdStatus);
  }
  return 0;
}

int main()
{
	int TrayCheck;
	init_scr();
	scr_clear();
	SifLoadModule("rom0:SIO2MAN", 0, NULL);
	SifLoadModule("rom0:PADMAN", 0, NULL);
	setupPad();
	WaitTime = Timer();
	sleep(1);
	int state = padGetState(0,0);
	scr_printf("PS2Eject v0.3 by VTSTech (12.06.2019) \n");
	scr_printf("===================www.vts-tech.org== \n \n");
	
	if (sceCdInit(SCECdINoD) == 1) {
		scr_printf("* libcdvd initalized...\n\n");
		}
	DriveState();
	if (sceCdTrayReq(3,&TrayCheck) == 1) {
		scr_printf("* sceCdTrayReq(3,SCECdTrayCheck): %d \n",TrayCheck);
		} else {
			scr_printf("! sceCdTrayReq() failed");
		}
	DriveState();
	if (sceCdTrayReq(0,&TrayCheck) == 1) {
		scr_printf("* sceCdTrayReq(0,SCECdTrayCheck): %d \n",TrayCheck);
		} else {
			scr_printf("! sceCdTrayReq() failed");
		}
	DriveState();
	//scr_printf("padGetState() %d", state);
	if (state == 6) {
		scr_printf(" \n* All operations complete. Press any button to exit. \n");
		while(1){
			state = readpad();
			if (new_pad != 0) {
				//scr_printf("Debug: %d \n",new_pad);
				return 0;
			}
		}
	} else {
		scr_printf(" \n* All operations complete. Exit in 10s...");
		sleep(10);
	}
	return 0;
}
