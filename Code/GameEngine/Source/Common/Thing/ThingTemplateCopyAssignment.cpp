// cl: /DNDEBUG /MD
// BFME's expanded ThingTemplate copy assignment.  The Zero Hour twin is the
// compiler-generated ThingTemplate::operator= in ThingFactory.cpp; the BFME
// record keeps that order but adds the fields visible in the retail body.

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_bfmeHead[0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &other);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

struct KindOfBlock
{
	unsigned int m_values[6];
};

struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
	unsigned char m_bfmeBytes[0x5c];
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);

private:
	unsigned int m_data[3];
};

class BfmeThingBVA
{
public:
	void bfmeStepBVA(BfmeThingBVA *other);

	BfmeThingBVA *bfmeGoBVA(BfmeThingBVA *other)
	{
		if (this != other)
		{
			bfmeStepBVA(other);
			m_bfmeFlag = true;
			m_bfmeWhat = other->m_bfmeWhat;
		}
		return this;
	}

	unsigned char m_bfmeHead[0x0c];
	int m_bfmeWhat;
	bool m_bfmeFlag;
};

// The callees below are incremental-link thunks.  Their ledger names have no
// parameters, but the retail call sites use the thiscall ABI of the body they
// forward to.  Casting only the call expression preserves both the known thunk
// relocation and the real destination/source register sequence.
extern void j_00020815();
extern void j_0001a7a8();
extern void j_0003530f();
extern void j_0003e851();
extern void j_00010447();
extern void j_000288c6();
extern void j_00023aba();
extern void j_0002df29();
extern void j_00015447();
extern void j_000414f7();
extern void j_0000b4fb();
extern void j_0004a746();
extern void j_00035981();

class BfmeCopyReceiver
{
};

union BfmeCopyCall
{
	void (*freeFunction)();
	void (BfmeCopyReceiver::*memberFunction)(const void *);
};

