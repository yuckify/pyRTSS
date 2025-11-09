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
        print(s.arrOSD)
        
        sleep(1)


if __name__ == "__main__":
    main()

