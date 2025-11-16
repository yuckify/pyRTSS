#include "RTSS.hpp"

#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>

namespace py = pybind11;

template<typename T>
class FixedArray {
	
	T *_beg;
	T *_end;
	
public:
	
	FixedArray() {
		_beg = nullptr;
		_end = nullptr;
	}

	template<typename C, size_t s>
	FixedArray(const T (*ptr)[s]) {
		_beg = ptr;
		_end = &ptr[s];
	}
	
	FixedArray(T *a, T *b) {
		_beg = a;
		_end = b;
	}
	
	FixedArray(T *a, size_t s) {
		_beg = a;
		_end = a + s;
	}
	
	FixedArray(const FixedArray<T> &other) {
		_beg = other._beg;
		_end = other._end;
	}
	
	T &get(size_t i) {
		assert(i < length());
		return _beg[i];
	}
	
	T &operator[](size_t i) {
		return get(i);
	}
	
	void set(size_t i, T &item) {
		assert(i <length());
		_beg[i] = item;
	}
	
	size_t length() {
		return _end - _beg;
	}
	
	size_t size() {
		return length();
	}
};

std::ostream &operator<<(std::ostream &out, LARGE_INTEGER &item) {
	out<<item.QuadPart;
	return out;
}

std::ostream &operator<<(std::ostream &out, 
		RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY &item) {
	
	out<<"{"
	
#define PRINT(x) <<#x ": " <<item.x <<", "
	PRINT(dwID)
	PRINT(dwParam)
	<<"dwData: " <<item.dwData
#undef PRINT
	
	<<"}";
	
	return out;
}

std::ostream &operator<<(std::ostream &out, 
		RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &item) {
	
	out<<"{"
	
#define PRINT(x) <<#x ": " <<item.x <<", "
#define PRINT_ARR(x)
	PRINT(dwProcessID)
	PRINT(szName)
	PRINT(dwFlags)
	PRINT(dwTime0)
	PRINT(dwTime1)
	PRINT(dwFrames)
	PRINT(dwFrameTime)
	PRINT(dwStatFlags)
	PRINT(dwStatTime0)
	PRINT(dwStatTime1)
	PRINT(dwStatFrames)
	PRINT(dwStatCount)
	PRINT(dwStatFramerateMin)
	PRINT(dwStatFramerateAvg)
	PRINT(dwStatFramerateMax)
	PRINT(dwOSDX)
	PRINT(dwOSDY)
	PRINT(dwOSDPixel)
	PRINT(dwOSDColor)
	PRINT(dwOSDFrame)
	PRINT(dwScreenCaptureFlags)
	PRINT(szScreenCapturePath)
	PRINT(dwOSDBgndColor)
	PRINT(dwVideoCaptureFlags)
	PRINT(szVideoCapturePath)
	PRINT(dwVideoFramerate)
	PRINT(dwVideoFramesize)
	PRINT(dwVideoFormat)
	PRINT(dwVideoQuality)
	PRINT(dwVideoCaptureThreads)
	PRINT(dwScreenCaptureQuality)
	PRINT(dwScreenCaptureThreads)
	PRINT(dwAudioCaptureFlags)
	PRINT(dwVideoCaptureFlagsEx)
	PRINT(dwAudioCaptureFlags2)
	PRINT(dwStatFrameTimeMin)
	PRINT(dwStatFrameTimeAvg)
	PRINT(dwStatFrameTimeMax)
	PRINT(dwStatFrameTimeCount)
	<<"dwStatFrameTimeBuf: [...], "
	PRINT(dwStatFrameTimeBufPos)
	PRINT(dwStatFrameTimeBufFramerate)
	PRINT(qwAudioCapturePTTEventPush)
	PRINT(qwAudioCapturePTTEventRelease)
	PRINT(qwAudioCapturePTTEventPush2)
	PRINT(qwAudioCapturePTTEventRelease2)
	PRINT(dwPrerecordSizeLimit)
	PRINT(dwPrerecordTimeLimit)
	PRINT(qwStatTotalTime)
	<<"dwStatFrameTimeLowBuf: [...], "
	PRINT(dwStatFramerate1Dot0PercentLow)
	PRINT(dwStatFramerate0Dot1PercentLow)
	PRINT(dw1Dot0PercentLowBufPos)
	PRINT(dw0Dot1PercentLowBufPos)
	PRINT(dwProcessPerfCountersFlags)
	PRINT(dwProcessPerfCountersCount)
	PRINT(dwProcessPerfCountersSamplingPeriod)
	PRINT(dwProcessPerfCountersSamplingTime)
	PRINT(dwProcessPerfCountersTimestamp)
	PRINT(qwLatencyMarkerPresentTimestamp)
	PRINT(dwResolutionX)
	PRINT(dwResolutionY)
	PRINT(qwInputSampleTime)
	PRINT(qwSimStartTime)
	PRINT(qwSimEndTime)
	PRINT(qwRenderSubmitStartTime)
	PRINT(qwRenderSubmitEndTime)
	PRINT(qwPresentStartTime)
	PRINT(qwPresentEndTime)
	PRINT(qwDriverStartTime)
	PRINT(qwDriverEndTime)
	PRINT(qwOsRenderQueueStartTime)
	PRINT(qwOsRenderQueueEndTime)
	PRINT(qwGpuRenderStartTime)
	PRINT(qwGpuRenderEndTime)
	PRINT(dwGpuActiveRenderTime)
	PRINT(dwGpuFrameTime)
	<<"arrPerfCounters: [...]"
#undef PRINT
#undef PRINT_ARR
	
	<<"}";
	
	return out;
}

