// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME: Object selection predicate at retail RVA 0x001C9980.

class BfmeThingZK;

class BfmeInnerZK
{
public:
	BfmeThingZK *bfmeResolveZK(void);
};

class BfmeThingZK
{
public:
	int m_bfmeSpareZK;
	BfmeInnerZK *m_bfmeInnerZK;
	unsigned char m_bfmeGapZK[0xc0];
	char m_bfmeStateZK;
};

class BfmeActorZK
{
public:
	bool bfmeCanZK(int what);

	unsigned char m_bfmeHeadZK[0x90];
	unsigned char m_bfmeFlagsZK;
};

struct Rva00367E30Logic
{
	BfmeActorZK *bfmeFindZK(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerZK
{
public:
	char bfmeCheckZK(void);
};

class Object
{
public:
	bool queryRva001C9980(void);

private:
	__forceinline int queryRva001C9980Tail(void);

	int m_bfmeSpareZK;
	BfmeThingZK *m_bfmeThingZK;
	unsigned char m_bfmeGapZK[0x70];
	void *m_bfmeKeyZK;
};

__forceinline int Object::queryRva001C9980Tail(void)
{
	if (((BfmeOwnerZK *)this)->bfmeCheckZK())
	{
		BfmeThingZK *thing = m_bfmeThingZK;

		if (thing && thing->m_bfmeInnerZK)
			thing = thing->m_bfmeInnerZK->bfmeResolveZK();

		if (!(thing->m_bfmeStateZK & 0x80))
			return 1;
	}

	return 0;
}

// ?queryRva001C9980@Object@@QAE_NXZ
bool Object::queryRva001C9980(void)
{
	void *key = m_bfmeKeyZK;

	if (key)
	{
		BfmeActorZK *actor = TheBfmeGameLogic->bfmeFindZK(key);

		if (actor && actor->bfmeCanZK(0x6c) && (actor->m_bfmeFlagsZK & 8))
			return false;
	}

	// The inlined helper has an integer result, while this public query is a
	// byte-returning predicate. Keeping both views preserves the retail ABI's
	// wide success/failure tail without changing the logical boolean value.
	union QueryResult
	{
		int wide;
		bool narrow;
	};
	QueryResult result;
	result.wide = queryRva001C9980Tail();
	return result.narrow;
}
