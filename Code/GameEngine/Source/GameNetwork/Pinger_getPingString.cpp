// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?getPingString@Pinger@@UAE?AVAsciiString@@H@Z:
// Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
// ZH Pinger::getPingString: lock the ping-map mutex, hex-encode each
// clamped ping as "%2.2X", concatenate, return by value.

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
	};
};

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
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
	void __cdecl format(AsciiString fmt, ...);
	void concat(const AsciiString &other)
	{
		const StringBase<char> *src = (const StringBase<char> *)&other;
		((StringBase<char> *)this)->concat(
			src->m_data ? &src->m_data->data[0] : (const char *)"",
			src->m_data ? src->m_data->length : 0);
	}

private:
	char *m_text;
};

class Pinger
{
public:
	virtual AsciiString getPingString(int timeout);

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	MutexClass m_pingMapMutex;
	unsigned char m_pad[0x58];
	_STL::map<_STL::string, int> m_pingMap;
};

// ?getPingString@Pinger@@UAE?AVAsciiString@@H@Z
AsciiString Pinger::getPingString(int timeout)
{
	MutexClass::LockClass m(m_pingMapMutex);

	AsciiString pingString;
	AsciiString tmp;
	for (_STL::map<_STL::string, int>::const_iterator it = m_pingMap.begin();
		it != m_pingMap.end(); ++it)
	{
		int ping = it->second;
		if (ping < 0 || ping > timeout)
			ping = timeout;
		ping = ping * 255 / timeout;
		tmp.format(AsciiString("%2.2X"), ping);
		pingString.concat(tmp);
	}
	return pingString;
}
