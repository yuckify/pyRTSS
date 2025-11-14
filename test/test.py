import sys
import os
from time import sleep
import psutil


#sys.path.append(os.getcwd() + "\\build\\Release")
import pyRTSS


def main():
    r = pyRTSS.RTSS()
    print("Version", r.version())
    
    while (True):
        s = r.snapshot()
        
        if s.dwLastForegroundAppProcessID == 0:
            continue
        
        app = s.arrApp[s.dwLastForegroundApp]
        tm = app.dwTime1 - app.dwTime0
        if not tm:
            continue
        fps = 1000.0 * app.dwFrames / tm
        print(app.szName, fps, end="\r")
        
        sleep(1)


if __name__ == "__main__":
    main()

