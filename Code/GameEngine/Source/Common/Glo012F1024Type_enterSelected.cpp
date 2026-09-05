// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
//
// Open-BFME5: Glo012F1024Type::enterSelected, retail 0x003B3A00, 157 bytes.
// Same campaign-manager layout as step at 0x003B3900 (index +0xC, 32-byte
// entry vector +0x10). Address-derived method name: no caller recovered a
// source identifier.

#include "StringInline.h"

typedef int Int;

class Glo012F1024Item
{
public:
 void bfmeEnter(void);
 AsciiString name003A72F0(void);
};

class Glo012F1024Entry
{
public:
	Glo012F1024Item *select(AsciiString *key);

	char m_bfmeBody[0x20];
};

class BfmeEntryVector
{
public:
	Int bfmeSize(void) const { return m_bfmeFinish - m_bfmeStart; }

	Glo012F1024Entry *m_bfmeStart;
	Glo012F1024Entry *m_bfmeFinish;
};

class Glo012F1028Sub
{
public:
	void bfmeNotify(void);
};

class Glo012F1028Type
{
public:
	void m(const AsciiString &name);
	char m_bfmeHead[0x28];
	Glo012F1028Sub *m_bfmeSub;
};

extern Glo012F1028Type *Glo012F1028;

class Glo012F1024Type
{
public:
	void enterSelected(AsciiString *key);

private:
	char m_pad00[0x0C];
	Int m_bfmeIndex;
	BfmeEntryVector m_bfmeEntries;
};

// ?enterSelected@Glo012F1024Type@@QAEXPAVAsciiString@@@Z
void Glo012F1024Type::enterSelected(AsciiString *key)
{
	if (m_bfmeIndex < 0)
		return;

	if ((unsigned int)m_bfmeIndex >= (unsigned int)m_bfmeEntries.bfmeSize())
		return;

	Glo012F1024Entry *start = m_bfmeEntries.m_bfmeStart;
	Glo012F1024Item *item = start[m_bfmeIndex].select(key);
	if (item != 0)
	{
		Glo012F1028->m(item->name003A72F0());
		item->bfmeEnter();
		Glo012F1028->m_bfmeSub->bfmeNotify();
	}
}
