// cl: /DNDEBUG /MD /EHsc
// Retail 0x00287290, address-derived update body.  The concrete owner is not
// proven; the class and method retain the RVA rather than inventing one.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

class Object;

union Rva001C9380VictimArgument
{
	Object *object;
	Int experience;
	float gain;

};

union Rva001C9380Argument
{
	Bool allow;
	float multiplier;

};

#define OBJECT_TU_MEMBERS \
	void rva001c9380(Rva001C9380VictimArgument victim, Rva001C9380Argument allow); \
	void rva001CCB20ApplyContainedCondition(Int value);
#include "../object.h"

class BfmeObjAS : public Object
{
public:
	BfmeObjAS *bfmeParentAS(Int mode);
};

class Rva00287290Interface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual Int slot64(Int value);
};

class Rva00287290Self
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual Bool accepts(BfmeObjAS *candidate);

	void Rva00287290(BfmeObjAS *candidate);

	unsigned char m_pad004[8];
	UnsignedInt m_count;
};

typedef void (Object::*Rva001C9380UnionCall)(
	Rva001C9380VictimArgument, Rva001C9380Argument);
typedef void (Object::*Rva001C9380ScalarCall)(Int, Int);

void Rva00287290Self::Rva00287290(BfmeObjAS *candidate)
{
	BfmeObjAS *parent =
		*(BfmeObjAS **)((char *)this - 0x18);

	if (candidate == 0)
		return;

	BfmeObjAS *resolved = candidate->bfmeParentAS(0);
	if (resolved == 0)
		return;

	if (!accepts(candidate))
		return;

	if (++m_count == 1)
	{
		resolved->rva001CCB20ApplyContainedCondition(0x3f);
	}

	Rva001C9380UnionCall unionCall = &Object::rva001c9380;
	Rva001C9380ScalarCall scalarCall =
		reinterpret_cast<Rva001C9380ScalarCall>(unionCall);
	(parent->bfmeParentAS(0)->*scalarCall)((Int)candidate, 1);

	Rva00287290Interface *interfaceValue =
		(Rva00287290Interface *)resolved->m_contain;
	if (interfaceValue == 0)
		return;
	if (interfaceValue->slot64(0) != 1)
		return;

	slot01();
}
