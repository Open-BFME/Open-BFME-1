// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?getPing@Pinger@@UAEHVAsciiString@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
//
// Pinger::getPing, 0x0065FD70, 307 bytes.
//
// ZH: MutexClass::LockClass m(m_pingMapMutex, 0); if (m.Failed()) return false;
// std::map<std::string,Int>::const_iterator it = m_pingMap.find(hostname.str());
// return it != end() ? it->second : -1. Layout proved byte-exact by the sibling
// body Pinger_getPingString.cpp: vtable(0), m_requestMutex(4), m_responseMutex(0xC),
// m_pingMapMutex(0x14), m_pad(0x1C..0x74), m_pingMap(0x74).

#include "string_base.h"
#include <map>
#include <string>

class MutexClass
{
	void *handle;
	unsigned locked;

public:
	enum { WAIT_INFINITE = -1 };
	class LockClass
	{
		MutexClass &mutex;
		bool failed;
	public:
		LockClass(MutexClass &m, int time = MutexClass::WAIT_INFINITE);
		~LockClass();
		bool Failed() { return failed; }
	};
};

extern const char g_bfmeEmptyAscii[];

typedef unsigned short UnsignedShort;

struct BfmeAsciiStringData
{
	char m_pad00[4];
	UnsignedShort m_length;
	UnsignedShort m_pad06;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *str)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(str);
	}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	const char *str() const
	{
		return m_data ? &m_data->m_text[0] : g_bfmeEmptyAscii;
	}

private:
	BfmeAsciiStringData *m_data;
};

class Pinger
{
public:
	virtual int getPing(AsciiString hostname);

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	MutexClass m_pingMapMutex;
	unsigned char m_pad[0x58];
	_STL::map<_STL::string, int> m_pingMap;
};

// ?getPing@Pinger@@UAEHVAsciiString@@@Z
int Pinger::getPing(AsciiString hostname)
{
	MutexClass::LockClass m(m_pingMapMutex, 0);
	if (m.Failed())
		return false;

	_STL::map<_STL::string, int>::const_iterator it = m_pingMap.find(hostname.str());
	if (it != m_pingMap.end())
		return it->second;

	return -1;
}
