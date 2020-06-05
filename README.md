<img src="https://i.gyazo.com/4f724f57e9d7c46df54a8f1472945995.png">

# PS2Eject
 A simple homebrew to eject the disc tray of a PS2
<pre>
 v0.6 12/20/2019 11:59:06 PM
 Swapped O for /\
 Removed 1s delay on DriveState()

 v0.5 12/20/2019 1:44:27 PM
 Added 'Press SEL for DriveState()'
 Added SCECdStatRead and SCECdStatSeek detection to DriveState()
 Removed sceCdTrayReq(2) & sceCdTrayReq(3)
 More specific menu, Eject/Insert specified.
 Now clears the screen instead of overwriting.

 v0.4 12/20/2019 1:00:17 PM
 Can now select multiple commands
 Sends sceCdTrayReq(0) and exits in 10s if no controller present/ready
 Makefile improvements
 
 v0.3 12/6/2019 5:33:45 PM
 Now waits for button press to exit
 Otherwise exits in 10s if no controller present/ready 

 v0.2 11/29/2019 3:09:20 PM
 Code optimizations

 v0.1 11/29/2019 11:44:31 AM
 First release
</pre>

PSX-Place https://www.psx-place.com/resources/ps2eject.882