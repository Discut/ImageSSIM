#pragma once

#ifndef EXPORT_IS
#define EXPORT_IS

#ifdef Export_Dll
#define Export_Dll __declspec(dllexport)
#else
#define Export_Dll __declspec(dllimport)
#endif 

Export_Dll double SSIM_Percent(const char* imgPath1, const char* imgPath2);

extern "C"{
    Export_Dll double C_SSIM_Percent(const char* imgPath1, const char* imgPath2);
}

#endif