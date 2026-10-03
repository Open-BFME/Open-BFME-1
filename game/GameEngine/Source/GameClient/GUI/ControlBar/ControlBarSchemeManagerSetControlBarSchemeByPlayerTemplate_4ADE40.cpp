// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp

#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Display.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

struct RealCoord2D
{
	Real x;
	Real y;
};

// This local view keeps the byte-matched string operations while the adjacent
// retail classes use the header's AsciiString spelling at their interface.
class ControlBarSchemeAsciiString : public AsciiString
{
public:
	ControlBarSchemeAsciiString(const char *text) : AsciiString(text) {}
	ControlBarSchemeAsciiString(const ControlBarSchemeAsciiString &that) : AsciiString(that) {}
	~ControlBarSchemeAsciiString() {}

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
		return AsciiString::isEmpty();
	}
	Int compare(const ControlBarSchemeAsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(*(const StringBase<char> *)&other);
	}
	Int getLength(void) const
	{
		return AsciiString::getLength();
	}
	const char *str(void) const
	{
		return AsciiString::str();
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
};

typedef _STL::list<class ControlBarScheme *> ControlBarSchemeList;

class ControlBarSchemeManagerSetControlBarSchemeByPlayerTemplate
{
public:
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, Bool useSmall);

private:
	ControlBarScheme *m_currentScheme;
	RealCoord2D m_multiplyer;
	ControlBarSchemeList m_schemeList;
};

// ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z
void ControlBarSchemeManagerSetControlBarSchemeByPlayerTemplate::setControlBarSchemeByPlayerTemplate(
	const PlayerTemplate *pt, Bool useSmall)
{
	if(!pt)
		return;
	ControlBarSchemeAsciiString side = *(const ControlBarSchemeAsciiString *)((const char *)pt + 8);
	if(useSmall)
		side.concat("Small", 5);
	ControlBarScheme *currentScheme = m_currentScheme;
	if(currentScheme && (((ControlBarSchemeAsciiString *)&currentScheme->m_side)->compare(side) == 0))
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
		if(((ControlBarSchemeAsciiString *)&CBScheme->m_side)->compareNoCase(side) == 0)
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
		m_currentScheme = ((ControlBarSchemeManager *)this)->findControlBarScheme(
			AsciiString("Default"));
	}
	if(m_currentScheme)
		m_currentScheme->init();
}
