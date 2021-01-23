Copy the plain text portion of the file into a new file aml_autoscript.txt . Then run this command from uboot-tools .
```
mkimage -A arm -O linux -T script -C none -d aml_autoscript.txt aml_autoscript
```
I had to use this on cfgload, to change ttyS0 to ttyAML0. Then the UART serial console was working properly.
