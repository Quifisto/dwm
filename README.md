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
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

You then need to rerun dwm by restarting (alt+shift+r) or quitting (alt+ctrl+shitft+q)
for the changes to take effect.