#define BFME_COPY_THUNK(thunk, target, source) do { \
	BfmeCopyCall _call; \
	_call.freeFunction = (thunk); \
	(((BfmeCopyReceiver *)(target))->*_call.memberFunction)((source)); \
} while (0)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public ScienceInfoBase
{
public:
	ThingTemplate &operator=(const ThingTemplate &other);

private:
	UnicodeString m_displayName;
	UnicodeString m_description;
	UnicodeString m_recruitText;
	UnicodeString m_reviveText;

	AsciiString m_hotkey;
	AsciiString m_nameString;
	AsciiString m_editorName;
	AsciiString m_defaultOwningSide;
	AsciiString m_commandSetString;
	AsciiString m_selectedPortraitImageName;
	AsciiString m_buttonImageName;
	AsciiString m_upgradeCameoUpgradeNames[5];
	AsciiString m_shadowTextureName;
	AsciiString m_unknownString50;
	AsciiString m_unknownString54;
	AsciiString m_experienceScalarTableName;
	AsciiString m_unknownString5c;

	BfmeCopyElementA m_geometryInfo;
	unsigned char m_unknownGeometry[0x0c];
	KindOfBlock m_kindOf;
	unsigned char m_unknownE0[0x1b4];

	struct Raw12
	{
		unsigned int m_words[3];
	};

	Raw12 m_behaviorModuleInfo;
	Raw12 m_drawModuleInfo;
	Raw12 m_clientUpdateModuleInfo;
	Raw12 m_clientBehaviorModuleInfo;
	Raw12 m_unknownModule2c4;
	Rva0076F980Mid m_unknownMid2d0;
	Rva0076F980Mid m_unknownMid2dc;
	Rva0076F980Mid m_unknownMid2e8;
	unsigned int m_unknown2f4;
	Raw12 m_unknown2f8;
	Raw12 m_unknown304;
	Raw12 m_unknown310;
	Raw12 m_unknown31c;
	Raw12 m_unitSpecificSounds;
	Raw12 m_unitSpecificFX;
	Raw12 m_unknown340;
	Raw12 m_unknown34c;
	Raw12 m_browser;
	BfmeThingBVA m_bfmeBVA[2];

	unsigned int m_scalar038c;
	unsigned int m_scalar0390;
	unsigned int m_scalar0394;
	unsigned int m_scalar0398;
	unsigned int m_scalar039c;
	unsigned int m_scalar03a0;
	unsigned int m_scalar03a4;
	unsigned int m_scalar03a8;
	unsigned int m_scalar03ac;
	unsigned int m_scalar03b0;
	unsigned int m_scalar03b4;
	unsigned int m_scalar03b8;
	unsigned int m_scalar03bc;
	unsigned int m_scalar03c0;
	unsigned int m_scalar03c4;
	unsigned int m_scalar03c8;
	unsigned int m_scalar03cc;
	unsigned int m_scalar03d0;
	unsigned int m_scalar03d4;
	unsigned int m_scalar03d8;
	unsigned int m_scalar03dc;
	unsigned int m_scalar03e0;
	unsigned int m_scalar03e4;
	unsigned int m_scalar03e8;
	unsigned int m_scalar03ec;
	unsigned int m_scalar03f0;
	unsigned int m_scalar03f4;
	unsigned int m_scalar03f8;
	unsigned int m_scalar03fc;
	unsigned int m_scalar0400;
	unsigned int m_scalar0404;
	unsigned int m_scalar0408;
	unsigned int m_scalar040c;
	unsigned int m_scalar0410;
	unsigned int m_scalar0414;
	unsigned int m_scalar0418;
	unsigned int m_scalar041c;
	unsigned int m_scalar0420;
	unsigned int m_scalar0424;
	unsigned int m_scalar0428;
	unsigned int m_scalar042c;
	unsigned int m_scalar0430;
	unsigned int m_scalar0434;
	unsigned int m_scalar0438;
	unsigned int m_scalar043c;
	unsigned int m_scalar0440;
	unsigned int m_scalar0444;
	unsigned int m_scalar0448;
	unsigned int m_scalar044c;
	unsigned int m_scalar0450;
	unsigned int m_scalar0454;
	unsigned int m_scalar0458;
	unsigned int m_scalar045c;
	unsigned int m_scalar0460;
	unsigned int m_scalar0464;
	unsigned int m_scalar0468;
	unsigned int m_scalar046c;
	unsigned int m_scalar0470;
	unsigned int m_scalar0474;

	unsigned short m_short0478;
	unsigned short m_short047a;
	unsigned short m_short047c;
	unsigned short m_short047e;
	unsigned short m_short0480;
	unsigned short m_short0482;

	unsigned char m_byte0484;
	unsigned char m_byte0485;
	unsigned char m_byte0486;
	unsigned char m_byte0487;
	unsigned char m_byte0488;
	unsigned char m_byte0489;
	unsigned char m_byte048a;
	unsigned char m_byte048b;
	unsigned char m_byte048c;
	unsigned char m_byte048d;
	unsigned char m_byte048e;
	unsigned char m_byte048f;
	unsigned char m_byte0490;
	unsigned char m_byte0491;
	unsigned char m_byte0492;
	unsigned char m_byte0493;
	unsigned char m_byte0494;
	unsigned char m_byte0495;
	unsigned char m_byte0496;
	unsigned char m_byte0497;
	unsigned char m_byte0498;
	unsigned char m_byte0499;
	unsigned char m_byte049a;
	unsigned char m_byte049b;
	unsigned char m_byte049c;
	unsigned char m_byte049d;

	unsigned int m_dword04a0;
	unsigned int m_dword04a4;
	unsigned int m_dword04a8;
	unsigned int m_dword04ac;
	unsigned char m_byte04b0;
	unsigned char m_byte04b1;
	unsigned int m_dword04b4;
	Raw12 m_liveCameraOffset;
	unsigned int m_dword04c4;
	unsigned char m_byte04c8;
	unsigned char m_byte04c9;
	unsigned char m_byte04ca;
	unsigned char m_byte04cb;
	unsigned char m_byte04cc;
	unsigned char m_byte04cd;
	unsigned int m_dword04d0;
};

