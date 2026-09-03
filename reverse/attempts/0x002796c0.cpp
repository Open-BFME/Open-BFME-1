// ?bfmeClearModelConditions@AIUpdateInterface@@QAEXXZ
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

typedef int Int;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType k, Int a, Int b, Int c, Int d, Int e, Int f, Int g, Int h);

	BitFlags() : m_bits() {}

	_STL::bitset<NUMBITS> m_bits;
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
