#ifndef RTSS_HPP
#define RTSS_HPP

#include <memory>
#include <vector>
#include <string>

#include <windows.h>
#include <RTSSSharedMemory.h>

namespace pyRTSS {

struct RTSS_SHARED_MEMORY_OSD_ENTRY {
	RTSS_SHARED_MEMORY_OSD_ENTRY();
	RTSS_SHARED_MEMORY_OSD_ENTRY(const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &other);
	RTSS_SHARED_MEMORY_OSD_ENTRY(const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY *other);
};

struct RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY {
	RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY(const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY &other);
	RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY(const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY *other);
	
	DWORD	dwID;
	DWORD	dwParam;
	DWORD	dwData;
};


struct RTSS_SHARED_MEMORY_APP_ENTRY {
	RTSS_SHARED_MEMORY_APP_ENTRY();
	RTSS_SHARED_MEMORY_APP_ENTRY(const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &other);
	
	DWORD	dwProcessID;
	std::string	szName;
	DWORD	dwFlags;
	DWORD	dwTime0;
	DWORD	dwTime1;
	DWORD	dwFrames;
	DWORD	dwFrameTime;
	DWORD	dwStatFlags;
	DWORD	dwStatTime0;
	DWORD	dwStatTime1;
	DWORD	dwStatFrames;
	DWORD	dwStatCount;
	DWORD	dwStatFramerateMin;
	DWORD	dwStatFramerateAvg;
	DWORD	dwStatFramerateMax;
	DWORD	dwOSDX;
	DWORD	dwOSDY;
	DWORD	dwOSDPixel;
	DWORD	dwOSDColor;
	DWORD	dwOSDFrame;
	DWORD	dwScreenCaptureFlags;
	std::string	szScreenCapturePath;
	DWORD	dwOSDBgndColor;
	DWORD	dwVideoCaptureFlags;
	std::string	szVideoCapturePath;
	DWORD	dwVideoFramerate;
	DWORD	dwVideoFramesize;
	DWORD	dwVideoFormat;
	DWORD	dwVideoQuality;
	DWORD	dwVideoCaptureThreads;
	DWORD	dwScreenCaptureQuality;
	DWORD	dwScreenCaptureThreads;
	DWORD	dwAudioCaptureFlags;
	DWORD	dwVideoCaptureFlagsEx;
	DWORD	dwAudioCaptureFlags2;
	DWORD	dwStatFrameTimeMin;
	DWORD	dwStatFrameTimeAvg;
	DWORD	dwStatFrameTimeMax;
	DWORD	dwStatFrameTimeCount;
	std::vector<DWORD>	dwStatFrameTimeBuf; // 1024
	DWORD	dwStatFrameTimeBufPos;
	DWORD	dwStatFrameTimeBufFramerate;
	LARGE_INTEGER qwAudioCapturePTTEventPush;
	LARGE_INTEGER qwAudioCapturePTTEventRelease;
	LARGE_INTEGER qwAudioCapturePTTEventPush2;
	LARGE_INTEGER qwAudioCapturePTTEventRelease2;
	DWORD	dwPrerecordSizeLimit;
	DWORD	dwPrerecordTimeLimit;
	LARGE_INTEGER qwStatTotalTime;
	std::vector<DWORD>	dwStatFrameTimeLowBuf; // 1024
	DWORD	dwStatFramerate1Dot0PercentLow;
	DWORD	dwStatFramerate0Dot1PercentLow;
	DWORD	dw1Dot0PercentLowBufPos;
	DWORD	dw0Dot1PercentLowBufPos;
	DWORD dwProcessPerfCountersFlags;
	DWORD dwProcessPerfCountersCount;
	DWORD dwProcessPerfCountersSamplingPeriod;
	DWORD dwProcessPerfCountersSamplingTime;
	DWORD dwProcessPerfCountersTimestamp;
	LARGE_INTEGER qwLatencyMarkerPresentTimestamp;
	DWORD dwResolutionX;
	DWORD dwResolutionY;
	ULONGLONG	qwInputSampleTime;
	ULONGLONG	qwSimStartTime;
	ULONGLONG	qwSimEndTime;
	ULONGLONG	qwRenderSubmitStartTime;
	ULONGLONG	qwRenderSubmitEndTime;
	ULONGLONG	qwPresentStartTime;
	ULONGLONG	qwPresentEndTime;
	ULONGLONG	qwDriverStartTime;
	ULONGLONG	qwDriverEndTime;
	ULONGLONG	qwOsRenderQueueStartTime;
	ULONGLONG	qwOsRenderQueueEndTime;
	ULONGLONG	qwGpuRenderStartTime;
	ULONGLONG	qwGpuRenderEndTime;
	DWORD		dwGpuActiveRenderTime;
	DWORD		dwGpuFrameTime;
	std::vector<RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY> arrPerfCounters; // 256
	
	float framerate();
};
typedef std::shared_ptr<RTSS_SHARED_MEMORY_APP_ENTRY> RTSS_SHARED_MEMORY_APP_ENTRY_P;


struct RTSS_SHARED_MEMORY {
	RTSS_SHARED_MEMORY();
	RTSS_SHARED_MEMORY(::RTSS_SHARED_MEMORY &other);
	
	DWORD	dwSignature;
	DWORD	dwVersion;
	DWORD	dwAppEntrySize;
	DWORD	dwAppArrOffset;
	DWORD	dwAppArrSize;
	DWORD	dwOSDEntrySize;
	DWORD	dwOSDArrOffset;
	DWORD	dwOSDArrSize;
	DWORD	dwOSDFrame;
	LONG dwBusy;
	DWORD dwDesktopVideoCaptureFlags;
//	DWORD dwDesktopVideoCaptureStat[5];
	std::vector<DWORD> dwDesktopVideoCaptureStat; // 5
	DWORD dwLastForegroundApp;
	DWORD dwLastForegroundAppProcessID;
	DWORD dwProcessPerfCountersEntrySize;
	DWORD dwProcessPerfCountersArrOffset;
	LARGE_INTEGER qwLatencyMarkerSetTimestamp;
	LARGE_INTEGER qwLatencyMarkerResetTimestamp;
	
	std::vector<RTSS_SHARED_MEMORY_OSD_ENTRY> arrOSD; // 8
	std::vector<RTSS_SHARED_MEMORY_APP_ENTRY> arrApp; // 256
	VIDEO_CAPTURE_PARAM autoVideoCaptureParam;		
	
	/*
	unsigned int version;
	RTSS_SHARED_MEMORY_APP_ENTRY_P foreground_app;
	std::vector<RTSS_SHARED_MEMORY_APP_ENTRY_P> app_list;
	*/
};
typedef std::shared_ptr<RTSS_SHARED_MEMORY> RTSS_SHARED_MEMORY_P;


class RTSS {
	HANDLE map_file;
	LPRTSS_SHARED_MEMORY ptr;
public:
	RTSS();
	~RTSS();
	
	DWORD version();
	RTSS_SHARED_MEMORY_P snapshot();
};

} // namespace pyRTSS

#endif // RTSS_HPP

