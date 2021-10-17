# dwm - dynamic window manager (suckless)

This is my fork of [dwm, the dynamic window manager](https://dwm.suckless.org/) which is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need
- the `Xlib` header files
- swallow patch
  - libxcb
  - Xlib-libxcb
  - xcb-res


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm

```
sudo make clean install
```


## Patches applied

- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [bottomstack](https://dwm.suckless.org/patches/bottomstack/)
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
- [deck](https://dwm.suckless.org/patches/deck/)
- [fibonacci](https://dwm.suckless.org/patches/fibonacci/)
- [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [resizecorners](https://dwm.suckless.org/patches/resizecorners/)
- [scratchpads](https://dwm.suckless.org/patches/scratchpads/)
- [statusallmons](https://dwm.suckless.org/patches/statusallmons/)
- [sticky](https://dwm.suckless.org/patches/sticky/)
- [swallow](https://dwm.suckless.org/patches/swallow/)
- [systray](https://dwm.suckless.org/patches/systray/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [Xresources](https://dwm.suckless.org/patches/xresources/)
- [viewontag](https://dwm.suckless.org/patches/viewontag/)
- [restartsig](https://dwm.suckless.org/patches/restartsig/)
- [shiftview](https://lists.suckless.org/dev/1104/7590.html)
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)


## Acknowledgements

Some ideas and code was taken from other projects. Credits for those go to

* [Luke Smith](https://github.com/LukeSmithxyz/dwm)