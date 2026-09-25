// cl: /DNDEBUG /MD /EHsc
// BannerCarrierUpdate::update, retail 0x00285300 (313 bytes).
//
// Identity: slot 0 of the update-interface table 0x010BBAB0 (ILT 0x0001A762),
// which the BannerCarrierUpdate constructor at 0x00283330 installs at +0x10.
// The interface sits at owner+0x10, so the module data and object are
// this-0x0C and this-0x08 (the layout LargeGroupAudioUpdate_update.cpp also
// models). Module-data offsets +0x08/+0x0C/+0x38 are corroborated by the
// landed module-data constructor and destructors; their meaning is not, so
// they keep offset names. Object members come from object.h.
//
// Shape: the three entry guards are ONE condition. Written as three separate
// `return`s the body compiles to the same control flow, but the module-data
// pointer then has enough uses that VC7.1 homes it in EDI ahead of the AI
// pointer; with one return it lands in EBX and the AI pointer and the frame
// temporary share EDI, as in retail. The out-parameter lives in its own block
// so its zero store is scheduled after the m_containedBy test, as in retail.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_00[0x3C];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// Pinned on retail ILT 0x0003AB20; its body at 0x000D3F10 tests one bit of
// the array at this+0x110, and the caller tests AL.
class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

// Receiver is Object::m_ai; same callee pin and +0x31E flag
// HordeContainTryScheduleReformation.cpp uses.
class AIUpdateInterface
{
public:
	Bool bfmeBlocksFormationRefresh();			// body 0x00278830, ILT 0x00044774

	unsigned char m_unmodelled_000[0x31E];
	Bool m_flag31E;						// +0x31E
};

// Body 0x0028F480 (ILT 0x00024357), called on Object+0x1F8.
class Gen_0028F480
{
public:
	Bool bfmeTest() const;
};

// Body 0x001BE390 (ILT 0x00023727), called on Object::m_containedBy.
class Rva001BE390
{
public:
	Int get();
};

// Object returned by slot +0x68 of the contain module; only slot +0x8C is used.
class Rva00285300ContainResult
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7C();
	virtual void s80(); virtual void s84(); virtual void s88();
	virtual Bool rva00285300Slot8C(Int *out, UnsignedInt value);	// +0x8C
};

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64();
	virtual Rva00285300ContainResult *rva00285300Slot68();		// +0x68
};

#define OBJECT_TU_MEMBERS \
	Object *bfmeResolveMeleeTarget(Int flags); /* ILT 0x0000FAA6 */ \
	Bool test(UnsignedInt bit) const \
	{ \
		return ((const BFMESelectionStatusBits *)this)->test(bit); \
	} \
	Gen_0028F480 *rva00285300Field1F8() const \
	{ \
		return *(Gen_0028F480 *const *)&m_unmodelled1F4[4]; \
	} \
	Int rva001BE390Get() \
	{ \
		return ((Rva001BE390 *)this)->get(); \
	}
#include "../object.h"

class BannerCarrierUpdateModuleData
{
public:
	unsigned char m_unmodelled_00[0x08];
	UnsignedInt m_field8;					// +0x08
	UnsignedInt m_field0C;					// +0x0C
	unsigned char m_unmodelled_10[0x38 - 0x10];
	Bool m_field38;						// +0x38
};

// +0x00 of BannerCarrierUpdate; the two members it calls are pinned on the
// retail ILTs 0x0003767D and 0x000454D0.
class Rva00285300Base
{
public:
	virtual void s00();

	void j0003767d();
	void j000454d0(Object *object);

protected:
	const BannerCarrierUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};

class Rva00285300Iface0C
{
public:
	virtual void s00();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class BannerCarrierUpdate : public Rva00285300Base,
			    public Rva00285300Iface0C,
			    public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

// ?update@BannerCarrierUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime BannerCarrierUpdate::update()
{
	const BannerCarrierUpdateModuleData *moduleData = m_moduleData;
	Object *object = m_object;

	if (!object || (object->m_modelConditionFlags[2] & 0x10)
		|| (object->m_status[1] & 0x20000000))
		return (UpdateSleepTime)moduleData->m_field8;

	AIUpdateInterface *ai = object->m_ai;
	if (ai && (ai->bfmeBlocksFormationRefresh() || ai->m_flag31E))
		return (UpdateSleepTime)moduleData->m_field8;

	Object *resolved = object->bfmeResolveMeleeTarget(0);
	Gen_0028F480 *field1F8 = resolved ? resolved->rva00285300Field1F8()
		: object->rva00285300Field1F8();
	if (field1F8 && field1F8->bfmeTest())
		return (UpdateSleepTime)moduleData->m_field8;

	if (moduleData->m_field38)
	{
		j0003767d();
		return (UpdateSleepTime)moduleData->m_field8;
	}

	if (object->test(0x25) || object->test(0x3c))
		return (UpdateSleepTime)moduleData->m_field8;

	if (object->m_containedBy)
	{
		UnsignedInt frame = TheGameLogic->m_frame;
		if ((UnsignedInt)object->m_containedBy->rva001BE390Get() > frame - moduleData->m_field0C)
			return (UpdateSleepTime)moduleData->m_field8;
	}

	{
		Int out = 0;
		if (object->m_containedBy && object->m_containedBy->bfmeResolveMeleeTarget(0))
		{
			Object *resolvedContainer = object->m_containedBy->bfmeResolveMeleeTarget(0);
			if (resolvedContainer->m_contain->rva00285300Slot68()->rva00285300Slot8C(&out, moduleData->m_field0C))
				return (UpdateSleepTime)moduleData->m_field8;
		}
	}

	j000454d0(object);
	return (UpdateSleepTime)moduleData->m_field8;
}