std::ostream &operator<<(std::ostream &out, 
		RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &item) {
	
	out<<"{"
	
#define PRINT(x) <<#x ": \"" <<item.x <<"\", "
	PRINT(szOSD)
	PRINT(szOSDOwner)
	PRINT(szOSDEx)
	<<"buffer: [...], "
	<<"szOSDEx2: " <<item.szOSDEx2 <<", "
#undef PRINT
	
	<<"}";
	
	return out;
}

struct impl {
	template<typename T>
	static void python_decl_fixed_array(py::module_ &m) {
		std::ostringstream tname;
		tname<<"FixedArray<" <<typeid(T).name() <<">";
		
		typedef FixedArray<T> FA;
		
		py::class_<FA>(m, tname.str().c_str())
			.def("__getitem__", &FA::get)
			.def("__setitem__", &FA::set)
			.def("__len__", &FA::length)
			.def("__str__", +[](FA &arr) {
				std::ostringstream str;
				str<<"[";
				for (int i = 0; i < arr.size(); i++) {
					str<<arr[i];
					if (i != arr.size() - 1)
						str<<", ";
				}
				str<<"]";
				return str.str();
			})
		;
	}
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

PYBIND11_MODULE(_pyRTSS, m, py::mod_gil_not_used()) {
	m.doc()               = "python bindings for Rivatuner Statistics Server";
    m.attr("__version__") = VERSION_INFO;

	impl::python_decl_fixed_array<DWORD>(m);
	impl::python_decl_fixed_array<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY>(m);
	impl::python_decl_fixed_array<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY>(m);
	
#define ATTR(x) m.attr(#x) = x
	ATTR(OSDFLAG_UPDATED);
	ATTR(STATFLAG_RECORD);
	ATTR(APPFLAG_OGL);
	ATTR(APPFLAG_DD);
	ATTR(APPFLAG_D3D8);
	ATTR(APPFLAG_D3D9);
	ATTR(APPFLAG_D3D9EX);
	ATTR(APPFLAG_D3D10);
	ATTR(APPFLAG_D3D11);
	ATTR(APPFLAG_D3D12);
	ATTR(APPFLAG_D3D12AFR);
	ATTR(APPFLAG_VULKAN);
	ATTR(APPFLAG_API_USAGE_MASK);
	ATTR(APPFLAG_ARCHITECTURE_X64);
	ATTR(APPFLAG_ARCHITECTURE_UWP);
	ATTR(APPFLAG_PROFILE_UPDATE_REQUESTED);
	ATTR(SCREENCAPTUREFLAG_REQUEST_CAPTURE);
	ATTR(SCREENCAPTUREFLAG_REQUEST_CAPTURE_OSD);
	ATTR(VIDEOCAPTUREFLAG_REQUEST_CAPTURE_START);
	ATTR(VIDEOCAPTUREFLAG_REQUEST_CAPTURE_PROGRESS);
	ATTR(VIDEOCAPTUREFLAG_REQUEST_CAPTURE_STOP);
	ATTR(VIDEOCAPTUREFLAG_REQUEST_CAPTURE_MASK);
	ATTR(VIDEOCAPTUREFLAG_REQUEST_CAPTURE_OSD);
	ATTR(VIDEOCAPTUREFLAG_INTERNAL_RESIZE);
	ATTR(PROCESS_PERF_COUNTER_ID_RAM_USAGE);
	ATTR(PROCESS_PERF_COUNTER_ID_D3DKMT_VRAM_USAGE_LOCAL);
	ATTR(PROCESS_PERF_COUNTER_ID_D3DKMT_VRAM_USAGE_SHARED);
#undef ATTR
	
	typedef FixedArray<DWORD> FA_DWORD;
	typedef FixedArray<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY> FA_OSD;
	typedef FixedArray<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY> FA_APP;
	
#define DEF_RO(n) .def_readonly(#n, &::RTSS_SHARED_MEMORY::n)
	auto rtss_class = py::class_<::RTSS_SHARED_MEMORY, RTSS_SHARED_MEMORY_P>(m, "RTSS_SHARED_MEMORY");
	rtss_class
		DEF_RO(dwSignature)
		DEF_RO(dwVersion)
		DEF_RO(dwAppEntrySize)
		DEF_RO(dwAppArrOffset)
		DEF_RO(dwAppArrSize)
		DEF_RO(dwOSDEntrySize)
		DEF_RO(dwOSDArrOffset)
		DEF_RO(dwOSDArrSize)
		DEF_RO(dwOSDFrame)
		DEF_RO(dwBusy)
		DEF_RO(dwDesktopVideoCaptureFlags)
		.def_property_readonly("dwDesktopVideoCaptureStat",
			+[](const RTSS_SHARED_MEMORY &s) -> FA_DWORD {
				return FA_DWORD((DWORD *)s.dwDesktopVideoCaptureStat, 
					ARRAY_SIZE(s.dwDesktopVideoCaptureStat));
			})
		DEF_RO(dwLastForegroundApp)
		DEF_RO(dwLastForegroundAppProcessID)
		DEF_RO(dwProcessPerfCountersEntrySize)
		DEF_RO(dwProcessPerfCountersArrOffset)
		DEF_RO(qwLatencyMarkerSetTimestamp)
		DEF_RO(qwLatencyMarkerResetTimestamp)
		.def_property_readonly("arrOSD",
			+[](const RTSS_SHARED_MEMORY &s) -> FA_OSD {
				return FA_OSD(
					(RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY *)s.arrOSD,
					ARRAY_SIZE(s.arrOSD)
				);
			})
		.def_property_readonly("arrApp",
			+[](const RTSS_SHARED_MEMORY &s) -> FA_APP {
				return FA_APP(
					(RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY *)s.arrApp,
					ARRAY_SIZE(s.arrApp)
				);
			})
		DEF_RO(autoVideoCaptureParam)
	;
#undef DEF_RO
	
	py::class_<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY>(m, "RTSS_SHARED_MEMORY_OSD_ENTRY")
		.def_property_readonly("szOSD", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &obj) -> std::string {
				return std::string(obj.szOSD);
			})
		.def_property_readonly("szOSDOwner", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &obj) -> std::string {
				return std::string(obj.szOSDOwner);
			})
		.def_property_readonly("szOSDEx", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &obj) -> std::string {
				return std::string(obj.szOSDEx);
			})
		.def_property_readonly("buffer", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &obj) -> FixedArray<BYTE> {
				return FixedArray<BYTE>((BYTE *)obj.buffer, ARRAY_SIZE(obj.buffer));
			})
		.def_property_readonly("szOSDEx2", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &obj) -> std::string {
				return std::string(obj.szOSDEx2);
			})
	;
	
