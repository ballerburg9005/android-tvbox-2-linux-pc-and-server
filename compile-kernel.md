Compiling the Kernel from Libreelec
===================================

The best and easiest way to compile a kernel yourself is to use the Coreelec / Libreelec source. For Amlogic, use the specific Github repository mentioned on http://linux-meson.com . Stick to the manual on the Libreelec website.

TODO: Find out what Libreelec does special, compared to compiling just compiling the kernel.
- initramfs might contain SOC specific initialization steps
- has optimized and working kernel config
- toolchains for cross-compilation not in actual kernel?
- busybox etc. for initramfs are compiled as well
/TODO

TODO: What can we add here to improve the Libreelec kernel?
- maybe SSHD inside initramfs for people who have not soldered UART cables to their box
- dumping logs and debug tests onto /flash/kernel_debug.txt by default (can be done from post-init hook)
/TODO

A flawfless compilation takes an entire day on an i5-2500 (high-end 2010 CPU). With bug babysitting, it takes several days.

```
git clone https://github.com/chewitt/LibreELEC.tv/
cd LibreELEC.tv
MAKEFLAGS="-j8" ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux
```

Fix M4 is too new bug. You might get different bugs.

```
for i in `find . -name 'configure*' -or -name '*.m4'`; do sed 's#$ac_path_M4_found && break 3$#\$ac_path_M4_found \&\& break 3; break 3#g' -i $i; done
```
