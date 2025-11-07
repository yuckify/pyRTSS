#include "RTSS.hpp"

#include <iostream>

namespace pyRTSS {

struct impl {
	template<typename T, typename U>
	static void copy(T &dst, U &src) {
		dst = src;
	}

	template<typename T, unsigned int count>
	static void copy(std::string &dst, T (&src)[count]) {
		dst = src;
	}

	template<typename T, typename Q, unsigned int count>
	static void copy(std::vector<T> &dst, Q (&src)[count]) {
		dst = std::vector<T>(&src[0], &src[count]);
	}
};


RTSS_SHARED_MEMORY_OSD_ENTRY::RTSS_SHARED_MEMORY_OSD_ENTRY() {
	
}

RTSS_SHARED_MEMORY_OSD_ENTRY::RTSS_SHARED_MEMORY_OSD_ENTRY(
		const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &other) {
	
}

RTSS_SHARED_MEMORY_OSD_ENTRY::RTSS_SHARED_MEMORY_OSD_ENTRY(
		const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY *other) {
	
}


RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY(
		const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY &other) {
	dwID = other.dwID;
	dwParam = other.dwParam;
	dwData = other.dwData;
}

RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY(
		const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY *other) {
	dwID = other->dwID;
	dwParam = other->dwParam;
	dwData = other->dwData;
}


RTSS_SHARED_MEMORY_APP_ENTRY::RTSS_SHARED_MEMORY_APP_ENTRY() {
	
}

RTSS_SHARED_MEMORY_APP_ENTRY::RTSS_SHARED_MEMORY_APP_ENTRY(
		const ::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &other) {
#define COPY(n) impl::copy(n, other.n);
		COPY(dwProcessID)
		COPY(szName)
		COPY(dwFlags)
		COPY(dwTime0)
		COPY(dwTime1)
		COPY(dwFrames)
		COPY(dwFrameTime)
		COPY(dwStatFlags)
		COPY(dwStatTime0)
		COPY(dwStatTime1)
		COPY(dwStatFrames)
		COPY(dwStatCount)
		COPY(dwStatFramerateMin)
		COPY(dwStatFramerateAvg)
		COPY(dwStatFramerateMax)
		COPY(dwOSDX)
		COPY(dwOSDY)
		COPY(dwOSDPixel)
		COPY(dwOSDColor)
		COPY(dwOSDFrame)
		COPY(dwScreenCaptureFlags)
		COPY(szScreenCapturePath)
		COPY(dwOSDBgndColor)
		COPY(dwVideoCaptureFlags)
		COPY(szVideoCapturePath)
		COPY(dwVideoFramerate)
		COPY(dwVideoFramesize)
		COPY(dwVideoFormat)
		COPY(dwVideoQuality)
		COPY(dwVideoCaptureThreads)
		COPY(dwScreenCaptureQuality)
		COPY(dwScreenCaptureThreads)
		COPY(dwAudioCaptureFlags)
		COPY(dwVideoCaptureFlagsEx)
		COPY(dwAudioCaptureFlags2)
		COPY(dwStatFrameTimeMin)
		COPY(dwStatFrameTimeAvg)
		COPY(dwStatFrameTimeMax)
		COPY(dwStatFrameTimeCount)
		COPY(dwStatFrameTimeBuf)
		COPY(dwStatFrameTimeBufPos)
		COPY(dwStatFrameTimeBufFramerate)
		COPY(qwAudioCapturePTTEventPush)
		COPY(qwAudioCapturePTTEventRelease)
		COPY(qwAudioCapturePTTEventPush2)
		COPY(qwAudioCapturePTTEventRelease2)
		COPY(dwPrerecordSizeLimit)
		COPY(dwPrerecordTimeLimit)
		COPY(qwStatTotalTime)
		COPY(dwStatFrameTimeLowBuf)
		COPY(dwStatFramerate1Dot0PercentLow)
		COPY(dwStatFramerate0Dot1PercentLow)
		COPY(dw1Dot0PercentLowBufPos)
		COPY(dw0Dot1PercentLowBufPos)
		COPY(dwProcessPerfCountersFlags)
		COPY(dwProcessPerfCountersCount)
		COPY(dwProcessPerfCountersSamplingPeriod)
		COPY(dwProcessPerfCountersSamplingTime)
		COPY(dwProcessPerfCountersTimestamp)
		COPY(qwLatencyMarkerPresentTimestamp)
		COPY(dwResolutionX)
		COPY(dwResolutionY)
		COPY(qwInputSampleTime)
		COPY(qwSimStartTime)
		COPY(qwSimEndTime)
		COPY(qwRenderSubmitStartTime)
		COPY(qwRenderSubmitEndTime)
		COPY(qwPresentStartTime)
		COPY(qwPresentEndTime)
		COPY(qwDriverStartTime)
		COPY(qwDriverEndTime)
		COPY(qwOsRenderQueueStartTime)
		COPY(qwOsRenderQueueEndTime)
		COPY(qwGpuRenderStartTime)
		COPY(qwGpuRenderEndTime)
		COPY(dwGpuActiveRenderTime)
		COPY(dwGpuFrameTime)
		COPY(arrPerfCounters)
#undef COPY
}

float RTSS_SHARED_MEMORY_APP_ENTRY::framerate() {
	return 1000.0f * dwFrames / (dwTime1 - dwTime0);
}


RTSS::RTSS() {
	map_file = nullptr;
	ptr = nullptr;
	
	map_file = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "RTSSSharedMemoryV2");
	if (!map_file) {
		std::cout<<"ERROR: could not open file" <<std::endl;
		return;
	}
	
