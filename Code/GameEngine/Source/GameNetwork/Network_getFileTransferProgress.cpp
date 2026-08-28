// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

// Retail 0x00682640, Network vtable slot 24. Slots 20..24 are sendChat,
// sendDisconnectChat, sendFile, sendFileAnnounce and this one -- Zero Hour's
// declaration order, and their 8/4/12/8/8-byte returns line up with it.
//
// Its own TU because of the by-value AsciiString. Left declared-only, its copy
// constructor makes the temporary opaque and MSVC schedules the EH-registration
// store after `mov ecx, esp` instead of before it -- the same six-byte swap
// reference/shims/languagefilter documents for UnicodeString. campaignmanagerascii
// fixes it the same way, with a visible StringBase<char> delegation, but its
// StringBase<char> would collide with the StringBase<wchar_t> that Network.cpp's
// languagefilter shim defines.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Int getFileTransferProgress(Int playerID, AsciiString path);
};

class Network
{
public:
	virtual Int getFileTransferProgress(Int playerID, AsciiString path);

protected:
	AsciiString m_name;              // SubsystemInterface's, at +0x04
	ConnectionManager *m_conMgr;     // +0x08
};

Int Network::getFileTransferProgress(Int playerID, AsciiString path)
{
	return m_conMgr->getFileTransferProgress(playerID, path);
}
