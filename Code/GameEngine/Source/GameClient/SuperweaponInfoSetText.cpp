// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?setText@SuperweaponInfo@@QAEXABVUnicodeString@@0@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Canonical Zero Hour SuperweaponInfo::setText body with BFME's vtable layout.

#include "StringInline.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class SuperweaponInfo
{
private:
	void *m_vtable;
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;

public:
	void setText(const UnicodeString &name, const UnicodeString &time);
};

void SuperweaponInfo::setText(const UnicodeString &name, const UnicodeString &time)
{
	m_nameDisplayString->setText(name);
	m_timeDisplayString->setText(time);
}
