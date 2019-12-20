// A simple homebrew to eject the disc tray of a PS2
// PS2Eject v0.4 Written by VTSTech (veritas@vts-tech.org)

// v0.5 12/20/2019 1:44:27 PM
// Added 'Press SEL for DriveState()'
// Added SCECdStatRead and SCECdStatSeek
// detection to DriveState()

// v0.4 12/20/2019 1:00:17 PM
// Can now select multiple commands
// Sends sceCdTrayReq(0) and exits in 10s if no controller present/ready
// Makefile improvements

// v0.3 12/6/2019 5:33:45 PM
// Now waits for button press to exit
// Otherwise exits in 10s if no controller present/ready

// v0.2 11/29/2019 3:09:20 PM
// Code optimizations

// v0.1 11/29/2019 11:44:31 AM
// First release

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

//thx sp193
void ResetIOP()
{
	SifInitRpc(0);
	while(!SifIopReset("", 0)){};
	while(!SifIopSync()){};
	SifInitRpc(0);
}

void InitPS2()
{
	init_scr();
	ResetIOP();
	SifInitIopHeap();
	SifLoadFileInit();
	fioInit();
	//wipeUserMem();
	sbv_patch_disable_prefix_check();
	SifLoadModule("rom0:SIO2MAN", 0, NULL);
	SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
	SifLoadModule("rom0:PADMAN", 0, NULL);
	sceCdInit(SCECdINoD);
	//cdInitAdd();
	sleep(1);
}
void DriveState()
{
  int CdStatus;
  sleep(1);
  CdStatus = sceCdStatus();
  if (CdStatus == 0) {
  	scr_printf("* sceCdvdDriveState: (00) SCECdStatStop \n");
  } else if (CdStatus == 1) {
  		scr_printf("* sceCdvdDriveState: (01) SCECdStatShellOpen \n");
  } else if (CdStatus == 6) {
  		scr_printf("* sceCdvdDriveState: (06) SCECdStatRead \n");
  } else if (CdStatus == 10) {
  		scr_printf("* sceCdvdDriveState: (10) SCECdStatSpin \n");
  } else if (CdStatus == 12) {
  		scr_printf("* sceCdvdDriveState: (12) SCECdStatSeek \n");
  } else {
  		scr_printf("* sceCdvdDriveState: (%d) Unknown \n",CdStatus);
  }
}
void menu(){
	scr_printf(" \n* Press  X for OPEN/EJECT ... \n");
	scr_printf(" \n* Press  O for CLOSE/INSERT ... \n");
	scr_printf(" \n* Press SEL for DriveState() \n");
	scr_printf(" \n* Press START to exit \n \n");
}

void banner(){
	scr_printf("PS2Eject v0.5 by VTSTech (12.20.2019) \n");
	scr_printf("===================www.vts-tech.org== \n \n");
}
int main()
{
	int TrayCheck;
	int YCheck;
	InitPS2();
	setupPad();
	WaitTime = Timer();
	sleep(1);
	int state = padGetState(0,0);
	banner();
	if (sceCdInit(SCECdINoD) == 1) {
		scr_printf("* libcdvd initalized...\n\n");
		}
	DriveState();
	//scr_printf("padGetState() %d", state);
	if (state == 6) {
		menu();
		while(1){
			state = readpad();
			//SEL = 1
			//L3  = 2
			//R3  = 4
			//STR = 8
			//UP  = 16
			//RGT = 32
			//DWN = 64
			//LFT = 128
			//L2  = 256
			//R2  = 512
			//L1  = 1024
			//R1  = 2048
			// /\ = 4096
			// O  = 8192
			// X  = 16384
			//[ ] = 32768	
			YCheck = scr_getY();
			if (YCheck >=25) {
				scr_clear();
				banner();
				menu();
			}
			if (new_pad == 16384) {
				if (sceCdTrayReq(0,&TrayCheck) == 1) {
					scr_printf("* X  sceCdTrayReq(0,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed \n");
				}
				DriveState();
			} else if (new_pad == 8192) {
				if (sceCdTrayReq(1,&TrayCheck) == 1) {
					scr_printf("* O  sceCdTrayReq(1,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed \n");
				}
				DriveState();
			} else if (new_pad == 8) {
					return 0;
			} else if (new_pad == 1) {
					DriveState();
			}
		}
	} else {
		if (sceCdTrayReq(0,&TrayCheck) == 1) {
			scr_printf("* sceCdTrayReq(0,SCECdTrayCheck): %d \n",TrayCheck);
			} else {
				scr_printf("! sceCdTrayReq() failed");
			}
		DriveState();
		scr_printf(" \n* All operations complete. Exit in 10s...");
		sleep(10);
		return 0;
	}
}
