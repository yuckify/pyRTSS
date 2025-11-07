#include "RTSS.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;


PYBIND11_MODULE(pyRTSS, m, py::mod_gil_not_used()) {

#define DEF_RO(n) .def_readonly(#n, &pyRTSS::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY::n)
	py::class_<pyRTSS::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY>(m, "RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY")
		DEF_RO(dwID)
		DEF_RO(dwParam)
		DEF_RO(dwData)
	;
#undef DEF_RO
	
#define DEF_RO(n) .def_readonly(#n, &pyRTSS::RTSS_SHARED_MEMORY_APP_ENTRY::n)
	py::class_<pyRTSS::RTSS_SHARED_MEMORY_APP_ENTRY, std::shared_ptr<pyRTSS::RTSS_SHARED_MEMORY_APP_ENTRY>>(m, "RTSS_SHARED_MEMORY_APP_ENTRY")
		.def(py::init<>())
		DEF_RO(dwProcessID)
		DEF_RO(szName)
		DEF_RO(dwFlags)
		DEF_RO(dwTime0)
		DEF_RO(dwTime1)
		DEF_RO(dwFrames)
		DEF_RO(dwFrameTime)
		DEF_RO(dwStatFlags)
		DEF_RO(dwStatTime0)
		DEF_RO(dwStatTime1)
		DEF_RO(dwStatFrames)
		DEF_RO(dwStatCount)
		DEF_RO(dwStatFramerateMin)
		DEF_RO(dwStatFramerateAvg)
		DEF_RO(dwStatFramerateMax)
		DEF_RO(dwOSDX)
		DEF_RO(dwOSDY)
		DEF_RO(dwOSDPixel)
		DEF_RO(dwOSDColor)
		DEF_RO(dwOSDFrame)
		DEF_RO(dwScreenCaptureFlags)
		DEF_RO(szScreenCapturePath)
		DEF_RO(dwOSDBgndColor)
		DEF_RO(dwVideoCaptureFlags)
		DEF_RO(szVideoCapturePath)
		DEF_RO(dwVideoFramerate)
		DEF_RO(dwVideoFramesize)
		DEF_RO(dwVideoFormat)
		DEF_RO(dwVideoQuality)
		DEF_RO(dwVideoCaptureThreads)
		DEF_RO(dwScreenCaptureQuality)
		DEF_RO(dwScreenCaptureThreads)
		DEF_RO(dwAudioCaptureFlags)
		DEF_RO(dwVideoCaptureFlagsEx)
		DEF_RO(dwAudioCaptureFlags2)
		DEF_RO(dwStatFrameTimeMin)
		DEF_RO(dwStatFrameTimeAvg)
		DEF_RO(dwStatFrameTimeMax)
		DEF_RO(dwStatFrameTimeCount)
		DEF_RO(dwStatFrameTimeBuf)
		DEF_RO(dwStatFrameTimeBufPos)
		DEF_RO(dwStatFrameTimeBufFramerate)
		DEF_RO(qwAudioCapturePTTEventPush)
		DEF_RO(qwAudioCapturePTTEventRelease)
		DEF_RO(qwAudioCapturePTTEventPush2)
		DEF_RO(qwAudioCapturePTTEventRelease2)
		DEF_RO(dwPrerecordSizeLimit)
		DEF_RO(dwPrerecordTimeLimit)
		DEF_RO(qwStatTotalTime)
		DEF_RO(dwStatFrameTimeLowBuf)
		DEF_RO(dwStatFramerate1Dot0PercentLow)
		DEF_RO(dwStatFramerate0Dot1PercentLow)
		DEF_RO(dw1Dot0PercentLowBufPos)
		DEF_RO(dw0Dot1PercentLowBufPos)
		DEF_RO(dwProcessPerfCountersFlags)
		DEF_RO(dwProcessPerfCountersCount)
		DEF_RO(dwProcessPerfCountersSamplingPeriod)
		DEF_RO(dwProcessPerfCountersSamplingTime)
		DEF_RO(dwProcessPerfCountersTimestamp)
		DEF_RO(qwLatencyMarkerPresentTimestamp)
		DEF_RO(dwResolutionX)
		DEF_RO(dwResolutionY)
		DEF_RO(qwInputSampleTime)
		DEF_RO(qwSimStartTime)
		DEF_RO(qwSimEndTime)
		DEF_RO(qwRenderSubmitStartTime)
		DEF_RO(qwRenderSubmitEndTime)
		DEF_RO(qwPresentStartTime)
		DEF_RO(qwPresentEndTime)
		DEF_RO(qwDriverStartTime)
		DEF_RO(qwDriverEndTime)
		DEF_RO(qwOsRenderQueueStartTime)
		DEF_RO(qwOsRenderQueueEndTime)
		DEF_RO(qwGpuRenderStartTime)
		DEF_RO(qwGpuRenderEndTime)
		DEF_RO(dwGpuActiveRenderTime)
		DEF_RO(dwGpuFrameTime)
		DEF_RO(arrPerfCounters)
		
		.def("framerate", &pyRTSS::RTSS_SHARED_MEMORY_APP_ENTRY::framerate)
	;
#undef DEF_RO
	
#define DEF_RO(n) .def_readonly(#n, &pyRTSS::RTSS_SHARED_MEMORY::n)
	py::class_<pyRTSS::RTSS_SHARED_MEMORY, std::shared_ptr<pyRTSS::RTSS_SHARED_MEMORY>>(m, "RTSS_SHARED_MEMORY")
		.def(py::init<>())
		
	;
#undef DEF_RO
	
	py::class_<pyRTSS::RTSS>(m, "RTSS")
		.def(py::init<>())
		.def("version", &pyRTSS::RTSS::version)
		.def("snapshot", &pyRTSS::RTSS::snapshot)
	;
	
}

