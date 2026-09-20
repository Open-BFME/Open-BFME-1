// ?parseFactionDecalEntry@Rva003760C0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.82 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: carved EH-framed body at retail 0x003760C0 (312 B). No named
// caller/registration is proven, but the evidence lines up with
// CastleBehaviorModuleData's obsolete "FactionDecal" INI field:
//   - reverse/field_names.csv pins FieldParse table 0x00CEA0B0 (already
//     identified as CastleBehaviorModuleData's table by its other rows:
//     CastleToUnpackForFaction, FilterValidOwnedEntries, PreBuiltList, ...)
//     with "FactionDecal" at offset 0x60.
//   - This body reads the vector at instance+0x60 (add ecx,0x60 before the
//     push_back call at 0x00375EA0, the matched
//     vector<Gen_t_00375ea0_p12cd>::push_back -- a 12-byte element, exactly
//     two RetailLayoutString (4 B each) plus a Real).
//   - The unconditional (debugReportingEnabled-gated) warning it logs on
//     every call is the retail string at VA 0x010E9C68: "A CastleBehavior
//     entry calls for a FactionDecal.\n This is an obsolete feature, which
//     will be removed soon. \nYou should expect bad results. \nPlease use an
//     object with W3DFloorDraw, instead. -MLo", passed as severity 2.
//   - CastleBehavior::getFactionDecal (0x0036F2D0, reverse/re_attempts.log)
//     independently reads that same instance+0x60 vector of 12-byte records
//     (two AsciiStrings and a Real), confirming the element shape.
// Address-derived owner/function names; the identity is evidence-backed but
// not caller-proven.

typedef float Real;

extern "C" unsigned int __cdecl strlen(const char *s);
#pragma intrinsic(strlen)

extern bool __cdecl _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set(const char *s, int n);

private:
	void releaseBuffer(void);
	void *m_data;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);

	static Real scanReal(const char *token);
};

struct Rva003760C0Entry
{
	RetailLayoutString m_name1;
	RetailLayoutString m_name2;
	Real m_value;
};

class Rva003760C0Vector
{
public:
	void push_back(const Rva003760C0Entry &value);
};

struct Rva003760C0Owner
{
	char m_unreconstructed[0x60];
	Rva003760C0Vector m_entries;
};

class Rva003760C0
{
public:
	static void parseFactionDecalEntry(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFactionDecalEntry@Rva003760C0@@SAXPAVINI@@PAX1PBX@Z
void Rva003760C0::parseFactionDecalEntry(INI *ini, void *instance, void *, const void *)
{
	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0);
		log->slot38((const char *)0x010E9C68)->slot4C(2);
	}

	Rva003760C0Entry entry;

	const char *token1 = ini->getNextTokenOrNull();
	if (token1 != 0)
	{
		entry.m_name1.set(token1, token1 ? (int)strlen(token1) : 0);

		const char *token2 = ini->getNextTokenOrNull();
		if (token2 != 0)
		{
			entry.m_name2.set(token2, token2 ? (int)strlen(token2) : 0);

			const char *token3 = ini->getNextTokenOrNull();
			if (token3 != 0)
			{
				entry.m_value = INI::scanReal(token3);
				((Rva003760C0Owner *)instance)->m_entries.push_back(entry);
			}
		}
	}
}
