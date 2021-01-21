* Check 5.11 Kernel from Libreelec branch mentioned on linux-meson.com

-> https://wiki.debian.org/PanfrostLima
```
apt install libglx-mesa0 libgl1-mesa-dri
```

-> https://linux-sunxi.org/Mali_binary_driver -> outdated?

* 4.9 Coreelec kernel comes with mali driver kernel module

vim /etc/udev/rules.d/50-mali.rules
```
KERNEL=="mali", MODE="0660", GROUP="video"
KERNEL=="ump", MODE="0660", GROUP="video"
```

cp /usr/lib/libMali.m450.so from Coreelec to /var/lib/libMali.so ???
ln -s /var/lib/libMali.so /usr/lib/libmali.so.0 ???
ln -s /var/lib/libMali.so /usr/lib/libmali.so

=> mali_drm missing

-> test Libreelec 5.11 kernel image first. Make sure it includes mali_drm
