// ?bfmeClearModelConditions@AIUpdateInterface@@QAEXXZ
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x002796C0: AIUpdateInterface helper that builds an 8-bit
// ModelConditionFlags mask and clearAndSetModelConditionFlags it against
// an empty set.

typedef int Int;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType k, Int a, Int b, Int c, Int d, Int e, Int f, Int g, Int h);

	__forceinline BitFlags()
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0;
		m_bits[4] = 0;
		m_bits[5] = 0;
		m_bits[6] = 0;
		m_bits[7] = 0;
		m_bits[8] = 0;
		m_bits[9] = 0;
	}

	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;

class Object
{
public:
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clr,
		const ModelConditionFlags &set);
};

class AIUpdateInterface
{
public:
	void bfmeClearModelConditions();

	unsigned char m_unmodelled_00[8];
	Object *m_object;
};

void AIUpdateInterface::bfmeClearModelConditions()
{
	Object *obj = m_object;
	if (!obj)
		return;

	ModelConditionFlags clr(ModelConditionFlags::kInit,
		0x3C, 0x7D, 0x7E, 0x81, 0x82, 0x7F, 0x80, 0x93);
	ModelConditionFlags set;
	obj->clearAndSetModelConditionFlags(clr, set);
}
