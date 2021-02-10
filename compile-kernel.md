Compiling the Kernel from Libreelec
===================================

The best and easiest way to compile a kernel yourself is to use the Libreelec source. For Amlogic, use the specific Github repository mentioned on http://linux-meson.com (seems to make little difference). Stick to the manual on the Libreelec website.

TODO: Find out what Libreelec does special, compared to compiling just compiling the kernel.

- initramfs might contain SOC specific initialization steps? -> haven't found anything
- has optimized and working kernel config
- toolchains for cross-compilation not in actual kernel?
- busybox etc. for initramfs are compiled as well

/TODO

TODO: What can we add here to improve the Libreelec kernel?

- maybe SSHD inside initramfs for people who have not soldered UART cables to their box
- dumping logs and debug tests onto /flash/kernel_debug.txt by default (can be done from post-init hook)

/TODO


```
git clone https://github.com/chewitt/LibreELEC.tv/
cd LibreELEC.tv
MAKEFLAGS="-j8" ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux
MAKEFLAGS="-j8" ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux-firmware
```

Copy the files. I am assuming that your installation matches the one your get from following the tutorial "Fastest way to run any distro". LIBREELEC is the name of the first and STORAGE the name of the second partition.
```
cp /home/l0rd/LibreELEC.tv/build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/linux-7c53f6b671f4aba70ff15e1b05148b10d58c2837/.image/uImage.lzo /media/LIBREELEC/KERNEL
cp build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/linux-7c53f6b671f4aba70ff15e1b05148b10d58c2837/usr/lib/kernel-overlays/base/lib/modules/5.11.0-rc3 /media/STORAGE/usr/lib/modules/ -r
rsync -lr build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/kernel-firmware-20201218/usr/lib/kernel-overlays/base/lib/firmware/ /media/STORAGE/lib/firmware/
rsync -lr build.LibreELEC-AMLGX.aarch64-9.80-devel/install_pkg/dvb-firmware-1.4.0/usr/lib/kernel-overlays/base/lib/firmware/ /media/STORAGE/lib/firmware/
```
If you want to do this for Libreelec, you would have to repack the SYSTEM file from the first partition.


== force recompile ==
The Libreelec build system doesn't work for source code changes. Edit scripts/build to excempt the linux package on line 47:

``` 
   if [ "${PKG_DEEPHASH}" = "${STAMP_PKG_DEEPHASH}" -a "${BUILD_WITH_DEBUG}" = "${STAMP_BUILD_WITH_DEBUG}" -a "${PKG_NAME}" != "linux" ]; then
     # stamp matched: already built, do nothing
     pkg_lock_status "UNLOCK" "${PKG_NAME}:${TARGET}" "build" "already built"
     exit 0
   fi
```


