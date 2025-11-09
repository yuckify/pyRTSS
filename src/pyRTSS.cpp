#include "RTSS.hpp"

#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
	PRINT(dwProcessID)
	PRINT(szName)
	PRINT(dwFlags)
	PRINT(dwTime0)
	PRINT(dwTime1)
	PRINT(dwFrames)
	PRINT(dwFrameTime)
#undef PRINT
	
	<<"}";
	
	
	
	return out;
}

std::ostream &operator<<(std::ostream &out, 
		RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_OSD_ENTRY &item) {
	
	out<<"{"
	
#define PRINT(x) <<#x ": \"" <<item.x <<"\", "
	PRINT(szOSD)
	PRINT(szOSDOwner)
#undef PRINT
	
	<<"}";
	
	return out;
}

struct impl {
	template<typename C, typename T, size_t size>
	static void python_decl_fixed_array(pybind11::module_ &m, const T (C::*member)[size]) {
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

PYBIND11_MODULE(pyRTSS, m, py::mod_gil_not_used()) {
	
	impl::python_decl_fixed_array(m, &RTSS_SHARED_MEMORY::dwDesktopVideoCaptureStat);
	impl::python_decl_fixed_array(m, &RTSS_SHARED_MEMORY::arrOSD);
	impl::python_decl_fixed_array(m, &RTSS_SHARED_MEMORY::arrApp);
	
	auto rtss_class = py::class_<::RTSS_SHARED_MEMORY, RTSS_SHARED_MEMORY_P>(m, "RTSS_SHARED_MEMORY");
	
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
					sizeof(s.dwDesktopVideoCaptureStat)/sizeof(s.dwDesktopVideoCaptureStat[0]));
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
					sizeof(s.arrOSD)/sizeof(s.arrOSD[0])
				);
			})
		.def_property_readonly("arrApp",
			+[](const RTSS_SHARED_MEMORY &s) -> FA_APP {
				return FA_APP(
					(RTSS_SHARED_MEMORY::RTSS_SHARED_MEMORY_APP_ENTRY *)s.arrApp,
					sizeof(s.arrApp)/sizeof(s.arrApp[0])
				);
			})
		DEF_RO(autoVideoCaptureParam)
	;
#undef DEF_RO
	
	py::class_<pyRTSS::RTSS>(m, "RTSS")
		.def(py::init<>())
		.def("version", &pyRTSS::RTSS::version)
		.def("snapshot", &pyRTSS::RTSS::snapshot)
	;
	
}