#define DEF_RO(n) .def_readonly(#n, &::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY::n)
	py::class_<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY>(m, "RTSS_SHARED_MEMORY_APP_ENTRY")
		DEF_RO(dwProcessID)
		.def_property_readonly("szName", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> std::string {
				return std::string(obj.szName);
			})
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
		.def_property_readonly("szScreenCapturePath", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> std::string {
				return std::string(obj.szScreenCapturePath);
			})
		DEF_RO(dwOSDBgndColor)
		DEF_RO(dwVideoCaptureFlags)
		.def_property_readonly("szVideoCapturePath", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> std::string {
				return std::string(obj.szVideoCapturePath);
			})
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
		.def_property_readonly("dwStatFrameTimeBuf", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> FixedArray<DWORD> {
				return FixedArray<DWORD>((DWORD *)obj.dwStatFrameTimeBuf, 
					ARRAY_SIZE(obj.dwStatFrameTimeBuf));
			})
		DEF_RO(dwStatFrameTimeBufPos)
		DEF_RO(dwStatFrameTimeBufFramerate)
		DEF_RO(qwAudioCapturePTTEventPush)
		DEF_RO(qwAudioCapturePTTEventRelease)
		DEF_RO(qwAudioCapturePTTEventPush2)
		DEF_RO(qwAudioCapturePTTEventRelease2)
		DEF_RO(dwPrerecordSizeLimit)
		DEF_RO(dwPrerecordTimeLimit)
		DEF_RO(qwStatTotalTime)
		.def_property_readonly("dwStatFrameTimeLowBuf", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> FixedArray<DWORD> {
				return FixedArray<DWORD>((DWORD *)obj.dwStatFrameTimeLowBuf, 
					ARRAY_SIZE(obj.dwStatFrameTimeLowBuf));
			})
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
		.def_property_readonly("arrPerfCounters", 
			+[](const RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY &obj) -> FixedArray<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY> {
				return FixedArray<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY>(
					(RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY *)obj.arrPerfCounters, 
					ARRAY_SIZE(obj.arrPerfCounters));
			})
	;
#undef DEF_RO
	
#define DEF_RO(n) .def_readonly(#n, &::RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY::n)
	py::class_<RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY>(m, "RTSS_SHARED_MEMORY_PROCESS_PERF_COUNTER_ENTRY")
		DEF_RO(dwID)
		DEF_RO(dwParam)
		DEF_RO(dwData)
	;
#undef DEF_RO
	
	py::class_<pyRTSS::RTSS>(m, "RTSS")
		.def(py::init<>())
		.def("version", &pyRTSS::RTSS::version)
		.def("snapshot", &pyRTSS::RTSS::snapshot)
	;
}

