Sometimes the DTB file that comes with Libreelec doesn't work quite right. A certain way to get the correct DTB file is directly from your box.

Copy from eMMC
==============
```
$ binwalk /dev/mmcblk0 

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
41945088      0x2800800       device tree image (dtb)
41965787      0x28058DB       eCos RTOS string reference: "ecos"
41965838      0x280590E       eCos RTOS string reference: "ecos_memory"
41988096      0x280B000       device tree image (dtb)
42008795      0x28100DB       eCos RTOS string reference: "ecos"
...

$ A=41945088; B=41988096; dd if=/dev/mmcblk0 of=dtb.img bs=512 skip=$(($A/512)) count=$(($(($B-$A))/512))
$ dtc -O dts dtb.img -o dtbs.txt # verifies that it worked
```

It might be that the partition is compressed:
```
$ binwalk /dev/mmcblk0 

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
707189        0xACA75         Android bootimg, kernel size: 1280131328 bytes, kernel addr: 0x55434553, ramdisk size: 1094713377 bytes, ramdisk addr: 0x7E004C4D, product name: " : fail to load internal RSA key!"
711832        0xADC98         SHA256 hash constants, little endian
1181844       0x120894        LZO compressed data
1182794       0x120C4A        SHA256 hash constants, little endian
41943040      0x2800000       gzip compressed data, from Unix, last modified: 1970-01-01 00:00:00 (null date)
42205184      0x2840000       gzip compressed data, from Unix, last modified: 1970-01-01 00:00:00 (null date)
113246208     0x6C00000       Linux EXT filesystem, blocks count: 286720, image size: 293601280, rev 1.0, ext4 filesystem data, UUID=4a570d5b-283c-458d-96d9-e3a714091409
...

$ A=41943040; B=42205184; dd if=/dev/mmcblk0 of=dtb.img.gz bs=512 skip=$(($A/512)) count=$(($(($B-$A))/512))
$ gzip -d dtb.img
```

Now process the file as described in the first step.

Copy from Android
=================
This might be easier, but your system needs to be rooted for it.

```
$ su
$ dd if=/dev/dtb of=/storage/1234-1234/dtb.raw.gz #put to usb stick
```

What I got from this was the entire dtb partition, gzip compressed, as described in the second step of "Copy from eMMC".

Pitfalls
========

It still might not work. TODO: How?? 
