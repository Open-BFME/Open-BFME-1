// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib

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
// inputs/reference/shims/languagefilter documents for UnicodeString. campaignmanagerascii
// fixes it the same way, with a visible StringBase<char> delegation, but its
// StringBase<char> would collide with the StringBase<wchar_t> that Network.cpp's
// languagefilter shim defines.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
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
