// A simple homebrew to eject the disc tray of a PS2
// PS2Eject v0.4 Written by VTSTech (veritas@vts-tech.org)

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
	InitPS2();
	setupPad();
	WaitTime = Timer();
	sleep(1);
	int state = padGetState(0,0);
	scr_printf("PS2Eject v0.4 by VTSTech (12.20.2019) \n");
	scr_printf("===================www.vts-tech.org== \n \n");
	
	if (sceCdInit(SCECdINoD) == 1) {
		scr_printf("* libcdvd initalized...\n\n");
		}
	DriveState();
	//scr_printf("padGetState() %d", state);
	if (state == 6) {
		scr_printf(" \n* Press  X for sceCdTrayReq(0) ... \n");
		scr_printf(" \n* Press  O for sceCdTrayReq(1) ... \n");
		scr_printf(" \n* Press [] for sceCdTrayReq(2) ... \n");
		scr_printf(" \n* Press /\\ for sceCdTrayReq(3) ... \n");
		scr_printf(" \n* Press START to exit \n \n");
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
			if (new_pad == 16384) {
				if (sceCdTrayReq(0,&TrayCheck) == 1) {
					scr_printf("* X  sceCdTrayReq(0,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed");
					}
					DriveState();
					} else if (new_pad == 8192) {
						if (sceCdTrayReq(1,&TrayCheck) == 1) {
							scr_printf("* O  sceCdTrayReq(1,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed");
					}
					DriveState();
					} else if (new_pad == 32768) {
						if (sceCdTrayReq(2,&TrayCheck) == 1) {
							scr_printf("* [] sceCdTrayReq(2,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed");
					}
					DriveState();
					} else if (new_pad == 4096) {
						if (sceCdTrayReq(3,&TrayCheck) == 1) {
							scr_printf("* /\\ sceCdTrayReq(3,SCECdTrayCheck): %d \n",TrayCheck);
					} else {
						scr_printf("! sceCdTrayReq() failed");
					}
					DriveState();
					} else if (new_pad == 8) {
						return 0;
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
