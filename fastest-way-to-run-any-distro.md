Using Libreelec scaffolding and kernel
=====================================

In this tutorial, we will simply use an Libreelec image and switch out the root file system and its location, thanks to a hook in the initramfs of the Libreelec kernel that calls "post-sysroot.sh" on the first partition.

Doing this doesn't just avoid tons of bugs, but it also saves you a lot of time and effort. Not only can you quickly switch to a newer kernel from newer Libreelec images using this method, but you can also compile newer kernel versions yourself directly from the Libreelec repo, without configuring a single thing by hand.

Beware that you need at least kernel 5.2 to use [video acceleration for Mali](https://www.phoronix.com/scan.php?page=news_item&px=Panfrost-DRM-For-Linux-5.2).

The first step is to get Libreelec to boot. This only requires two simple actions: 1. burning the image to USB stick, 2. change uEnv.ini on the first partition (LIBREELEC) to pick the correct DTB file for your box. Stick to their howtos to create and boot the stick, see if everything works in Libreelec (sound, wifi, DVB tuner, etc). This will also resize the second partition (STORAGE) automatically, which we will use as the root partition instead. 

My Amlogic box would not boot with Libreelec, until I replaced the "aml_autoscript" with the one from Coreelec. For this to work you need to rename "KERNEL" to "kernel.img" as well, not use the uEnv.ini but save the correct DTB file as "dtb.img", and copy the file "cfgload" as well as "config.ini" over from the Coreelec image.

After testing Libreelec, we simply wipe the second partition and put the root partition files from another image onto it (e.g. Ubuntu MATE aarch64 for Rasperry Pi). In theory any image should work without any issues that is of the same architecture (make sure to not mix arm/armhf and arm64/aarch64). 

```
# TODO describe how to put the root system to /media/STORAGE
```

In order to get the firmware and module files from Libreelec, do something like this:

```
cd ~
unsquashfs -d squashfs-root /media/LIBREELEC/SYSTEM 
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

Finally you should also change /etc/fstab , so that it reflects the new uuids or labels.


On the first partition (LIBREELEC), create the file "post-sysroot.sh", with the following content:

```
#!/bin/bash

umount /sysroot
mount /dev/sda2 /sysroot # if installed on USB stick
mount /dev/mmc??TODO?? /sysroot # if installed on SD card
```

**Now you can boot the image and should see the graphical installer.**

But before you do that it's smart to enable sshd first and set root password. You can do it by simply chrooting into the image on your PC:

```
# install qemu-arm-static first
cp $(which qemu-arm-static) /media/STORAGE/usr/bin
chroot /media/STORAGE qemu-arm-static /bin/bash

# this might be specific to Ubuntu/Debian
echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
apt-get install openssh-server
passwd
```

