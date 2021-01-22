Compiling the Kernel from Libreelec
===================================

The best and easiest way to compile a kernel yourself is to use the Coreelec / Libreelec source. For Amlogic, use the specific Github repository mentioned on http://linux-meson.com . Stick to the manual on the Libreelec website.

```
git clone https://github.com/chewitt/LibreELEC.tv/
cd LibreELEC.tv
ARCH=aarch64 PROJECT=Amlogic DEVICE=AMLGX ./scripts/build linux
```

Those are the bugs that I had to fix. You may face different bugs.

```
# bug1 in Bash causes silenced command from if-statement to pipe into some file instead
./config.status: line 535: 0a1,274: command not found
./config.status: line 536: syntax error near unexpected token `newline'
./config.status: line 536: `> # This file is a shell script that caches the results of configure'

# bug2: m4 is too new and incorrectly identified as bugged

# fix with:
for i in `find . -name 'configure*' -or -name '*.m4' -or -name '*.m4f'`; do 
  #bug1
  sed 's#if diff "$cache_file" confcache >/dev/null 2>&1#if false #g' -i $i;
  #bug2
  sed 's#$ac_path_M4_found && break 3$#\$ac_path_M4_found \&\& break 3; break 3#g' -i $i;
done
```

