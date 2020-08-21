#!/bin/sh

# A script to get the number of available updates by apt-get

dwm_updates () {

    #simulate upgrade; probably not the best solution...
    UPDATES=$(apt-get upgrade -s |grep -P '^\d+ upgraded'|cut -d" " -f1)

    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "🔌 %s" "$UPDATES"
    else
        printf "UPD %s" "$UPDATES"
    fi
    printf "%s\n" "$SEP2"
}

dwm_updates

