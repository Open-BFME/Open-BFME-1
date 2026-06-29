#include "xfer.h"
#include "snapshot.h"
#include "../math/coord3d.h"
#include "../math/coord2d.h"
#include "../math/icoord.h"
#include "../math/region.h"
#include "../math/color.h"

Xfer::Xfer()
{
}

Xfer::~Xfer()
{
}

bool Xfer::IsLoading() const
{
    return false;
}

bool Xfer::IsStoring() const
{
    return false;
}

bool Xfer::IsCRC() const
{
    return false;
}

bool Xfer::IsLightCRC() const
{
    return false;
}

void Xfer::SkipBadBlock(Snapshot &snapshot, unsigned int size)
{
}

__declspec(naked) Xfer &Xfer::operator==(char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x62797465
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x75627974
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x73687274
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x75736874
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x75696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(float &f)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x7265616c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(__int64 &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 8
        push ecx
        push 0x693634
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(bool &b)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x626f6f6c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(Snapshot &snapshot)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [ecx]
        push esi
        call dword ptr [eax + 0x0c]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(Coord3DBase& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00633364
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(ICoord3D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69633364
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Region3D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00723364
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 12
        add edi, 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(IRegion3D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69723364
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 12
        add edi, 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Coord2D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00633264
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(ICoord2D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69633264
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Region2D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00723264
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 8
        add edi, 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(IRegion2D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69723264
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 8
        add edi, 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RealRange& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x726e6765
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBColor& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00726762
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBAColorReal& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x72676272
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 16
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBAColorInt& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x72676269
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 16
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