	ptr = (LPRTSS_SHARED_MEMORY)MapViewOfFile(map_file, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!ptr) {
		std::cout<<"ERROR: could not map view of file" <<std::endl;
		return;
	}
	
	if (ptr->dwSignature != 'RTSS') {
		std::cout<<"ERROR: bad signature" <<std::endl;
		return;
	}
}

RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY() {
	
}


RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY(::RTSS_SHARED_MEMORY &other) {
#define COPY(n) impl::copy(n, other.n)
	COPY(dwSignature);
	COPY(dwVersion);
	COPY(dwAppEntrySize);
	COPY(dwAppArrOffset);
	COPY(dwAppArrSize);
	COPY(dwOSDEntrySize);
	COPY(dwOSDArrOffset);
	COPY(dwOSDArrSize);
	COPY(dwOSDFrame);
	COPY(dwBusy);
	COPY(dwDesktopVideoCaptureFlags);
	COPY(dwDesktopVideoCaptureStat);
	COPY(dwLastForegroundApp);
	COPY(dwLastForegroundAppProcessID);
	COPY(dwProcessPerfCountersEntrySize);
	COPY(dwProcessPerfCountersArrOffset);
	COPY(qwLatencyMarkerSetTimestamp);
	COPY(qwLatencyMarkerResetTimestamp);
	COPY(arrOSD);
	COPY(arrApp);
	COPY(autoVideoCaptureParam);
	
#undef COPY	
}


RTSS::~RTSS() {
	if (ptr)
		UnmapViewOfFile((void *)ptr);
	if (map_file)
		CloseHandle(map_file);
}

DWORD RTSS::version() {
	if (!ptr) {
		std::cout<<"ERROR: rtss not opened" <<std::endl;
		return 0;
	}
	
	DWORD version = 0;
	if (ptr->dwVersion >= 0x00020000) {
		version = ptr->dwVersion;
	}
	
	return version;
}

