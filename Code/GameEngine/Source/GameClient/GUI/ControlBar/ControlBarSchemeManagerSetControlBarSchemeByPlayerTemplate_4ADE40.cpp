// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Ireference/shims/ini /Ireference/shims/controlbarvtables /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

class ControlBarSchemeAsciiString;

template <typename T>
class StringBase
{
public:
	void concat(const T *text, int length);
	void set(const T *text, int length);
	int compare(const StringBase<T> &other) const;

private:
	friend class ControlBarSchemeAsciiString;
	StringBase(const StringBase<T> &source);
	StringBase(const T *text);
	~StringBase();
	void releaseBuffer();
};

class PlayerTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void _slot0(void) {}
	virtual void _slot1(void) {}
	virtual void _slot2(void) {}
	virtual void _slot3(void) {}
	virtual void _slot4(void) {}
	virtual void _slot5(void) {}
	virtual void _slot6(void) {}
	virtual void _slot7(void) {}
	virtual void _slot8(void) {}
	virtual void _slot9(void) {}
	virtual void _slot10(void) {}
	virtual UnsignedInt getWidth(void);
	virtual UnsignedInt getHeight(void);
};

extern Display *TheDisplay;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct RealCoord2D
{
	Real x;
	Real y;
};

class ControlBarSchemeAsciiString
{
public:
	ControlBarSchemeAsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	ControlBarSchemeAsciiString(const ControlBarSchemeAsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~ControlBarSchemeAsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}
	void set(const char *text, int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}
	bool isEmpty(void) const
	{
		return m_text == 0 || *(const UnsignedShort *)(m_text + 4) == 0;
	}
	Int compare(const ControlBarSchemeAsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(*(const StringBase<char> *)&other);
	}
	Int getLength(void) const
	{
		return m_text ? *(const UnsignedShort *)(m_text + 4) : 0;
	}
	const char *str(void) const
	{
		return m_text ? m_text + 8 : "";
	}
	Int compareNoCase(const ControlBarSchemeAsciiString &other) const
	{
		Int otherLen = other.getLength();
		const char *otherText = other.str();
		Int thisLen = getLength();
		const char *thisText = str();
		Int shorter = thisLen < otherLen ? thisLen : otherLen;

		Int difference = _memicmp(thisText, otherText, shorter);
		if(difference != 0)
			return difference;
		return thisLen - otherLen;
	}

private:
	char *m_text;
};

typedef _STL::list<class ControlBarScheme *> ControlBarSchemeList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
public:
	ControlBarSchemeAsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	ControlBarSchemeAsciiString m_side;

	void init(void);
};

class ControlBarSchemeManagerSetControlBarSchemeByPlayerTemplate
{
public:
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, Bool useSmall);
	ControlBarScheme *findControlBarScheme(ControlBarSchemeAsciiString name);

private:
	ControlBarScheme *m_currentScheme;
	RealCoord2D m_multiplyer;
	ControlBarSchemeList m_schemeList;
};

void ControlBarSchemeManagerSetControlBarSchemeByPlayerTemplate::setControlBarSchemeByPlayerTemplate(
	const PlayerTemplate *pt, Bool useSmall)
{
	if(!pt)
		return;
	ControlBarSchemeAsciiString side = *(const ControlBarSchemeAsciiString *)((const char *)pt + 8);
	if(useSmall)
		side.concat("Small", 5);
	ControlBarScheme *currentScheme = m_currentScheme;
	if(currentScheme && (currentScheme->m_side.compare(side) == 0))
	{
		currentScheme->init();
		return;
	}

	if(side.isEmpty())
		side.set("Observer", 8);
	ControlBarScheme *tempScheme = 0;
	ControlBarSchemeList::iterator it = m_schemeList.begin();
	while(it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if(!CBScheme)
		{
			++it;
			continue;
		}
		if(CBScheme->m_side.compareNoCase(side) == 0)
		{
			if(!tempScheme || tempScheme->m_ScreenCreationRes.x < CBScheme->m_ScreenCreationRes.x)
				tempScheme = CBScheme;
		}
		++it;
	}

	if(tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (Real)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (Real)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if(m_currentScheme)
		m_currentScheme->init();
}
