# dwm

Personal build of the dwm tiling window manager based on Luke Smith's and others' builds.

Also contains an autostart script and other scripts for a custom dwm-bar build.

I'm running all of this on Debian 10.

## Requirements/dependencies

* libxcb-res0-dev (sudo apt install it). Without this librray you will get a xcb/res.h not found error, because some of the applied dwm patches.

### Other tools used by the setup

* compton (optional)
* alacritty terminal
* dmenu
* rofi
* vifm
* htop
* firefox
* maim

## Installation
* (it may be good to install dwm via package management first, to register it with you display manager/login tool)
* clone
* put files where you want
* put autostart.sh into ~/.dwm directory
* change path in autostart.sh to dwm_bar.sh location
* chmod +x all .sh files
* cd dwm/dwm && make && sudo make install

## Credits
Thanks goes to Luke Smith and Joe Standring and others from whom all this was copied and is based on.

