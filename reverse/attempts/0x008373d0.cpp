// ?bfmeCall2WB@@YAXPAX00000H@Z
// partial score=0.82 date=2026-09-10
void * __cdecl bfmeCall1WB(void *buffer, void *seventh, void *eighth, void *slot, void *sixth);
void __cdecl bfmeCall2WB(void *out, void *buffer, void *made, void *second, void *third, void *fourth, int zero);

class BfmeIter1016;

class BfmeR1016
{
public:
	BfmeR1016 &bfmeGo1016R(int value);

	BfmeIter1016 *m_bfmeIt;
	char m_bfmeOk;
};

struct BfmeWBTemp
{
	void *m_begin;
	void *m_end;
	char m_bfmePad[0x78];
};

class BfmeWBCallTarget
{
public:
	virtual void bfmeSlot0(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot1(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot2(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot3(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot4(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot5(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot6(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot7(void *, void *, BfmeWBTemp *);
	virtual void bfmeSlot8(void *, void *, BfmeWBTemp *);
	virtual void bfmeCallWB(void *buffer, void *made, BfmeWBTemp *result);
};

class BfmeWBFourth
{
public:
	char m_bfmePad[0x40];
	BfmeWBCallTarget *m_bfmeCallTarget;
};

struct BfmeWBResult
{
	void *m_bfmeIt;
	int m_bfmeOk;
};

void __cdecl bfmeCall2WB(void *out, void *buffer, void *made, void *second, void *third, void *fourth, int zero)
{
	BfmeWBResult result;
	BfmeWBTemp temp;
	register void *bufferValue = buffer;
	register void *madeValue = made;
	BfmeR1016 *resultPointer = (BfmeR1016 *)&result;

	((BfmeWBFourth *)fourth)->m_bfmeCallTarget->bfmeCallWB(bufferValue, madeValue, &temp);

	int count = (int)((char *)madeValue - (char *)bufferValue);
	count &= ~1;
	result.m_bfmeIt = second;
	result.m_bfmeOk = (long)third;

	unsigned short *value = (unsigned short *)temp.m_begin;
	while (count > 0)
	{
		resultPointer->bfmeGo1016R(*value);
		value++;
		--count;
	}

	*(BfmeWBResult *)out = result;
}

class BfmeOwnerWB
{
public:
	void *bfmeMakeWB(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh, void *eighth);
};

void *BfmeOwnerWB::bfmeMakeWB(void *out, void *second, void *third, void *fourth, void *fifth, void *sixth, void *seventh, void *eighth)
{
	char buffer[0x40];

	void *made = bfmeCall1WB(buffer, seventh, eighth, (char *)this + 0xc, sixth);

	bfmeCall2WB(out, buffer, made, second, third, fourth, 0);

	return out;
}
