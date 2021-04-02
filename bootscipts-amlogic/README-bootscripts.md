These are the proper and working bootfiles for Amlogic that are missing from Libreelec.

I have taken them from Coreelec and modified them slightly to work with Libreelec.

If you want to modify the files yourself, you have to copy & paste the text portion into a .txt file. Then you can use uboot-tools to convert them back again, like so:

```
mkimage -A arm -O linux -T script -C none -d aml_autoscript.txt aml_autoscript
```
