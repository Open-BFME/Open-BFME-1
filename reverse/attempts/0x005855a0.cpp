// ?cachedPair@Rva005855A0Owner@@QAEXXZ
// partial score=0.2814 date=2026-09-24
// ?cachedPair@Rva005855A0Owner@@QAEXXZ
// Open-BFME5: retail RVA 0x005855A0, 167 bytes.
// The address-qualified owner is retained because no evidence identifies its
// original class or method.  Retail calls the matched fallback, ESM runner,
// and bfmeGo1077C callback, then caches the returned integer pair.

// cl: /DNDEBUG /DWIN32 /MD /EHsc

struct Rva005855A0Pair
{
	int first;
	int second;
};

class Rva003C9470Key
{
};

struct Rva003C9470Output
{
	union { float x; unsigned int rawX; };
	union { float y; unsigned int rawY; };
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);
};

class Glo012F1028Type
{
	public:
	char pad00[0x28];
	Rva003C9470Owner *m_owner;
};

extern Glo012F1028Type *Glo012F1028;
void bfmeGo1077C(int, float, float);

class BfmePairESM
{
public:
	int first;
	int second;
};

class BfmeHostESM
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24(BfmePairESM *request,
		Rva005855A0Pair *result);
	char bfmeRunESM(int first, int second, void **out);
};

class Gen_00609320;
extern Gen_00609320 *g_bfmeStateDF;

class Rva005855A0Owner
{
public:
	void cachedPair();

private:
	char pad00[0x10];
	int m_cachedFirst;
	int m_cachedSecond;
};

void Rva005855A0Owner::cachedPair()
{
	Rva003C9470Output fallbackPair;
	Glo012F1028->m_owner->fallback(
		(Rva003C9470Key *)(*(char **)((char *)this + 8) + 4), &fallbackPair);

	void *resultPointer;
	BfmePairESM request = { (int)fallbackPair.rawX, (int)fallbackPair.rawY };
	((BfmeHostESM *)g_bfmeStateDF)->bfmeRunESM(request.first, request.second, &resultPointer);

	Rva005855A0Pair result;
	((BfmeHostESM *)g_bfmeStateDF)->slot24(&request, &result);

	if (result.first != m_cachedFirst || result.second != m_cachedSecond)
	{
		bfmeGo1077C(0, (float)result.first, (float)result.second);
		m_cachedFirst = result.first;
		m_cachedSecond = result.second;
	}
}
