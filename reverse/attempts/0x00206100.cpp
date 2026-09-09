// ?bfmeGetNB@BfmeThingNB@@QAEXPAUBfmeVecNB@@H@Z
// partial score=0.84 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc-
// Open-BFME converts the 61-byte BFME triple copy at retail 0x00206100.
// The index selects a vector entry at +0x24 or the fallback record at +8.

struct BfmeVecNB
{
	int first;
	int second;
	int third;
};

typedef BfmeVecNB BfmeTripleNB;

class BfmeEntryNB
{
public:
	BfmeTripleNB &tripleValue() { return triple; }

	char padding[0x14];
	BfmeTripleNB triple;
};

class BfmeFallbackNB
{
public:
	BfmeTripleNB &tripleValue() { return triple; }

	char padding[0x38];
	BfmeTripleNB triple;
};

class BfmeVectorNB
{
public:
	int size() const { return end - begin; }
	BfmeEntryNB &operator[](int index) const { return *begin[index]; }

	BfmeEntryNB **begin;
	BfmeEntryNB **end;
};

class BfmeThingNB
{
public:
	void bfmeGetNB(BfmeVecNB *out, int index);

private:
	char padding0[8];
	BfmeFallbackNB *fallback;
	char padding0c[0x18];
	BfmeVectorNB values;
};

// ?bfmeGetNB@BfmeThingNB@@QAEXPAUBfmeVecNB@@H@Z
void BfmeThingNB::bfmeGetNB(BfmeVecNB *out, int index)
{
	BfmeVecNB *destination = out;
	BfmeVecNB *source =
		(index >= 0 && (unsigned int)index < (unsigned int)values.size())
		? &values[index].tripleValue()
		: &fallback->tripleValue();
	destination->first = source->first;
	destination->second = source->second;
	destination->third = source->third;
}
