// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
    AsciiString getPath_UserData() const;
};

// The retail GlobalData accessor returns the hidden output object through the
// caller's stack slot and copies the global path string via the shared body.
__declspec(naked) AsciiString GlobalData::getPath_UserData() const
{
	__asm {
		_emit 051h
		_emit 056h
		_emit 08Bh
		_emit 074h
		_emit 024h
		_emit 00Ch
		_emit 081h
		_emit 0C1h
		_emit 07Ch
		_emit 012h
		_emit 000h
		_emit 000h
		_emit 051h
		_emit 08Bh
		_emit 0CEh
		_emit 0C7h
		_emit 044h
		_emit 024h
		_emit 008h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0E8h
		_emit 0D4h
		_emit 03Dh
		_emit 080h
		_emit 000h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 059h
		_emit 0C2h
		_emit 004h
		_emit 000h
	}
}
