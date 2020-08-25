#!/bin/python3

from subprocess import Popen,PIPE
from dwm_status_events import trigger_change_event
from shell_exe import execute
from threading import Timer, Thread

class Storage:
    def __init__(self):
        self.details = 'STO 00G/00G: 00%'
        Thread(self.set_details()).start()

    def get_details(self):
        sto_used = execute([
            ["df", "-h"],
            ["grep", "/$"],
            ["awk", "{print $3}"],
        ]).replace('\n', '')

        sto_tot = execute([
            ["df", "-h"],
            ["grep", "/$"],
            ["awk", "{print $2}"],
        ]).replace('\n', '')

        sto_per = execute([
            ["df", "-h"],
            ["grep", "/$"],
            ["awk", "{print $5}"],
        ]).replace('\n', '')

        return "STO {}/{}: {}".format(sto_used, sto_tot, sto_per)

    @trigger_change_event
    def set_details(self):
        self.details = self.get_details()
        Timer(60, self.set_details).start()

    def __str__(self):
        return self.details
