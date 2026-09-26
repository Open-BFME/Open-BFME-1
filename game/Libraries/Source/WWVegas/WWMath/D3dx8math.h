// Minimal D3dx8math.h for the WWMath byte-match build. The DirectX 8 SDK header
// is not vendored; Matrix3D::Get_Inverse only needs the D3DXMATRIX type and the
// D3DXMatrixInverse declaration (its __stdcall/extern "C" linkage is what shapes
// the call site).
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef D3DX8MATH_H
#define D3DX8MATH_H

#ifndef BFME_D3DXMATRIX_DEFINED
#define BFME_D3DXMATRIX_DEFINED
typedef struct _D3DXMATRIX {
	float m[4][4];
} D3DXMATRIX;
#endif // BFME_D3DXMATRIX_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

D3DXMATRIX* __stdcall D3DXMatrixInverse(D3DXMATRIX* pOut, float* pDeterminant, const D3DXMATRIX* pM);

#ifdef __cplusplus
}
#endif

#endif
