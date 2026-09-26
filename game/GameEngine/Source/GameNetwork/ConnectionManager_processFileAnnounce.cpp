// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ConnectionManager::processFileAnnounce, RVA0x0066A030, 256 bytes.
// Matched incoming type20 dispatcher calls ILT0x89F4 to this body.
// Record the filename and recipient mask by command ID, then initialize each
// player's file-transfer progress: zero for recipients and 100 for nonrecipients.
// BFME owns these maps in ConnectionManager at +12118/+12124/+12130.
// The filename result is a full-expression temporary. Inline forwarding to
// StringBase<char> preserves its real assignment and destruction lifetime.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

template<class T> class StringBase {
 friend class AsciiString;
private:
 StringBase():m_data(0) {} StringBase(const StringBase&); ~StringBase();
public:
 void set(const StringBase&);
 StringBase &operator=(const StringBase& other){set(other);return *this;}
 void *m_data;
};
class AsciiString:private StringBase<char> {
public:
 AsciiString(){} AsciiString(const AsciiString& s):StringBase<char>(s){} ~AsciiString(){}
 AsciiString&operator=(const AsciiString& s){StringBase<char>::operator=(s);return *this;}
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
	m_fileCommandMap[msg->getFileID()] = msg->getRealFilename();
	m_fileRecipientMaskMap[msg->getFileID()] = msg->getPlayerMask();
	for (int i = 0; i < 8; ++i) {
		if ((1 << i) & msg->getPlayerMask()) {
			m_fileProgressMap[i][msg->getFileID()] = 0;
		} else {
			m_fileProgressMap[i][msg->getFileID()] = 100;
		}
	}
}
