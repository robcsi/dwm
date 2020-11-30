#!/bin/sh

#/home/robcsi/git/dwm/dwm-bar/dwm_bar.sh &
#killall -q dwm_status.sh ||
#/home/robcsi/git/dwm/dwm-status/dwm_status.py &

pkill dwm-status || ~/.local/bin/dwm-status ~/.dwm-status.json &
compton &
nm-applet &
artha &
dunst &
xfce4-power-manager &
pa-applet &
blueman-applet &
