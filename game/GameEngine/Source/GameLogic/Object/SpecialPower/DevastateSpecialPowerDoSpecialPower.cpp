// DevastateSpecialPower::doSpecialPower at retail 0x0025A930 (75 B): slot 11 of
// the SpecialPowerModuleInterface table 0x010B4608, which the registered
// DevastateSpecialPower constructor 0x0025A7C0 stores at +0x10. It is reached
// only through ILT 0x0000E0D4, whose VA appears once in the image.
// Object::doSpecialPower (0x001C3790) calls slot 11 (+0x2C); the body ends `ret 4`
// and never reads `this`. Its only work is a debug report, "Error! Devastate
// Power requires either a target object or location": the power must be
// fired at an object or a location.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md

bool __cdecl _bfme_debugReportingEnabled();
// ?_bfme_debugRecordCallsite@@YAXH@Z -- game/GameEngine/Source/Common/Debug_recordCallsite.cpp
extern void _bfme_debugRecordCallsite(int n);

class BfmeMsgVHJ
{
public:
	virtual void bfmeSlot00VHJ();
	virtual void bfmeSlot04VHJ();
	virtual void bfmeSlot08VHJ();
	virtual void bfmeSlot0CVHJ();
	virtual void bfmeSlot10VHJ();
	virtual void bfmeSlot14VHJ();
	virtual void bfmeSlot18VHJ();
	virtual void bfmeSlot1CVHJ();
	virtual void bfmeSlot20VHJ();
	virtual void bfmeSlot24VHJ();
	virtual void bfmeSlot28VHJ();
	virtual void bfmeSlot2CVHJ();
	virtual void bfmeSlot30VHJ();
	virtual void bfmeSlot34VHJ();
	virtual class BfmeMsgVHJ *bfmeSlot38VHJ(const char *t);
	virtual void bfmeSlot3CVHJ();
	virtual void bfmeSlot40VHJ();
	virtual void bfmeSlot44VHJ();
	virtual void bfmeSlot48VHJ();
	virtual void bfmeSlot4cVHJ(int n);
	virtual void bfmeSlot50VHJ();
	virtual void bfmeSlot54VHJ();
	virtual void bfmeSlot58VHJ();
	virtual void bfmeSlot5CVHJ();
	virtual void bfmeSlot60VHJ();
	virtual void bfmeSlot64VHJ();
	virtual void bfmeSlot68VHJ();
	virtual void bfmeSlot6CVHJ();
};

struct Rva00889690Obj
{
public:
	virtual void bfmeOwn00VHJ();
	virtual void bfmeOwn04VHJ();
	virtual void bfmeOwn08VHJ();
	virtual void bfmeOwn0CVHJ();
	virtual void bfmeOwn10VHJ();
	virtual void bfmeOwn14VHJ();
	virtual void bfmeOwn18VHJ();
	virtual void bfmeOwn1CVHJ();
	virtual void bfmeOwn20VHJ();
	virtual void bfmeOwn24VHJ();
	virtual void bfmeOwn28VHJ();
	virtual void bfmeOwn2CVHJ();
	virtual void bfmeOwn30VHJ();
	virtual void bfmeOwn34VHJ();
	virtual void bfmeOwn38VHJ();
	virtual void bfmeOwn3CVHJ();
	virtual void bfmeOwn40VHJ();
	virtual void bfmeOwn44VHJ();
	virtual void bfmeOwn48VHJ();
	virtual void bfmeOwn4CVHJ();
	virtual void bfmeOwn50VHJ();
	virtual void bfmeOwn54VHJ();
	virtual void bfmeOwn58VHJ();
	virtual void bfmeOwn5CVHJ();
	virtual void bfmeOwn60VHJ();
	virtual void bfmeOwn64VHJ();
	virtual void bfmeOwn68VHJ();
	virtual class BfmeMsgVHJ *bfmeOwn6cVHJ(int a, int b);
};

extern Rva00889690Obj *g_rva00889690;

typedef unsigned int UnsignedInt;

class DevastateSpecialPower
{
public:
	virtual void doSpecialPower(UnsignedInt commandOptions);
};

void DevastateSpecialPower::doSpecialPower(UnsignedInt)
{
	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		g_rva00889690->bfmeOwn60VHJ();
		g_rva00889690->bfmeOwn6cVHJ(0, 0)->bfmeSlot38VHJ("Error! Devastate Power requires either a target object or location")->bfmeSlot4cVHJ(2);
	}
}
