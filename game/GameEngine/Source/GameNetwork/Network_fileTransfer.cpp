// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"

class BFMEConnectionManager
{
public:
	void sendFileChunk(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
};

class ConnectionManager
{
public:
	UnsignedShort sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
};

class Network
{
public:
	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	virtual UnsignedShort sendFileAnnounce(AsciiString path, UnsignedByte playerMask);

protected:
	AsciiString m_name;
	BFMEConnectionManager *m_conMgr;
};

void Network::sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID)
{
	m_conMgr->sendFileChunk(path, playerMask, commandID);
}

UnsignedShort Network::sendFileAnnounce(AsciiString path, UnsignedByte playerMask)
{
	return reinterpret_cast<ConnectionManager *>(m_conMgr)->sendFileAnnounce(path, playerMask);
}
