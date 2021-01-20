
...

==Using Coreelec scaffolding and kernel==

Getting Libreelec to boot is a very easy two-step process. Stick to their howtos to create and boot the stick, see if it works. This will also resize the system partition automatically.

Now we can simply wipe the second partition (STORAGE), and put the rootfs files from another image onto it (e.g. Ubuntu arm64 for Rasperry Pi). In theory any image should work that is of the same architecture.

In order to get the firmware and module files from Libreelec, do something like this:

```
cd ~
unsquashfs /media/LIBREELEC/SYSTEM
cd /media/STORAGE
cp ~/squashfs-root/usr/lib/kernel-overlays/base/lib/modules/4.9.113/ usr/lib/modules/ -r
mv usr/lib/firmware usr/lib/firmware_old
cp ~/squashfs-root/usr/lib/kernel-overlays/base/lib/firmware usr/lib/ -r
```

On the first partition, create the file "post-sysroot.sh" with the following content:

```
#!/bin/bash

umount /sysroot
mount /dev/sda2 /sysroot # if installed on USB stick
mount /dev/mmc??TODO?? /sysroot # if installed on SD card
```
