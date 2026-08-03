// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

class GlobalData
{
    unsigned char m_padding[0x127c];
    AsciiString m_pathUserData;

public:
    AsciiString getPath_UserData() const;
};

// The retail GlobalData accessor returns the hidden output object through the
// caller's stack slot and copies the path string from its +0x127c member.
AsciiString GlobalData::getPath_UserData() const
{
	return m_pathUserData;
}
