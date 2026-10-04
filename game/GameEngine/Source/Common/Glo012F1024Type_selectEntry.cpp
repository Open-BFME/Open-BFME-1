// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Glo012F1024Type::setCampaign, retail 0x003B41A0, 131 bytes.
// Same campaign-manager layout as step at 0x003B3900. Address-derived method
// name: no caller recovered a source identifier.

class AsciiString { public: unsigned short *m_data; };

typedef int Int;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_bfmeHead[0x8E];
	Bool m_flag8E;
	char m_pad8F[0x94 - 0x8F];
	AsciiString m_at94;
};

extern GlobalData *TheWritableGlobalData;

class GameLogic
{
public:
	void invoke(void);
};

extern GameLogic *TheGameLogic;

class Glo012F1028Sub
{
public:
	void consume(AsciiString *key);
	void refresh003CAD90(void);
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	Glo012F1028Sub *m_bfmeSub;
};

// Retail .data 0x012F1028 is EA's TheLivingWorldLogic
// (game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp:35,
// data_rows.csv ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A).  The
// Glo012F1028 spelling here was the old address-derived pin; only this
// reference moves to the defining name, and the local Glo012F1028Type view
// still describes the +0x28 sub-object this body reads.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Glo012F1024Entry
{
public:
	void stepFlag(void);
	char m_head[0x1C];
	unsigned char m_flag;
	char m_tail[0x03];
};

class BfmeEntryVector
{
public:
	Glo012F1024Entry *m_bfmeStart;
	Glo012F1024Entry *m_bfmeFinish;
};

class Glo012F1024Type
{
public:
	void setCampaign(AsciiString *key);
	int lookup(AsciiString *key);

private:
	char m_pad00[0x0C];
	Int m_bfmeIndex;
	BfmeEntryVector m_bfmeEntries;
	char m_pad18[0x1C - 0x18];
	unsigned char m_at1C;
};

// ?setCampaign@Glo012F1024Type@@QAEXPAVAsciiString@@@Z
// The four calls this body makes are retail ILT thunks (VA 0x00045B88,
// 0x0003B417, 0x0000577C, 0x0001FB18), whose ledger owners are the
// ?j_XXXXXXXX@@YAXXZ gen-thunks, so each is reached through a member-call
// cast exactly as GiantBirdGuardReturnState_update.cpp does.
extern void j_00045b88();
extern void j_0003b417();
extern void j_0000577c();
extern void j_0001fb18();

typedef void (Glo012F1028Sub::*ConsumeCall)(AsciiString *);
typedef void (GameLogic::*InvokeCall)();
typedef int (Glo012F1024Type::*LookupCall)(AsciiString *);
typedef void (Glo012F1024Entry::*StepFlagCall)();

void Glo012F1024Type::setCampaign(AsciiString *key)
{
	Glo012F1028Sub *sub = ((Glo012F1028Type *)TheLivingWorldLogic)->m_bfmeSub;
	if (sub != 0)
	{
		union
		{
			void *asVoid;
			ConsumeCall asMember;
		} consumeCast;
		consumeCast.asVoid = (void *)j_00045b88;
		(sub->*consumeCast.asMember)(key);
		sub->refresh003CAD90();
	}

	union
	{
		void *asVoid;
		InvokeCall asMember;
	} invokeCast;
	invokeCast.asVoid = (void *)j_0003b417;
	(TheGameLogic->*invokeCast.asMember)();

	if (TheWritableGlobalData->m_flag8E
		|| (TheWritableGlobalData->m_at94.m_data != 0 && TheWritableGlobalData->m_at94.m_data[2] != 0))
	{
		union
		{
			void *asVoid;
			LookupCall asMember;
		} lookupCast;
		lookupCast.asVoid = (void *)j_0000577c;
		int n = (this->*lookupCast.asMember)(key);
		m_bfmeIndex = n;
		if (n != -1)
		{
			Glo012F1024Entry *start = m_bfmeEntries.m_bfmeStart;
			m_at1C = start[n].m_flag;
			union
			{
				void *asVoid;
				StepFlagCall asMember;
			} stepFlagCast;
			stepFlagCast.asVoid = (void *)j_0001fb18;
			(start[n].*stepFlagCast.asMember)();
		}
		else
			m_at1C = 0;
	}
}
