Copy the plain text portion of the file into a new file aml_autoscript.txt . Then run this command from uboot-tools .
```
mkimage -A arm -O linux -T script -C none -d aml_autoscript.txt aml_autoscript
```
