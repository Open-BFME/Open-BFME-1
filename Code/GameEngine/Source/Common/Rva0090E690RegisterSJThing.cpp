// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// FUZZY-TWIN of Code/Libraries/Source/WWVegas/WW3D2/Register_Animation_Prototype.cpp
// (?Register_Animation_Prototype@@YAXPBDHH@Z, 0x0090C000, 124B): same
// "if not Exists, allocate and Add_Prototype" shell, but retail here takes
// only ONE parameter (no `a`/`b` ints), allocates 0x3C bytes (sizeof
// BfmeThingSJ, not the twin's 0x24-byte Rva0090BD60Proto) and constructs it
// by calling the already-matched BfmeThingSJ constructor at 0x0090E3D0
// (landed as ?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z, object-symbol=ctor) instead of
// the twin's 3-arg Rva0090BD60Proto ctor.

#include "wwstring.h"

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

bool Render_Obj_Exists(const char *name);
void Add_Prototype(void *proto);

void rva0090e690RegisterSJThing(const char *name)
{
	if (name != 0 && !Render_Obj_Exists(name))
	{
		BfmeThingSJ *thing = new BfmeThingSJ((int)name);
		Add_Prototype(thing);
	}
}