RTSS_SHARED_MEMORY_P RTSS::snapshot() {
	RTSS_SHARED_MEMORY_P mem = std::make_shared<RTSS_SHARED_MEMORY>(*ptr);
	
	/*
	mem->version = ptr->dwVersion;
	
	for (unsigned i = 0; i < 256; i++) {
		RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &entry = ptr->arrApp[i];
		if (strlen(entry.szName) == 0)
			continue;
		
		RTSS_SHARED_MEMORY_APP_ENTRY_P e = std::make_shared<RTSS_SHARED_MEMORY_APP_ENTRY>();
#define COPY(n) impl::copy(e->n, entry.n);
		COPY(dwProcessID)
		COPY(szName)
		COPY(dwFlags)
		COPY(dwTime0)
		COPY(dwTime1)
		COPY(dwFrames)
		COPY(dwFrameTime)
		COPY(dwStatFlags)
		COPY(dwStatTime0)
		COPY(dwStatTime1)
		COPY(dwStatFrames)
		COPY(dwStatCount)
		COPY(dwStatFramerateMin)
		COPY(dwStatFramerateAvg)
		COPY(dwStatFramerateMax)
		COPY(dwOSDX)
		COPY(dwOSDY)
		COPY(dwOSDPixel)
		COPY(dwOSDColor)
		COPY(dwOSDFrame)
		COPY(dwScreenCaptureFlags)
		COPY(szScreenCapturePath)
		COPY(dwOSDBgndColor)
		COPY(dwVideoCaptureFlags)
		COPY(szVideoCapturePath)
		COPY(dwVideoFramerate)
		COPY(dwVideoFramesize)
		COPY(dwVideoFormat)
		COPY(dwVideoQuality)
		COPY(dwVideoCaptureThreads)
		COPY(dwScreenCaptureQuality)
		COPY(dwScreenCaptureThreads)
		COPY(dwAudioCaptureFlags)
		COPY(dwVideoCaptureFlagsEx)
		COPY(dwAudioCaptureFlags2)
		COPY(dwStatFrameTimeMin)
		COPY(dwStatFrameTimeAvg)
		COPY(dwStatFrameTimeMax)
		COPY(dwStatFrameTimeCount)
		COPY(dwStatFrameTimeBuf)
		COPY(dwStatFrameTimeBufPos)
		COPY(dwStatFrameTimeBufFramerate)
		COPY(qwAudioCapturePTTEventPush)
		COPY(qwAudioCapturePTTEventRelease)
		COPY(qwAudioCapturePTTEventPush2)
		COPY(qwAudioCapturePTTEventRelease2)
		COPY(dwPrerecordSizeLimit)
		COPY(dwPrerecordTimeLimit)
		COPY(qwStatTotalTime)
		COPY(dwStatFrameTimeLowBuf)
		COPY(dwStatFramerate1Dot0PercentLow)
		COPY(dwStatFramerate0Dot1PercentLow)
		COPY(dw1Dot0PercentLowBufPos)
		COPY(dw0Dot1PercentLowBufPos)
		COPY(dwProcessPerfCountersFlags)
		COPY(dwProcessPerfCountersCount)
		COPY(dwProcessPerfCountersSamplingPeriod)
		COPY(dwProcessPerfCountersSamplingTime)
		COPY(dwProcessPerfCountersTimestamp)
		COPY(qwLatencyMarkerPresentTimestamp)
		COPY(dwResolutionX)
		COPY(dwResolutionY)
		COPY(qwInputSampleTime)
		COPY(qwSimStartTime)
		COPY(qwSimEndTime)
		COPY(qwRenderSubmitStartTime)
		COPY(qwRenderSubmitEndTime)
		COPY(qwPresentStartTime)
		COPY(qwPresentEndTime)
		COPY(qwDriverStartTime)
		COPY(qwDriverEndTime)
		COPY(qwOsRenderQueueStartTime)
		COPY(qwOsRenderQueueEndTime)
		COPY(qwGpuRenderStartTime)
		COPY(qwGpuRenderEndTime)
		COPY(dwGpuActiveRenderTime)
		COPY(dwGpuFrameTime)
		COPY(arrPerfCounters)
#undef COPY
		
		if (i == ptr->dwLastForegroundApp) {
			mem->foreground_app = e;
		}
		mem->app_list.push_back(e);
	}
	*/
	
	return mem;
}

} // namespace pyRTSS

