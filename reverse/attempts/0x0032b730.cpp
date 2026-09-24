// ?evaluateNamedSelected@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z
// partial score=0.9716 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Parameter
{
public:
	const AsciiString &getString(void) const
	{
		return *(const AsciiString *)((const char *)this + 0x10);
	}
};

class Condition
{
public:
	Int getCustomData(void) const
	{
		return *(const Int *)((const char *)this + 0x44);
	}
	void setCustomData(Int value)
	{
		*(Int *)((char *)this + 0x44) = value;
	}
	UnsignedInt getCustomFrame(void) const
	{
		return *(const UnsignedInt *)((const char *)this + 0x48);
	}
	void setCustomFrame(UnsignedInt value)
	{
		*(UnsignedInt *)((char *)this + 0x48) = value;
	}
};

class Object
{
public:
	const AsciiString &getName(void) const
	{
		return *(const AsciiString *)((const char *)this + 0x84);
	}
};

class Drawable
{
public:
	Object *getObject(void)
	{
		return *(Object **)((char *)this + 0xfc);
	}
	Object *getObject(void) const
	{
		return *(Object **)((const char *)this + 0xfc);
	}
};

typedef _STL::list<Drawable *> DrawableList;

__forceinline Bool bfmeStringEqual(const AsciiString &left, const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right) == 0;
}

class GameEngine
{
public:
#define BFME_ENGINE_SLOT(n) virtual void slot##n(void) = 0
	BFME_ENGINE_SLOT(00); BFME_ENGINE_SLOT(01); BFME_ENGINE_SLOT(02);
	BFME_ENGINE_SLOT(03); BFME_ENGINE_SLOT(04); BFME_ENGINE_SLOT(05);
	BFME_ENGINE_SLOT(06); BFME_ENGINE_SLOT(07); BFME_ENGINE_SLOT(08);
	BFME_ENGINE_SLOT(09); BFME_ENGINE_SLOT(10); BFME_ENGINE_SLOT(11);
	BFME_ENGINE_SLOT(12); BFME_ENGINE_SLOT(13); BFME_ENGINE_SLOT(14);
#undef BFME_ENGINE_SLOT
	virtual Bool isMultiplayerSession(void) = 0;
};

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n(void) = 0
	BFME_UI_SLOT(00); BFME_UI_SLOT(01); BFME_UI_SLOT(02); BFME_UI_SLOT(03);
	BFME_UI_SLOT(04); BFME_UI_SLOT(05); BFME_UI_SLOT(06); BFME_UI_SLOT(07);
	BFME_UI_SLOT(08); BFME_UI_SLOT(09); BFME_UI_SLOT(10); BFME_UI_SLOT(11);
	BFME_UI_SLOT(12); BFME_UI_SLOT(13); BFME_UI_SLOT(14); BFME_UI_SLOT(15);
	BFME_UI_SLOT(16); BFME_UI_SLOT(17); BFME_UI_SLOT(18); BFME_UI_SLOT(19);
	BFME_UI_SLOT(20); BFME_UI_SLOT(21); BFME_UI_SLOT(22); BFME_UI_SLOT(23);
	BFME_UI_SLOT(24); BFME_UI_SLOT(25); BFME_UI_SLOT(26); BFME_UI_SLOT(27);
	BFME_UI_SLOT(28); BFME_UI_SLOT(29); BFME_UI_SLOT(30); BFME_UI_SLOT(31);
	BFME_UI_SLOT(32); BFME_UI_SLOT(33); BFME_UI_SLOT(34); BFME_UI_SLOT(35);
	BFME_UI_SLOT(36); BFME_UI_SLOT(37); BFME_UI_SLOT(38); BFME_UI_SLOT(39);
	BFME_UI_SLOT(40); BFME_UI_SLOT(41); BFME_UI_SLOT(42); BFME_UI_SLOT(43);
	BFME_UI_SLOT(44); BFME_UI_SLOT(45); BFME_UI_SLOT(46); BFME_UI_SLOT(47);
	BFME_UI_SLOT(48); BFME_UI_SLOT(49); BFME_UI_SLOT(50); BFME_UI_SLOT(51);
	BFME_UI_SLOT(52); BFME_UI_SLOT(53); BFME_UI_SLOT(54); BFME_UI_SLOT(55);
	BFME_UI_SLOT(56); BFME_UI_SLOT(57); BFME_UI_SLOT(58); BFME_UI_SLOT(59);
	BFME_UI_SLOT(60); BFME_UI_SLOT(61);
#undef BFME_UI_SLOT
	virtual UnsignedInt getFrameSelectionChanged(void) = 0;
	virtual const DrawableList *getAllSelectedDrawables(void) = 0;
};

extern GameEngine *TheGameEngine;
extern InGameUI *TheInGameUI;

class ScriptConditions
{
protected:
	Bool evaluateNamedSelected(Condition *pCondition, Parameter *pUnitParm);
};

// ?evaluateNamedSelected@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z
Bool ScriptConditions::evaluateNamedSelected(Condition *pCondition, Parameter *pUnitParm)
{
	if (TheGameEngine->isMultiplayerSession())
		return false;

	Bool anyChanges = false;
	if (pCondition->getCustomData() == 0)
		anyChanges = true;

	if (TheInGameUI->getFrameSelectionChanged() != pCondition->getCustomFrame())
		anyChanges = true;

	if (!anyChanges)
	{
		if (pCondition->getCustomData() == -1)
			return false;
		if (pCondition->getCustomData() == 1)
			return true;
	}

	Bool isSelected = false;
	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
	DrawableList::const_iterator end = selected->end();
	DrawableList::const_iterator it = selected->begin();
	for (; it != end; ++it)
	{
		Drawable *draw = *it;
		if (bfmeStringEqual(draw->getObject()->getName(), pUnitParm->getString()))
		{
			isSelected = true;
			break;
		}
	}

	pCondition->setCustomData(-1);
	if (isSelected)
		pCondition->setCustomData(1);
	pCondition->setCustomFrame(TheInGameUI->getFrameSelectionChanged());
	return isSelected;
}
