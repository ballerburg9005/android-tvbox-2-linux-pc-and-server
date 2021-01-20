Using Libreelec scaffolding and kernel
=====================================

In this tutorial, we will simply use an Libreelec or Coreelec image and switch out the root file system and its location via a hook in the initramfs of the Libreelec kernel. 

Getting Libreelec to boot is a very very easy two-step process. Stick to their howtos to create and boot the stick, see if it works. This will also resize the system partition automatically.

Now we can simply wipe the second partition (STORAGE), and put the rootfs files from another image onto it (e.g. Ubuntu MATE arm64 for Rasperry Pi). In theory any image should work that is of the same architecture.

In order to get the firmware and module files from Libreelec, do something like this:

```
cd ~
unsquashfs /media/LIBREELEC/SYSTEM
cd /media/STORAGE
cp ~/squashfs-root/usr/lib/kernel-overlays/base/lib/modules/4.9.113/ usr/lib/modules/ -r
mv usr/lib/firmware usr/lib/firmware_old
cp ~/squashfs-root/usr/lib/kernel-overlays/base/lib/firmware usr/lib/ -r
```

This is just so that the initramfs from Libreelec feels less confused:
```
mkdir -p usr/lib/kernel-overlays/base/lib/modules/4.9.113/
mkdir flash
mkdir storage
```

Finally you should also change /etc/fstab , so that it reflects the correct uuids or labels.


On the first partition (LIBREELEC), create the file "post-sysroot.sh", with the following content:

```
#!/bin/bash

umount /sysroot
mount /dev/sda2 /sysroot # if installed on USB stick
mount /dev/mmc??TODO?? /sysroot # if installed on SD card
```

Now you should see the graphical installer and can proceed as usual. 

Hint for Ubuntu MATE: There is a bug that crashes the installer if you have internet connected. 
