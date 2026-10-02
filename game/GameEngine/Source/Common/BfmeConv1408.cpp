// Open-BFME5 conversions.

class BfmeBlockVKQ
{
public:
	char bfmeAnyVKQ(const BfmeBlockVKQ &other);
	int m_bfmeArr[10];
};

typedef bool Bool;
typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

private:
	__forceinline Bool equals(const ModelConditionFlags *other) const
	{
		for (UnsignedInt i = 0; i < 10; ++i)
		{
			if (m_bits[i] != other->m_bits[i])
				return false;
		}
		return true;
	}
	UnsignedInt m_bits[10];
};

class BfmeThingVKQ
{
public:
	char bfmeTestVKQ(BfmeBlockVKQ &f);
	int m_bfme00;
	BfmeBlockVKQ m_bfme04;
	BfmeBlockVKQ m_bfme2c;
};

char BfmeThingVKQ::bfmeTestVKQ(BfmeBlockVKQ &f)
{
	if (f.bfmeAnyVKQ(m_bfme2c))
		return false;
	BfmeBlockVKQ tmp = f;
	for (int i = 0; i < 10; ++i)
		tmp.m_bfmeArr[i] &= m_bfme04.m_bfmeArr[i];
	return !(*(const ModelConditionFlags *)&m_bfme04 !=
		*(const ModelConditionFlags *)&tmp);
}
