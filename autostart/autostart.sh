#!/bin/sh

#/home/robcsi/git/dwm/dwm-bar/dwm_bar.sh &
#killall -q dwm_status.sh ||
/home/robcsi/git/dwm/dwm-status/dwm_status.py &
compton &
nm-applet &
artha &
orage &
dunst &
mate-power-manager &
mate-volume-control-applet &
killall -q nitrogen || nitrogen --random --set-zoom-fill /home/robcsi/wallpapers/ &
