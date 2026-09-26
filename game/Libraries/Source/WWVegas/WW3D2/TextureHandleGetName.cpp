// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME owning texture-handle name getter: RVA 0x008FF5B0, full 231 bytes.
// MeshLoadContextClass::Add_Legacy_Material calls this at 0x0096F45B and
// 0x0096F477 before comparing texture names. Retail dereferences the handle,
// invokes the texture's first virtual slot for its name, and returns an
// owning StringClass copy; an empty handle yields an empty string.
// The copy constructor is the named 0x008FF470 body and Free_String is
// 0x009DB7A0. The final RET 4 at 0x008FF694 ends before INT3 at 0x008FF697.
#include "wwstring.h"

class TextureClass
{
public:
    virtual const char *Get_Name() const;
};

class BfmeHandleCX
{
public:
    TextureClass *p;
    StringClass Get_Texture_Name() const;
};

StringClass BfmeHandleCX::Get_Texture_Name() const
{
    const char *name = p ? p->Get_Name() : 0;
    StringClass result(name);
    return result;
}
