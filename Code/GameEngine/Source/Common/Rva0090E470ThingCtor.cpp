// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "wwstring.h"

// The base body is the already matched BfmeThingSJ constructor at 0x0090E3D0.
// This derived type's RTTI name is not recovered; its vftable is pinned by the
// retail address written by the constructor.
class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

class BfmeThingSJ : public GenBase009EB7D0
{
public:
	BfmeThingSJ(int what);
	virtual void handle();

	int m_bfme14;
	StringClass m_bfmeName;
	Gen_00920A20 m_bfmeData;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
};

class Rva0090E470Thing : public BfmeThingSJ
{
public:
	Rva0090E470Thing(const char *name, int what, int field);
	virtual void derivedSlot1();
	virtual void derivedSlot3();

private:
	StringClass m_name;
	int m_field;
};

Rva0090E470Thing::Rva0090E470Thing(const char *name, int what, int field)
	: BfmeThingSJ(what),
	  m_name(name, false)
{
	m_field = field;
}
