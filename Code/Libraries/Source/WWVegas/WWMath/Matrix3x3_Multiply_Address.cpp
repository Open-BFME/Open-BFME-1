// cl: /DNDEBUG /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
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

// Out-of-line copy of the WWINLINE Matrix3x3::operator* the retail linker
// kept as a real function. Taking its address forces MSVC to emit the
// COMDAT body instead of inlining it away, the same lever matrix4x4.cpp
// uses for Matrix4x4::operator*. The angle-bracket form is load-bearing:
// this directory's own quoted matrix3.h is the older Generals-era `Matrix3`.

#include <matrix3.h>

Matrix3x3 (*const Matrix3x3_Multiply_Address)(const Matrix3x3 &, const Matrix3x3 &) = &operator*;
