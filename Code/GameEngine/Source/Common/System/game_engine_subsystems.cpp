// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
    AsciiString getPath_UserData() const;

private:
    char m_unreconstructed_00[0x127C];
    AsciiString m_userDataDir;
};

// The retail GlobalData accessor returns the hidden output object through the
// caller's stack slot and copies the global path string via the shared body.
AsciiString GlobalData::getPath_UserData() const
{
	return m_userDataDir;
}
