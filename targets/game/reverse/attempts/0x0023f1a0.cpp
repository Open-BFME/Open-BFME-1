// ?bfmeAfter@Gen_0022F900@@QAEXPAVObject@@PAX@Z
// partial score=0.78 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Gen_0022F900::bfmeAfter, retail 0x0023F1A0 (507 bytes).
//
// The entry is reached through ILT 0x00047EE7 from the landed gain-level
// caller.  Its this pointer is the HordeContain base subobject at +0x20;
// the base/view offsets and the member-index map are witnessed by the
// adjacent HordeContain conversions and constructor vtables.

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmeModelConditionFlags
{
	BfmeModelConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	UnsignedInt m_bits[3];
};

class Drawable;
class ExperienceTracker;
class Pathfinder;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Object : public BfmeVirtualSlots<10>
{
public:
	virtual Drawable *getDrawable(void) = 0;
	Int getID(void) const
	{
		return *reinterpret_cast<const Int *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0x74);
	}
};

class BfmeObjectStatusCallTarget
{
public:
	void apply(const BfmeModelConditionFlags &flags, Bool on);
};

class BfmeObjectProducerCallTarget
{
public:
	void setProducer(const Object *producer);
};

class BfmeObjectPositionCallTarget
{
public:
	void setPosition(const Coord3D *position);
};

class ExperienceTracker
{
public:
	void setExperienceSink(UnsignedInt id);
};

class BfmeContainingCallTarget
{
public:
	void bfmeDoBPC(Object *object, void *extra);
};

class BfmeMemberIndexNode
{
public:
	UnsignedByte m_pad00[0x14];
	Int m_index;
};

struct BfmeMemberIndexIterator
{
	BfmeMemberIndexNode *m_node;
};

class BfmeMemberIndexMap
{
public:
	BfmeMemberIndexIterator find(const Int &id);

	BfmeMemberIndexNode *m_header;
	UnsignedByte m_pad04[8];
};

struct BfmeHordeContainMemberIndexLayout
{
	UnsignedByte m_pad00[0x100];
	BfmeMemberIndexMap m_memberIndices;
};

class BfmeHordeContainBase : public BfmeVirtualSlots<30>
{
public:
	virtual void slot30(Int value) = 0;
	virtual void slot31(void *value) = 0;
};

class BfmeHordeContainViewBefore84 : public BfmeVirtualSlots<7>
{
public:
	virtual void slot7(Coord3D *position, Object *member, Int *scratch) = 0;
};

template <int N>
class BfmeViewSlotsAfter7 : public BfmeViewSlotsAfter7<N - 1>
{
public:
	virtual void unusedAfter7(char (*)[N]) = 0;
};

template <>
class BfmeViewSlotsAfter7<0> : public BfmeHordeContainViewBefore84
{
};

class BfmeHordeContainViewWith84 : public BfmeViewSlotsAfter7<76>
{
public:
	virtual Int slot84(Int value) = 0;
};

template <int N>
class BfmeViewSlotsAfter84 : public BfmeViewSlotsAfter84<N - 1>
{
public:
	virtual void unusedAfter84(char (*)[N]) = 0;
};

template <>
class BfmeViewSlotsAfter84<0> : public BfmeHordeContainViewWith84
{
};

class BfmeHordeContainView : public BfmeViewSlotsAfter84<4>
{
public:
	virtual Int slot89(void *container) = 0;
};

class BfmeD1044
{
public:
	void bfmeStep1044(Int orientation);
};

class Rva001BEC40DwordSlot
{
public:
	void set(Int value);
};

class BfmeHordeContainOwner
{
public:
	void bfmeApplyMemberFormationState(Object *member);
};

class AIUpdateInterface : public BfmeVirtualSlots<127>
{
public:
	virtual void slot127(Int value) = 0;
};

class Pathfinder
{
public:
	Int getLayer(const Coord3D *position);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	UnsignedByte m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

struct Rva003FD060TerrainLogic
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Real getLayerHeight(Real x, Real y, Int layer,
		void *normal, Bool clip) const = 0;
};

struct Rva006C9270GlobalData
{
	UnsignedByte m_pad00[0xa76];
	UnsignedByte m_flagA76;
};

struct BfmeModuleData
{
	UnsignedByte m_pad00[0x2cc];
	Int m_value2cc;
};

