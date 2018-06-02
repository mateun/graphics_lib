// graphics_lib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "graphics_lib.h"


// This is an example of an exported variable
GRAPHICS_LIB_API int ngraphics_lib=0;

// This is an example of an exported function.
GRAPHICS_LIB_API int fngraphics_lib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see graphics_lib.h for the class definition
Cgraphics_lib::Cgraphics_lib()
{
    return;
}
