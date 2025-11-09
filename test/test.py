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
        
        print(s.dwDesktopVideoCaptureStat)
        print("dwLastForegroundAppProcessID", s.dwLastForegroundAppProcessID)
        
        for i in range(256):
            app = s.arrApp[i]
            if len(app.szName) == 0:
                break
            
            print(app.szName)
        
        sleep(1)


if __name__ == "__main__":
    main()