extern AI *TheAI;
extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern Rva006C9270GlobalData *TheWritableGlobalData;

extern void j_0000cb3f();
extern void j_0000d990();
extern void j_0000efa2();
extern void j_0001a95b();
extern void j_0001e9d4();
extern void j_0001f000();
extern void j_000307e7();
extern void j_000392ca();
extern void j_000399a5();
extern void j_0003a1a7();
extern void j_0003e7f7();
extern void j_000476f9();
extern void j_00013435();

class Rva00413FF0GuardedVCall
{
public:
	void forward(Int value);
};

class Rva004141A0GuardedVCall
{
public:
	void forward(Int first, Int second);
};

class Gen_0022F900
{
public:
	void bfmeAfter(Object *member, void *extra);
};

// ?bfmeAfter@Gen_0022F900@@QAEXPAVObject@@PAX@Z
void Gen_0022F900::bfmeAfter(Object *member, void *extra)
{
	BfmeModelConditionFlags status;
	Object *memberObject = member;
	BfmeHordeContainMemberIndexLayout *container =
		reinterpret_cast<BfmeHordeContainMemberIndexLayout *>(this);

	status.m_bits[1] |= 0x20;
	{
		typedef void (BfmeObjectStatusCallTarget::*ApplyStatusCall)(
			const BfmeModelConditionFlags &, Bool);
		union
		{
			void (*raw)(void);
			ApplyStatusCall typed;
		} call;
		call.raw = j_000307e7;
		(reinterpret_cast<BfmeObjectStatusCallTarget *>(memberObject)->*call.typed)(
			status, true);
	}

	{
		typedef void (BfmeContainingCallTarget::*OnContainingCall)(
			Object *, void *);
		union
		{
			void (*raw)(void);
			OnContainingCall typed;
		} call;
		call.raw = j_000476f9;
		(reinterpret_cast<BfmeContainingCallTarget *>(this)->*call.typed)(
			memberObject, extra);
	}

	{
		typedef void (BfmeObjectProducerCallTarget::*SetProducerCall)(const Object *);
		union
		{
			void (*raw)(void);
			SetProducerCall typed;
		} call;
		call.raw = j_0000d990;
		(reinterpret_cast<BfmeObjectProducerCallTarget *>(memberObject)->*call.typed)(
			*reinterpret_cast<Object **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x18));
	}

	{
		UnsignedInt ownerID = *reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<UnsignedByte *>(*reinterpret_cast<Object **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x18)) + 0x74);
		ExperienceTracker *tracker = *reinterpret_cast<ExperienceTracker **>(
			reinterpret_cast<UnsignedByte *>(memberObject) + 0x210);
		typedef void (ExperienceTracker::*SetExperienceSinkCall)(UnsignedInt);
		union
		{
			void (*raw)(void);
			SetExperienceSinkCall typed;
		} call;
		call.raw = j_0001e9d4;
		(tracker->*call.typed)(ownerID);
	}

	*reinterpret_cast<UnsignedByte *>(reinterpret_cast<UnsignedByte *>(this) + 0xc8) = 1;

	{
		BfmeMemberIndexIterator iterator =
			container->m_memberIndices.find(
			memberObject->getID());

		if (iterator.m_node != container->m_memberIndices.m_header)
			return;

		BfmeHordeContainBase *base = reinterpret_cast<BfmeHordeContainBase *>(
			reinterpret_cast<UnsignedByte *>(this) - 0x20);
		BfmeHordeContainView *view;
		if (*reinterpret_cast<UnsignedByte *>(
			reinterpret_cast<UnsignedByte *>(this) + 0x11c) == 0)
			base->slot30(1);
		base->slot31(view);
		view = reinterpret_cast<BfmeHordeContainView *>(
			reinterpret_cast<UnsignedByte *>(this) + 0xc4);

		Int scratch = 0;
		Coord3D position;
		view->slot7(&position, memberObject, &scratch);

		Pathfinder *pathfinder = TheAI->pathfinder();
		Int layer;
		{
			typedef Int (Pathfinder::*GetLayerCall)(const Coord3D *);
			union
			{
				void (*raw)(void);
				GetLayerCall typed;
			} call;
			call.raw = j_0001a95b;
			layer = (pathfinder->*call.typed)(reinterpret_cast<const Coord3D *>(
				reinterpret_cast<UnsignedByte *>(*reinterpret_cast<Object **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x18)) + 0x38));
		}

		pathfinder = TheAI->pathfinder();
		{
			typedef void (Pathfinder::*AdjustDestinationCall)(
			Object *, Coord3D *, Object *, Int);
			union
			{
				void (*raw)(void);
				AdjustDestinationCall typed;
			} call;
			call.raw = j_000392ca;
			(pathfinder->*call.typed)(memberObject, &position,
				*reinterpret_cast<Object **>(reinterpret_cast<UnsignedByte *>(this) - 0x18), 0);
		}

		position.z = TheTerrainLogic->getLayerHeight(
			position.x, position.y, layer, 0, true);

		{
			typedef void (BfmeObjectPositionCallTarget::*SetPositionCall)(const Coord3D *);
			union
			{
				void (*raw)(void);
				SetPositionCall typed;
			} call;
			call.raw = j_0003a1a7;
			(reinterpret_cast<BfmeObjectPositionCallTarget *>(memberObject)->*call.typed)(
				&position);
			(reinterpret_cast<BfmeObjectPositionCallTarget *>(memberObject)->*call.typed)(
				&position);
		}

		{
			typedef void (Rva001BEC40DwordSlot::*SetDwordCall)(Int);
			union
			{
				void (*raw)(void);
				SetDwordCall typed;
			} call;
			call.raw = j_0000cb3f;
			(reinterpret_cast<Rva001BEC40DwordSlot *>(memberObject)->*call.typed)(layer);
		}

		{
			Int orientation = *reinterpret_cast<Int *>(
				reinterpret_cast<UnsignedByte *>(*reinterpret_cast<Object **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x18)) + 0x44);
			typedef void (BfmeD1044::*SetOrientationCall)(Int);
			union
			{
				void (*raw)(void);
				SetOrientationCall typed;
			} call;
			call.raw = j_000399a5;
			(reinterpret_cast<BfmeD1044 *>(memberObject)->*call.typed)(orientation);
		}

		{
			typedef void (BfmeHordeContainOwner::*ApplyFormationCall)(Object *);
			union
			{
				void (*raw)(void);
				ApplyFormationCall typed;
			} call;
			call.raw = j_0000efa2;
			(reinterpret_cast<BfmeHordeContainOwner *>(base)->*call.typed)(memberObject);
		}

		BfmeModuleData *data = *reinterpret_cast<BfmeModuleData **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x1c);
		if (data != 0 && data->m_value2cc != -1)
		{
			AIUpdateInterface *ai = *reinterpret_cast<AIUpdateInterface **>(
				reinterpret_cast<UnsignedByte *>(memberObject) + 0x204);
			if (ai != 0)
				ai->slot127(data->m_value2cc);
		}

		Object *owner = *reinterpret_cast<Object **>(
				reinterpret_cast<UnsignedByte *>(this) - 0x18);
		if (owner != 0)
		{
			Drawable *drawable = owner->getDrawable();
			if (drawable != 0 && *reinterpret_cast<UnsignedByte *>(
				reinterpret_cast<UnsignedByte *>(drawable) + 0x3ac) != 0 &&
				TheWritableGlobalData->m_flagA76 != 0)
			{
				Int feedback;
				feedback = view->slot84(0);
				typedef void (Rva00413FF0GuardedVCall::*GuardedFeedbackCall)(Int);
				union
				{
					void (*raw)(void);
					GuardedFeedbackCall typed;
				} call;
				call.raw = j_00013435;
				(reinterpret_cast<Rva00413FF0GuardedVCall *>(drawable)->*
					call.typed)(feedback);
			}
		}
		else
		{
			Drawable *drawable = memberObject->getDrawable();
			if (drawable != 0)
			{
				Int feedback = view->slot89(this);
				typedef void (Rva004141A0GuardedVCall::*GuardedFeedbackCall)(Int, Int);
				union
				{
					void (*raw)(void);
					GuardedFeedbackCall typed;
				} call;
				call.raw = j_0003e7f7;
				(reinterpret_cast<Rva004141A0GuardedVCall *>(drawable)->*call.typed)(
					1, feedback);
			}
		}
	}
}
