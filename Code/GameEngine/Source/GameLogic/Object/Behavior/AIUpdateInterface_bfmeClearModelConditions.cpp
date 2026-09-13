// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

typedef int Int;

class BfmeC1166
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BfmeC1166(Int tag, unsigned int a, unsigned int b, unsigned int c,
		unsigned int d, unsigned int e, unsigned int f, unsigned int g,
		unsigned int h) throw();

	BfmeC1166() {}

	_STL::bitset<320> m_bits;
};

typedef BfmeC1166 ModelConditionFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clr,
		const ModelConditionFlags &set);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
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

	unsigned char clrStorage[sizeof(ModelConditionFlags)];
	ModelConditionFlags *clr = new (clrStorage) ModelConditionFlags(
		0,
		0x3C, 0x7D, 0x7E, 0x81, 0x82, 0x7F, 0x80, 0x93);
	ModelConditionFlags set;
	obj->clearAndSetModelConditionFlags(*clr, set);
}
