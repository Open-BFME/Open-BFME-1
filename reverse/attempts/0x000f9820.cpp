// ?d_000f9820@@YAXXZ
// partial score=0.97 date=2026-09-06
struct Rva000F9820Record
{
	char pad00[0x30];
	int value30;
	int value34;
};

class BfmeElemVLH
{
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int index);
	int value00;
	Rva000F9820Record *begin;
	Rva000F9820Record *end;
	int value0c;
	int value10;
};

class Rva000F9270FactoryLookup
{
public:
	void *evaluate(void *argument);
};

class AsciiStringBN
{
};

class BfmeOtherBN
{
public:
	void *bfmeLookupBN(const AsciiStringBN &record);
};

class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

struct BfmeGameLogic
{
	char pad00[0x3c];
	int frame;
};

extern BfmeOtherBN *g_bfmeOtherBN;

class Rva000F9820Owner : public BfmeVecVLH
{
public:
	float getValue(int divisor, int *out);
};

float Rva000F9820Owner::getValue(int divisor, int *out)
{
	Rva000F9820Record *record;
	void *key;
	BfmeUseB980 *product;
	int value;

	record = (Rva000F9820Record *)bfmeAtVLH(divisor);
	if (record)
	{
		if (record->value30 == -1)
		{
			if (out)
				*out = (int)((Rva000F9270FactoryLookup *)record)->evaluate((void *)value10);
			return *(const float *)0x01075334;
		}

		key = (void *)value10;
		product = (BfmeUseB980 *)g_bfmeOtherBN->bfmeLookupBN(*reinterpret_cast<const AsciiStringBN *>(record));
		if (product)
		{
			value = (int)product->bfmeApply980B((int)key, record->value34);
			if (value > 0)
			{
				BfmeGameLogic *logic = *(BfmeGameLogic **)0x012F0898;
				float result = (float)(unsigned int)logic->frame;
				float numerator = result - (float)record->value30;
				return numerator / value;
			}
		}
	}
	return *(const float *)0x01075350;
}
