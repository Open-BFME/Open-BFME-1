// Open-BFME5 conversions: module-data field-parse table builders.

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add(const FieldParse *f, unsigned int n);
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse(void);
};

extern const FieldParse g_bfme5FieldsA[];
extern const FieldParse g_bfme5FieldsB[];
extern const FieldParse g_bfme5FieldsC[];
extern const FieldParse g_bfme5FieldsD[];

void __cdecl bfme5BuildFieldParseA(MultiIniFieldParse *p)
{
	p->add(g_bfme5FieldsA, 0x58);
	p->add(DieMuxData::getFieldParse(), 0x2c);
	p->add(g_bfme5FieldsB, 0);
}

void __cdecl bfme5BuildFieldParseB(MultiIniFieldParse *p)
{
	p->add(g_bfme5FieldsC, 0x14);
	p->add(DieMuxData::getFieldParse(), 0x7c);
	p->add(g_bfme5FieldsD, 0);
}
