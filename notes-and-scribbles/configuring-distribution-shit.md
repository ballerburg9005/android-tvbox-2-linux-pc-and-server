speedup tricks
==============

The following is a list of tricks that either have dramatic effects, or are less obvious and easy to forget about.

=> **surprise: nothing whatsoever you can do has dramatic effects. Basically just old scribbles in this doc.**

more lax cache behavior on USB media ([explanation](https://lonesysadmin.net/2013/12/22/better-linux-disk-caching-performance-vm-dirty_ratio/))
------------------------------------
Reload with: sysctl -p /etc/sysctl.conf
```
vm.swappiness = 0
vm.dirty_background_ratio = 20
vm.dirty_expire_centisecs = 0
vm.dirty_ratio = 80
vm.dirty_writeback_centisecs = 3000 
```
===> did not help!!!

I picked this:
```
vm.dirty_writeback_centisecs = 100
vm.dirty_expire_centisecs = 100
```

minor ext4 optimizations
------------------------

https://developer.ridgerun.com/wiki/index.php/High_performance_SD_card_tuning_using_the_EXT4_file_system

/etc/fstab :
```
LABEL=STORAGE      /               ext4    defaults,noatime,data=ordered,async   0   0
```

check cpufreq settings
----------------------

* govenor = performance?
* freq stuck low?

Firefox -> change useragent to make certain sites like Youtube more lightweight
------------------------------------------------------------------------------

The speedup on youtube is huge. But once the video plays, it plays all the same.

* install extension "User agent switcher and manager"
* Click the toolbar icon, go to "options" (it's above the blue button "Test UA")
* pick "Custom Mode" and insert the following:

```
{
  "youtube.com": "Mozilla 5.0 (Android 7.0: Mobile; rv:68.0) Gecko 68.0 Firefox/68.0",
  "dailymotion.com": "Mozilla 5.0 (Android 7.0: Mobile; rv:68.0) Gecko 68.0 Firefox/68.0",
}
```

Lower mouse polling rate
------------------------

When using Youtube or Facebook, wiggling the mouse around can cause as much as an additional 80% CPU load. Some mice have a 10x worse performance impact than others. On mini-keyboard trackpads you can reduce the polling rate very low, and hence save some CPU, because they are either way clunky to use it makes no real difference. Usbhid.mousepoll=10 e.g. add the following to config.ini (for Coreelec)
usbopts='usbhid.mousepoll=10'

* This is a nice idea, but unfortunately there is a known bug in the kernel and no one is willing to fix it since 10 years. So it just doesn't work.
