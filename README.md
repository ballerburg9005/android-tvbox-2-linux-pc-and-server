**Transform a $30 Android TVbox into a home PC, media center and server for all your data.**

This project is incomplete and quite inactive. Please be aware that some issues, like wifi or sound not working, might have resolved now with time after 2 years.

Ultimately I wanted to make an image for a certain cheap box (most are Amlogic), where everything was working flawlessly. I also started documenting all the important steps how other people can make an image themselves.  There is no image yet, but you can check 

[The Wiki](https://github.com/ballerburg9005/android-tvbox-2-linux-pc-and-server/wiki) 

for instructions.

## personal experience & what to do

Overall, while it is quite possible to get to a workable result (esp. for a server), with some random Amlogic box chances are you will experience pitfalls along the way and end up with some issues remaining (e.g. no HDMI audio). Also the performance of Cortex A55 chips is not good enough, to e.g. play Youtube in 1080p directly in the browser, and A72 isn't *that* much better either. When I started this project in 2021, $30 TV boxes were getting faster and faster, but this is no longer true. So the dream of a newer $30 box that does it all might not become true any time soon.

LibreELEC has no browser, so you can't watch 123-movies and such. On the other hand the alternative is to run Armbian and Xorg, which requires much more processing power and can produce a lot of other issues.

General recommendations:

* for a mixed server and media box, use an SSD via USB (beware you need SATA adapter with external power supply, or else it will crash often!)
* Use [amlogic-s9xxx-armbian](https://github.com/ophub/amlogic-s9xxx-armbian) for a pure server
* Use LibreELEC for a media box, and docker plugin if server applications are required
