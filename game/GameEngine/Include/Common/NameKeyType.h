/*
**	Command & Conquer Generals Zero Hour(tm)
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
#pragma once

// Existing BFME1 contract factored from inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h; values preserved.
enum NameKeyType
{
	NAMEKEY_INVALID					= 0,
	NAMEKEY_MAX							= 1<<23,					// max ordinal value of a NameKey (some code relies on these fitting into 24 bits safely)
	FORCE_NAMEKEYTYPE_LONG	= 0x7fffffff	// a trick to ensure the NameKeyType is a 32-bit int
};
