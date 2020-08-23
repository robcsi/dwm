#!/bin/sh

killall -q dwm_bar.sh
/home/robcsi/git/dwm/dwm-bar/dwm_bar.sh &
compton &
nm-applet &
artha &
orage &
dunst &
mate-power-manager &
mate-volume-control-applet &
killall -q nitrogen
nitrogen --random --set-zoom-fill /home/robcsi/wallpapers/
