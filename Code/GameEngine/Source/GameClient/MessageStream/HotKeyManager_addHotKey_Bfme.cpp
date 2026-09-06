// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport

#define private public
#define protected public
#include <map>
#undef protected
#undef private
#include "Common/AsciiString.h"

class GameWindow;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	int m_04;
};

class HotKeyAsciiStringLess
{
public:
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};

namespace _STL
{
template <> struct less<AsciiString> : public HotKeyAsciiStringLess
{
};
}

class HotKey
{
public:
	__forceinline HotKey()
	{
		m_win = NULL;
		m_key.clear();
	}

	GameWindow *m_win;
	AsciiString m_key;
};

class HotKeyManager : public SubsystemInterface
{
public:
	void addHotKey(GameWindow *win, const AsciiString &key, bool commandKey);

private:
	_STL::map<AsciiString, HotKey> m_hotKeys;
	_STL::map<AsciiString, HotKey> m_commandKeys;
};

// ?addHotKey@HotKeyManager@@QAEXPAVGameWindow@@ABVAsciiString@@_N@Z
void HotKeyManager::addHotKey(GameWindow *win, const AsciiString &key, bool commandKey)
{
	_STL::map<AsciiString, HotKey> &keys = commandKey ? m_commandKeys : m_hotKeys;
	AsciiString lowerKey = key;
	lowerKey.toLower();
	if (keys._M_t._M_find(lowerKey) != keys._M_t._M_header._M_data)
	{
		lowerKey.toUpper();
		if (keys._M_t._M_find(lowerKey) != keys._M_t._M_header._M_data)
			return;
	}
	HotKey hotKey;
	hotKey.m_key.set(lowerKey);
	hotKey.m_win = win;
	HotKey &storedHotKey = keys[lowerKey];
	storedHotKey.m_win = hotKey.m_win;
	AsciiString *storedKey = &storedHotKey.m_key;
	storedKey->set(hotKey.m_key);
}
