speedup tricks
==============

The following is a list of tricks that either have dramatic effects, or are less obvious and easy to forget about.

faster cache behavior on USB media ([explanation](https://lonesysadmin.net/2013/12/22/better-linux-disk-caching-performance-vm-dirty_ratio/))
------------------------------------
Reload with: sysctl -p /etc/sysctl.conf
```
vm.swappiness = 0
vm.dirty_background_ratio = 20
vm.dirty_expire_centisecs = 0
vm.dirty_ratio = 80
vm.dirty_writeback_centisecs = 3000 
```

check cpufreq settings
----------------------
