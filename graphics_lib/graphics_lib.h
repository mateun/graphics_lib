// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GRAPHICS_LIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GRAPHICS_LIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GRAPHICS_LIB_EXPORTS
#define GRAPHICS_LIB_API __declspec(dllexport)
#else
#define GRAPHICS_LIB_API __declspec(dllimport)
#endif

// This class is exported from the graphics_lib.dll
class GRAPHICS_LIB_API Cgraphics_lib {
public:
	Cgraphics_lib(void);
	// TODO: add your methods here.
};

extern GRAPHICS_LIB_API int ngraphics_lib;

GRAPHICS_LIB_API int fngraphics_lib(void);
