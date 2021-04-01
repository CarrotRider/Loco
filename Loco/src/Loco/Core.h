#pragma once

#ifdef LOCO_PLATFORM_WINDOWS
	#ifdef LOCO_BUILD_DLL
		#define LOCO_API __declspec(dllexport)
	#else
		#define LOCO_API __declspec(dllimport)
	#endif
#else
	#error Loco only supports Windows now!
#endif
