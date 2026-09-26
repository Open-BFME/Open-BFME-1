// cl: /DNDEBUG /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Out-of-line copies of the WWINLINE Matrix4x4 operators the retail linker
// kept as real functions. The repo's own WWMath/matrix4.h is the older
// Generals-era `Matrix4`; retail is the Zero Hour `Matrix4x4` rename, so this
// TU compiles against the vendored Zero Hour header instead of the local one.
// Taking each operator's address is what forces MSVC to emit the COMDAT body
// rather than inlining it away. The angle-bracket form is load-bearing: a
// quoted include would find this directory's own Generals-era matrix4.h first.

#include <matrix4.h>

Matrix4x4 (*const Matrix4x4_Multiply_Address)(const Matrix4x4 &, const Matrix4x4 &) = &operator*;

void (Matrix4x4::*const Matrix4x4_Init_Address)(float, float, float, float,
                                                float, float, float, float,
                                                float, float, float, float,
                                                float, float, float, float) = &Matrix4x4::Init;

typedef Vector4 & (Vector4::*V4AddAssign)(const Vector4 &);
V4AddAssign Vector4_Add_Assign_Address = &Vector4::operator+=;
