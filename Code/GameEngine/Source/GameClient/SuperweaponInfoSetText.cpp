// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Canonical Zero Hour SuperweaponInfo::setText body with BFME's vtable layout.

#include "StringInline.h"

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
};

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
