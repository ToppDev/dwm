# dwm - dynamic window manager (suckless)

This is my fork of [dwm, the dynamic window manager](https://dwm.suckless.org/) which is an extremely fast, small, and dynamic window manager for X.


# Requirements

In order to build dwm you need
- the `Xlib` header files


# Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm

```
sudo make clean install
```


# Patches applied

- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [bottomstack](https://dwm.suckless.org/patches/bottomstack/)

