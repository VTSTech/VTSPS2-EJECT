// A simple homebrew to eject the disc tray of a PS2
// PS2Eject v0.1 Written by VTSTech (veritas@vts-tech.org)

// v0.2 11/29/2019 3:09:20 PM
// Code optimizations

// v0.1 11/29/2019 11:44:31 AM
// First release

#include <debug.h>
#include <unistd.h>
#include <libcdvd.h>

int DriveState()
{
  int CdStatus;
  sleep(1);
  CdStatus = sceCdStatus();
  if (CdStatus == 0) {
  	scr_printf("* sceCdvdDriveState: (00) SCECdStatStop\n");
  } else if (CdStatus == 1) {
  	scr_printf("* sceCdvdDriveState: (01) SCECdStatShellOpen\n");
  } else if (CdStatus == 10) {
  	scr_printf("* sceCdvdDriveState: (10) SCECdStatSpin\n");
  } else {
  	scr_printf("* sceCdvdDriveState: (%d) Unknown\n",CdStatus);
  }
  return 0;
}

int main()
{
  int TrayCheck;
  init_scr();
  scr_clear();
  sleep(1);
  scr_printf("PS2Eject v0.2 by VTSTech (11-29-2019)\n=====================================\n\n");
  if (sceCdInit(SCECdINoD) == 1) { scr_printf("* libcdvd initalized...\n\n"); }
	DriveState();
  if (sceCdTrayReq(3,&TrayCheck) == 1) { scr_printf("* sceCdTrayReq(3,SCECdTrayCheck): %d\n",TrayCheck); } else { scr_printf("! sceCdTrayReq() failed"); }
	DriveState();
	if (sceCdTrayReq(0,&TrayCheck) == 1) { scr_printf("* sceCdTrayReq(0,SCECdTrayCheck): %d\n",TrayCheck); } else { scr_printf("! sceCdTrayReq() failed"); }
	DriveState();
  scr_printf("\n* All operations complete. Exit in 30s...");
  sleep(30);
  return 0;
}
