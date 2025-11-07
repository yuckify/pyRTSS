import sys
import os
from time import sleep
import psutil


sys.path.append(os.getcwd() + "\\build\\Release")
import pyRTSS


def main():
    r = pyRTSS.RTSS()
    print("Version", r.version())
    
    while (True):
        s = r.snapshot()
        
        if s.foreground_app:
            if s.foreground_app.pid:
                print(s.foreground_app.name, s.foreground_app.frame_rate())
        sleep(1)


if __name__ == "__main__":
    main()

