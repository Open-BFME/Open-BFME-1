// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

template<class T> struct StringData
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Rva00434A90
{
public:
	static Bool lookup(const char *label, UnicodeString *subtitle);
};

Bool Rva00434A90::lookup(const char *label, UnicodeString *subtitle)
{
	AsciiString subtitleLabel("SUBTITLE:");
	Bool exists;
	((StringBase<char> *)&subtitleLabel)->concat(label, label ? (int)strlen(label) : 0);
	((StringBase<unsigned short> *)subtitle)->set(
		(const StringBase<unsigned short> &)TheGameText->fetch(subtitleLabel, &exists));
	return exists;
}
