#include "RTSS.hpp"

#include <iostream>

namespace pyRTSS {

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
	
	*mem = *ptr;
	
	return mem;
}

} // namespace pyRTSS

