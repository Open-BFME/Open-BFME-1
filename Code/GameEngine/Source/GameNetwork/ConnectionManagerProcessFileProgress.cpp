// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class NetFileProgressCommandMsg
{
public:
	unsigned int getPlayerID() const { return m_playerID; }
	unsigned short getFileID();
	int getProgress();

private:
	unsigned char m_unknown[0xC];
	unsigned int m_playerID;
};

namespace _STL
{
	template <class T> struct less {};
	template <class T> class allocator {};
	template <class First, class Second> struct pair {};

	template <class Key, class Value, class Compare = less<Key>,
		class Allocator = allocator<pair<const Key, Value> > >
	class map
	{
	public:
		Value &operator[](const Key &key);

	private:
		void *m_header;
		unsigned int m_size;
		unsigned int m_allocator;
	};
}

typedef _STL::map<unsigned short, int> FileProgressMap;

class ConnectionManager
{
private:
	void processFileProgress(NetFileProgressCommandMsg *msg);

	unsigned char m_unknown[0x12130];
	FileProgressMap m_fileProgressMap[8];
};

template <class T> inline const T &maxRef(const T &left, const T &right)
{
	return left > right ? left : right;
}

void ConnectionManager::processFileProgress(NetFileProgressCommandMsg *msg)
{
	int oldProgress = m_fileProgressMap[msg->getPlayerID()][msg->getFileID()];
	m_fileProgressMap[msg->getPlayerID()][msg->getFileID()] =
		maxRef(oldProgress, msg->getProgress());
}
