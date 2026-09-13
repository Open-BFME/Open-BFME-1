// cl: /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Icode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"

#include "GameNetwork/DownloadManager.h"

class Open2Rec6270C0
{
public:
	Open2Rec6270C0( const Open2Rec6270C0 &other );
};

class BfmeErasedValue_00627200
{
public:
	BfmeErasedValue_00627200() {}
	~BfmeErasedValue_00627200();

	AsciiString server;
	AsciiString userName;
	AsciiString password;
	AsciiString file;
	AsciiString localFile;
	AsciiString regKey;
	Bool tryResume;
};

namespace std
{
template <>
inline void _Construct<BfmeErasedValue_00627200, BfmeErasedValue_00627200>(
	BfmeErasedValue_00627200 *place, const BfmeErasedValue_00627200 &value )
{
	new ( place ) Open2Rec6270C0( *(const Open2Rec6270C0 *)&value );
}
}

class Rva00627810DownloadManager
{
public:
	void queueFileForDownload( AsciiString server, AsciiString username,
		AsciiString password, AsciiString file, AsciiString localfile,
		AsciiString regkey, Bool tryResume );

private:
	unsigned char m_prefix[0x18];
	std::list<BfmeErasedValue_00627200> m_queuedDownloads;
};

// ?queueFileForDownload@DownloadManager@@QAEXVAsciiString@@00000_N@Z
void Rva00627810DownloadManager::queueFileForDownload( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	BfmeErasedValue_00627200 q;
	q.file = file;
	q.localFile = localfile;
	q.password = password;
	q.regKey = regkey;
	q.server = server;
	q.tryResume = tryResume;
	q.userName = username;

	m_queuedDownloads.push_back(q);
}