ThingTemplate &ThingTemplate::operator=(const ThingTemplate &other)
{
	ScienceInfoBase::operator=(other);

	m_displayName = other.m_displayName;
	m_description = other.m_description;
	m_recruitText = other.m_recruitText;
	m_reviveText = other.m_reviveText;
	m_hotkey = other.m_hotkey;
	m_nameString = other.m_nameString;
	m_editorName = other.m_editorName;
	m_defaultOwningSide = other.m_defaultOwningSide;
	m_commandSetString = other.m_commandSetString;
	m_selectedPortraitImageName = other.m_selectedPortraitImageName;
	m_buttonImageName = other.m_buttonImageName;
	register AsciiString *upgradeTarget = m_upgradeCameoUpgradeNames;
	register int upgradeDifference = (char *)other.m_upgradeCameoUpgradeNames
		- (char *)m_upgradeCameoUpgradeNames;
	register int upgradeCount = 5;
	do
	{
		upgradeTarget->operator=(*(AsciiString *)
			((char *)upgradeTarget + upgradeDifference));
		++upgradeTarget;
		--upgradeCount;
	} while (upgradeCount != 0);
	m_shadowTextureName = other.m_shadowTextureName;
	m_unknownString50 = other.m_unknownString50;
	m_unknownString54 = other.m_unknownString54;
	m_experienceScalarTableName = other.m_experienceScalarTableName;
	m_unknownString5c = other.m_unknownString5c;

	m_geometryInfo.bfmeAssign(
		const_cast<BfmeCopyElementA *>(&other.m_geometryInfo));
	BFME_COPY_THUNK(j_00020815, &m_unknownGeometry,
		&other.m_unknownGeometry);

	m_kindOf = other.m_kindOf;

	BFME_COPY_THUNK(j_0001a7a8, &m_unknownE0, &other.m_unknownE0);
	BFME_COPY_THUNK(j_0003530f, &m_behaviorModuleInfo,
		&other.m_behaviorModuleInfo);
	BFME_COPY_THUNK(j_0003530f, &m_drawModuleInfo,
		&other.m_drawModuleInfo);
	BFME_COPY_THUNK(j_0003530f, &m_clientUpdateModuleInfo,
		&other.m_clientUpdateModuleInfo);
	BFME_COPY_THUNK(j_0003530f, &m_clientBehaviorModuleInfo,
		&other.m_clientBehaviorModuleInfo);
	BFME_COPY_THUNK(j_0003e851, &m_unknownModule2c4,
		&other.m_unknownModule2c4);
	m_unknownMid2d0 = other.m_unknownMid2d0;
	m_unknownMid2dc = other.m_unknownMid2dc;
	m_unknownMid2e8 = other.m_unknownMid2e8;
	m_unknown2f4 = other.m_unknown2f4;
	BFME_COPY_THUNK(j_00010447, &m_unknown2f8, &other.m_unknown2f8);
	BFME_COPY_THUNK(j_000288c6, &m_unknown304, &other.m_unknown304);
	BFME_COPY_THUNK(j_00023aba, &m_unknown310, &other.m_unknown310);
	BFME_COPY_THUNK(j_0002df29, &m_unknown31c, &other.m_unknown31c);
	BFME_COPY_THUNK(j_00015447, &m_unitSpecificSounds,
		&other.m_unitSpecificSounds);
	BFME_COPY_THUNK(j_000414f7, &m_unitSpecificFX, &other.m_unitSpecificFX);
	BFME_COPY_THUNK(j_0000b4fb, &m_unknown340, &other.m_unknown340);
	BFME_COPY_THUNK(j_0004a746, &m_unknown34c, &other.m_unknown34c);
	BFME_COPY_THUNK(j_00035981, &m_browser, &other.m_browser);

	for (int i = 0; i < 2; ++i)
	{
		m_bfmeBVA[i].bfmeGoBVA(
			const_cast<BfmeThingBVA *>(&other.m_bfmeBVA[i]));
	}

	m_scalar038c = other.m_scalar038c;
	m_scalar0390 = other.m_scalar0390;
	m_scalar0394 = other.m_scalar0394;
	m_scalar0398 = other.m_scalar0398;
	m_scalar039c = other.m_scalar039c;
	m_scalar03a0 = other.m_scalar03a0;
	m_scalar03a4 = other.m_scalar03a4;
	m_scalar03a8 = other.m_scalar03a8;
	m_scalar03ac = other.m_scalar03ac;
	m_scalar03b0 = other.m_scalar03b0;
	m_scalar03b4 = other.m_scalar03b4;
	m_scalar03b8 = other.m_scalar03b8;
	m_scalar03bc = other.m_scalar03bc;
	m_scalar03c0 = other.m_scalar03c0;
	m_scalar03c4 = other.m_scalar03c4;
	m_scalar03c8 = other.m_scalar03c8;
	m_scalar03cc = other.m_scalar03cc;
	m_scalar03d0 = other.m_scalar03d0;
	m_scalar03d4 = other.m_scalar03d4;
	m_scalar03d8 = other.m_scalar03d8;
	m_scalar03dc = other.m_scalar03dc;
	m_scalar03e0 = other.m_scalar03e0;
	m_scalar03e4 = other.m_scalar03e4;
	m_scalar03e8 = other.m_scalar03e8;
	m_scalar03ec = other.m_scalar03ec;
	m_scalar03f0 = other.m_scalar03f0;
	m_scalar03f4 = other.m_scalar03f4;
	m_scalar03f8 = other.m_scalar03f8;
	m_scalar03fc = other.m_scalar03fc;
	m_scalar0400 = other.m_scalar0400;
	m_scalar0404 = other.m_scalar0404;
	m_scalar0408 = other.m_scalar0408;
	m_scalar040c = other.m_scalar040c;
	m_scalar0410 = other.m_scalar0410;
	m_scalar0414 = other.m_scalar0414;
	m_scalar0418 = other.m_scalar0418;
	m_scalar041c = other.m_scalar041c;
	m_scalar0420 = other.m_scalar0420;
	m_scalar0424 = other.m_scalar0424;
	m_scalar0428 = other.m_scalar0428;
	m_scalar042c = other.m_scalar042c;
	m_scalar0430 = other.m_scalar0430;
	m_scalar0434 = other.m_scalar0434;
	m_scalar0438 = other.m_scalar0438;
	m_scalar043c = other.m_scalar043c;
	m_scalar0440 = other.m_scalar0440;
	m_scalar0444 = other.m_scalar0444;
	m_scalar0448 = other.m_scalar0448;
	m_scalar044c = other.m_scalar044c;
	m_scalar0450 = other.m_scalar0450;
	m_scalar0454 = other.m_scalar0454;
	m_scalar0458 = other.m_scalar0458;
	m_scalar045c = other.m_scalar045c;
	m_scalar0460 = other.m_scalar0460;
	m_scalar0464 = other.m_scalar0464;
	m_scalar0468 = other.m_scalar0468;
	m_scalar046c = other.m_scalar046c;
	m_scalar0470 = other.m_scalar0470;
	m_scalar0474 = other.m_scalar0474;

	m_short0478 = other.m_short0478;
	m_short047a = other.m_short047a;
	m_short047c = other.m_short047c;
	m_short047e = other.m_short047e;
	m_short0480 = other.m_short0480;
	m_short0482 = other.m_short0482;

	m_byte0484 = other.m_byte0484;
	m_byte0485 = other.m_byte0485;
	m_byte0486 = other.m_byte0486;
	m_byte0487 = other.m_byte0487;
	m_byte0488 = other.m_byte0488;
	m_byte0489 = other.m_byte0489;
	m_byte048a = other.m_byte048a;
	m_byte048b = other.m_byte048b;
	m_byte048c = other.m_byte048c;
	m_byte048d = other.m_byte048d;
	m_byte048e = other.m_byte048e;
	m_byte048f = other.m_byte048f;
	m_byte0490 = other.m_byte0490;
	m_byte0491 = other.m_byte0491;
	m_byte0492 = other.m_byte0492;
	m_byte0493 = other.m_byte0493;
	m_byte0494 = other.m_byte0494;
	m_byte0495 = other.m_byte0495;
	m_byte0496 = other.m_byte0496;
	m_byte0497 = other.m_byte0497;
	m_byte0498 = other.m_byte0498;
	m_byte0499 = other.m_byte0499;
	m_byte049a = other.m_byte049a;
	m_byte049b = other.m_byte049b;
	m_byte049c = other.m_byte049c;
	m_byte049d = other.m_byte049d;

	m_dword04a0 = other.m_dword04a0;
	m_dword04a4 = other.m_dword04a4;
	m_dword04a8 = other.m_dword04a8;
	m_dword04ac = other.m_dword04ac;
	m_byte04b0 = other.m_byte04b0;
	m_byte04b1 = other.m_byte04b1;
	m_dword04b4 = other.m_dword04b4;
	m_liveCameraOffset = other.m_liveCameraOffset;
	m_dword04c4 = other.m_dword04c4;
	m_byte04c8 = other.m_byte04c8;
	m_byte04c9 = other.m_byte04c9;
	m_byte04ca = other.m_byte04ca;
	m_byte04cb = other.m_byte04cb;
	m_byte04cc = other.m_byte04cc;
	m_byte04cd = other.m_byte04cd;
	m_dword04d0 = other.m_dword04d0;

	return *this;
}
