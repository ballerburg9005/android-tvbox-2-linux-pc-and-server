Compiling the Kernel from Libreelec
===================================

Stick to the manual on the Libreelec website. 

This tutorial is only useful if you are developing or debugging on the kernel itself.

```
git clone https://github.com/chewitt/LibreELEC.tv/
cd LibreELEC.tv
MAKEFLAGS="-j8" ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux
MAKEFLAGS="-j8" ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux-firmware
```

copy the files
===============

/media/LIBREELEC is the first and /media/STORAGE the second partition of your ARM installation.

```
cp ./LibreELEC.tv/build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/linux-.../.image/uImage.lzo /media/LIBREELEC/KERNEL
cp build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/linux-.../usr/lib/kernel-overlays/base/lib/modules/5.11.0-rc3 /media/STORAGE/usr/lib/modules/ -r
rsync -lr build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/kernel-firmware-20201218/usr/lib/kernel-overlays/base/lib/firmware/ /media/STORAGE/lib/firmware/
rsync -lr build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/dvb-firmware-1.4.0/usr/lib/kernel-overlays/base/lib/firmware/ /media/STORAGE/lib/firmware/
```

If you want to put a new Kernel into Libreelec, you would have to repack the SYSTEM file from the first partition with squashfstools and the new module and firmware files.


force to always recompile
=========================
The Libreelec build system doesn't work for source code changes. Edit scripts/build to excempt the linux package on line 47:

``` 
   if [ "${PKG_DEEPHASH}" = "${STAMP_PKG_DEEPHASH}" -a "${BUILD_WITH_DEBUG}" = "${STAMP_BUILD_WITH_DEBUG}" -a "${PKG_NAME}" != "linux" ]; then
     # stamp matched: already built, do nothing
     pkg_lock_status "UNLOCK" "${PKG_NAME}:${TARGET}" "build" "already built"
     exit 0
   fi
```



TODO: Find out what Libreelec does special, compared to compiling just compiling the kernel.

- initramfs might contain SOC specific initialization steps? -> haven't found anything
- has optimized and working kernel config
- toolchains for cross-compilation not in actual kernel?
- busybox etc. for initramfs are compiled as well

/TODO

