#pragma once
#include <math.h>
inline double pow(double x, unsigned int y) { return pow(x, (double)y); }
// Verbatim DX8.1 SDK d3dx8core.h
HRESULT WINAPI D3DXGetErrorStringA(HRESULT hr, LPSTR pBuffer, UINT BufferLen);
