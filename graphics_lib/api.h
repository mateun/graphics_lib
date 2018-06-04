#pragma once
#ifdef GRAPHICS_LIB_EXPORTS
#define GRAPHICS_LIB_API __declspec(dllexport)
#else
#define GRAPHICS_LIB_API __declspec(dllimport)
#endif
