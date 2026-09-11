// ?fill@Gen003C0350Found@@QAE_NPAX0@Z
// partial score=0.82 date=2026-09-11
// Open-BFME5: retail RVA 0x00619840, 146 bytes.
//
// The body is the fill method called by Rva003C0350::run at 0x003C0350.
// The caller supplies an encoded index and an eight-byte output pair.  The
// normal path copies the indexed pair; the negative/out-of-range path asks
// the Living World provider for a base pair and adds its two float offsets.

struct Gen003BC9C0Pair
{
	float m_x;
	float m_y;
};

class BfmePairGM
{
	public:
	float m_x;
	float m_y;
};

class Gen_003C7D50
{
public:
	bool bfmePairAt(int index, BfmePairGM *out) const;
};

class Gen003C9470Owner
{
public:
	void fill(void *source, Gen003BC9C0Pair *out);
};

class Glo012F1028Type
{
private:
	unsigned char m_pad00[0x28];

public:
	Gen003C9470Owner *m_provider;
};

extern Glo012F1028Type *Glo012F1028;

class Gen003C0350Found
{
public:
	bool fill(void *encodedIndex, void *output);

private:
	unsigned char m_pad00[4];
	unsigned char m_payload[0x40];
	BfmePairGM *m_begin;
	BfmePairGM *m_end;
};

bool Gen003C0350Found::fill(void *encodedIndex, void *output)
{
	int index = reinterpret_cast<int>(encodedIndex);
	Gen003C0350Found *self = this;
	BfmePairGM *result = (BfmePairGM *)output;

	if (index >= 0)
	{
		if ((unsigned int)index <
			(unsigned int)(self->m_end - self->m_begin))
		{
			BfmePairGM *element = self->m_begin + index;
			result->m_x = element->m_x;
			result->m_y = element->m_y;
			return true;
		}
	}

	Gen003C9470Owner *provider = Glo012F1028->m_provider;
	if (provider == 0)
		return false;

	if (!((Gen_003C7D50 *)provider)->bfmePairAt(index,
		(BfmePairGM *)result))
		return false;

	Gen003BC9C0Pair delta;
	provider->fill(m_payload, &delta);
	result->m_x += delta.m_x;
	result->m_y += delta.m_y;
	return true;
}
