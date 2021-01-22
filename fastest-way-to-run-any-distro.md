Using Libreelec scaffolding and kernel
======================================

In this tutorial, we will simply use an Libreelec image and switch out the root file system and its location, thanks to a hook in the initramfs of the Libreelec kernel that calls "post-sysroot.sh" on the first partition.

Doing this doesn't just avoid tons of bugs, but it also saves you a lot of time and effort. 

Beware that you need at least kernel 5.2 to use [video acceleration for Mali](https://www.phoronix.com/scan.php?page=news_item&px=Panfrost-DRM-For-Linux-5.2).

I recommend using https://test.libreelec.tv/ which has the latest kernels.


Testing Libreelec
-----------------

Installing Libreelec only requires two simple actions: 1. burning the image to USB stick, 2. change uEnv.ini on the first partition (LIBREELEC) to pick the correct DTB file for your box. Stick to their howtos to create and boot the stick, see if everything works in Libreelec (sound, wifi, DVB tuner, etc). This will also resize the second partition (STORAGE) automatically, which we will use as the root partition instead. 

If you have an Amlogic box it might not boot. Try Coreelec-ng instead first. If Coreelec works, copy the SYSTEM. SYSTEM.md5, KERNEL, KERNEL.md5 and dtb directory from the Libreelec image to your installation media. Rename the KERNEL file to kernel.img + the md5 file as well. Lastly copy the correct dtb file from the new dtb directory to "dtb.img".


Installing the distribution
---------------------------

After testing Libreelec, we simply wipe the second partition and put the root partition files from another image onto it (e.g. Ubuntu MATE aarch64 for Rasperry Pi). Any image should work without issues that is of the same architecture (make sure to not mix arm/armhf and arm64/aarch64). But there are probably update scripts that might run during installation and make false assumptions (e.g. trying to flash Rasperry Pi bootloader) that need to be disabled first. I recommend you use qemu and chroot for this as described.


Copy the files from your distribution's image:
```
mkdir /tmp/sdX2_from_ubuntu_image/
I=ubuntu-mate-20.10-desktop-arm64+raspi.img ; mount -o offset=$((512*$(fdisk -o start -l $I | tail -n 1))) $I /tmp/sdX2_from_ubuntu_image/
cp -ar /tmp/sdX2_from_ubuntu_image/* /media/STORAGE/
```

In order to get the firmware and module files from Libreelec, do something like this:

```
unsquashfs -d ~/squashfs-root /media/LIBREELEC/SYSTEM 
cd /media/STORAGE
cp ~/squashfs-root/usr/lib/kernel-overlays/base/lib/modules/5.11.0-rc3/ usr/lib/modules/ -r
rsync -lr ~/squashfs-root/usr/lib/kernel-overlays/base/lib/firmware/ usr/lib/firmware/
```

This is just so that the initramfs from Libreelec feels less confused:
```
mkdir -p usr/lib/kernel-overlays/base/lib/modules/5.11.0-rc3/
mkdir flash
mkdir storage
```

Finally you should also change /etc/fstab , so that it reflects the new uuids or labels.


On the first partition, create the file "post-sysroot.sh", with the following content:

```
#!/bin/bash

umount /sysroot
mount /dev/sda2 /sysroot # if installed on USB stick
mount /dev/mmc0blk1p2 /sysroot # if installed on SD card
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

Hint for Ubuntu MATE: I had to remove the flash-kernel package, or it would crash the installer.
