#ifndef RTSS_HPP
#define RTSS_HPP

#include <memory>
#include <vector>
#include <string>

#include <windows.h>
#include <RTSSSharedMemory.h>

typedef std::shared_ptr<::RTSS_SHARED_MEMORY> RTSS_SHARED_MEMORY_P;

namespace pyRTSS {

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

