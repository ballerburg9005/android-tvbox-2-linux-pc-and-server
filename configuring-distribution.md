speedup tricks
==============

The following is a list of tricks that either have dramatic effects, or are less obvious and easy to forget about.

=> surprise: nothing has dramatic effects. Just scribbles in this doc.

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

The speedup on youtube is huge. Once the video plays, it plays all the same though.

* install extension "User agent switcher and manager"
* Click the toolbar icon, go to "options" (it's above the blue button "Test UA")
* pick "Custom Mode" and insert the following:

```
{
  "youtube.com": "Mozilla 5.0 (Android 7.0: Mobile; rv:68.0) Gecko 68.0 Firefox/68.0",
  "dailymotion.com": "Mozilla 5.0 (Android 7.0: Mobile; rv:68.0) Gecko 68.0 Firefox/68.0",
}
```

Greasemonkey scripts for Youtube
--------------------------------

Disable mouse movement:
```
window.addEventListener("mousemove", function (event) { event.stopPropagation();}, true);
```
