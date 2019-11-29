// A simple homebrew to eject the disc tray of a PS2
// PS2Eject v0.1 Written by VTSTech (veritas@vts-tech.org)

// v0.1 11/29/2019 11:44:31 AM
// First release

#include <debug.h>
#include <unistd.h>
#include <libcdvd.h>

int main()
{
  int num;
  char str;
  init_scr();
  scr_clear();
  sleep(1);
  scr_printf("PS2Eject v0.1 by VTSTech\n");
  scr_printf("========================\n\n");
  if (sceCdInit(SCECdINoD) == 1) { scr_printf("* libcdvd initalized...\n"); }
  sleep(1);
  num = sceCdStatus();
  if (num == 0) {
  	scr_printf("* SCECdvdDriveState: (0) SCECdStatStop\n");
  } else if (num >=1) {
  	scr_printf("* SCECdvdDriveState: (%d) Unknown\n",num);
  }
  scr_printf("* sceCdTrayReq(3,SCECdTrayCheck): %d\n",sceCdTrayReq(3,num));
  scr_printf("* SCECdTrayCheck: (%d) Unknown\n",num);
  sleep(1);
  num = sceCdStatus();
  if (num == 0) {
  	scr_printf("* SCECdvdDriveState: (0) SCECdStatStop\n");
  } else if (num >=1) {
  	scr_printf("* SCECdvdDriveState: (%d) Unknown\n",num);
  }
  scr_printf("* sceCdTrayReq(0,SCECdTrayCheck): %d\n",sceCdTrayReq(0,num));
  scr_printf("* SCECdTrayCheck: (%d) Unknown\n",num);
  num = sceCdStatus();
  if (num == 0) {
  	scr_printf("* SCECdvdDriveState: (0) SCECdStatStop\n");
  } else if (num >=1) {
  	scr_printf("* SCECdvdDriveState: (%d) Unknown\n",num);
  }
  sleep(30);
  return 0;
}
