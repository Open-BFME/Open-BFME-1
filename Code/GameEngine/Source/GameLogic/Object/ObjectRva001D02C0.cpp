// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA 0x001D02C0. The matched caller at 0x002FABE0 passes an Object
// through the 0x00049D73 thunk. The body queries the contained-item view and
// dispatches ObjectSMCHelper::setModelConditionState on selected members, or
// on this object when there is no view. The original member spelling remains
// unknown, so its name retains the retail address.

#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

class ObjectSMCHelper
{
public:
	void setModelConditionState(Int condition, UnsignedInt frames);
};

class BfmeRva493A0Object
{
public:
	char m_pad000[0x1dc];
	ObjectSMCHelper *m_smcHelper;
};

class BfmeContainListView
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0; virtual void slot56() = 0;
	virtual void slot57() = 0; virtual void slot58() = 0;
	virtual const _STL::list<BfmeRva493A0Object *> *getContainedItemsList() = 0;
};

class Rva001CF980Result : public BfmeContainListView {};

class Object
{
public:
	Rva001CF980Result *queryAt001CF980();
	void rva001D02C0(Int condition, Int frames, Real percent);

private:
	void **m_vtable;
	char m_pad004[0x1dc - 4];
	ObjectSMCHelper *m_smcHelper;
};

extern const Real g_bfmeK1253;
extern Int GetGameLogicRandomValue(Int low, Int high, char *file, Int line);

#pragma comment(linker, "/alternatename:?queryAt001CF980@Object@@QAEPAVRva001CF980Result@@XZ=?j_0002be77@@YAXXZ")
#pragma comment(linker, "/alternatename:?setModelConditionState@ObjectSMCHelper@@QAEXHI@Z=?j_00012b70@@YAXXZ")
#pragma comment(linker, "/alternatename:?GetGameLogicRandomValue@@YAHHHPADH@Z=?j_00001bae@@YAXXZ")

void Object::rva001D02C0(Int condition, Int frames, Real percent)
{
	Rva001CF980Result *result = queryAt001CF980();
	if (result != 0)
	{
		_STL::list<BfmeRva493A0Object *> objects(
			*result->getContainedItemsList());

		const _STL::list<BfmeRva493A0Object *> *source =
			result->getContainedItemsList();
		Int count = (Int)source->size();

		Int remaining = count;
		Int selected = (Int)((Real)count * percent + g_bfmeK1253);
		Int lower = selected;
		if (selected >= count)
			lower = count;
		if (lower < 1)
		{
			selected = 1;
			goto selected_count_ready;
		}
		if (selected >= count)
			selected = count;

	selected_count_ready:
		for (_STL::list<BfmeRva493A0Object *>::iterator it = objects.begin();
			it != objects.end(); ++it)
		{
			Int random = GetGameLogicRandomValue(1, remaining,
				(char *)0x0109EC20, 0xAA6);
			--remaining;
			if (random <= selected)
			{
				BfmeRva493A0Object *item = *it;
				--selected;
				item->m_smcHelper->setModelConditionState(condition,
					(UnsignedInt)frames);
			}
		}
		return;
	}

	m_smcHelper->setModelConditionState(condition, (UnsignedInt)frames);
}
