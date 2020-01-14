# dwm - dynamic window manager (quifisto's version)
dwm is an extremely fast, small, and dynamic window manager for X.
I added some personal modifications and some patches from suckless' [website](https://dwm.suckless.org).
Some of those can be found in the patches folder.


## Installation
In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm


## Configuration
The simple configuration (shortcuts, fonts, colors) of dwm is done by creating a custom config.h and (re)compiling the source code.
If you want to make more drastic changes you'll have to edit the actual functions in the code.
But don't be frightened, if you know a bit of c it's quite easy to read and make changes.
You should start by looking at dwm.c, which contains the majority of the code.
All drawing functions are writen in drw.c, so that might also be worth a look.

For the changes to take effect you need to rerun dwm by restarting (alt+shift+r) or quitting (alt+ctrl+shitft+q).
