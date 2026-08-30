// ?processFileAnnounce@ConnectionManager@@AAEXPAVNetFileAnnounceCommandMsg@@@Z
// partial score=0.72 date=2026-08-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

class NetFileAnnounceCommandMsg
{
public:
	unsigned short getFileID();
	AsciiString getRealFilename();
	unsigned char getPlayerMask();
};

#include <map>

typedef std::map<unsigned short, AsciiString> FileCommandMap;
typedef std::map<unsigned short, unsigned char> FileMaskMap;
typedef std::map<unsigned short, int> FileProgressMap;

class ConnectionManager
{
private:
	void processFileAnnounce(NetFileAnnounceCommandMsg *msg);

	unsigned char m_unknown[0x12118];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileRecipientMaskMap;
	FileProgressMap m_fileProgressMap[8];
};

void ConnectionManager::processFileAnnounce(NetFileAnnounceCommandMsg *msg)
{
	unsigned short fileID = msg->getFileID();
	const AsciiString &filename = msg->getRealFilename();
	m_fileCommandMap[fileID] = filename;
	m_fileRecipientMaskMap[msg->getFileID()] = msg->getPlayerMask();
	for (int i = 0; i < 8; ++i) {
		if ((1 << i) & msg->getPlayerMask()) {
			m_fileProgressMap[i][msg->getFileID()] = 0;
		} else {
			m_fileProgressMap[i][msg->getFileID()] = 100;
		}
	}
}
