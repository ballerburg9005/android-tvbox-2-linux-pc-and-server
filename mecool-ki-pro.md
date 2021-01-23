
* Use 5.11 Kernel 
* comes with video decoder HW acceleration in browser and media player
* works out of the box via mesa and framebuffer driver
* If Xorg doesn't start, you may need to add this to /etc/X11/xorg.conf
```
Section "ServerFlags"
        Option "AutoAddGPU" "off"
EndSection
```
* VPU doesn't work quite right, weird blocky tearing
* **TODO** how to double-buffer to avoid tearing?
