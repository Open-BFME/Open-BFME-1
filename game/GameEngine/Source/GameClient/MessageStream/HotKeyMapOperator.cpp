// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "PreRTS.h"

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
	HotKey()
	{
		m_win = NULL;
		m_key.clear();
	}

	void *m_win;
	AsciiString m_key;
};

typedef _STL::map<AsciiString, HotKey> HotKeyMapOperator;

// retail 0x005B3E30
template HotKey &HotKeyMapOperator::operator[](const AsciiString &);
