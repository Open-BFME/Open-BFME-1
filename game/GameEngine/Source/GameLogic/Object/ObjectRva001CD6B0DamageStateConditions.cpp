// stlport
// ?rva001CD6B0@Object@@QAEXW4BodyDamageType@@H@Z, retail 0x001CD6B0 (585 bytes). Swaps the damage model conditions
// through a -1/3/4/5 table like Zero Hour's Drawable::reactToBodyDamageStateChange, then sets one of conditions 0x83..0x86 by the second argument.
// Owner name is address-derived; receiver is the Object that module callers read at this-8 (ILT 0x00043135).
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags() { }
	BitFlags(BogusInitType, Int idx1, Int idx2, Int idx3);
	BitFlags(BogusInitType, Int idx1, Int idx2, Int idx3, Int idx4);

	void set(Int i) { m_bits._Unchecked_set((size_t)i); }
	Bool test(Int i) const { return m_bits._Unchecked_test((size_t)i); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> ModelConditionFlags;
// The ILT 0x000095ED pin spells the clear-and-set parameters as BitFlags<320>; both are ten words.
typedef BitFlags<320> PinnedModelConditionFlags;

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

enum BodyDamageType
{
	BODY_PRISTINE = 0
};

extern void j_00039301();

class Drawable
{
public:
	void rva00417AE0(BodyDamageType newState);
};

typedef void (Drawable::*Rva00417AE0Call)(BodyDamageType);

class ObjectSMCHelper
{
public:
	void setModelConditionState(Int condition, UnsignedInt frames);
};

class GameLogic
{
public:
	Bool isLoadingMap() const { return m_loadingMap; }

	char m_pad000[0x69];
	Bool m_loadingMap;								// +0x069
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void clearAndSetModelConditionFlags(const PinnedModelConditionFlags &clr, const PinnedModelConditionFlags &set);
	void rva001CD6B0(BodyDamageType newState, Int variant);

	char m_pad000[0x80];
	Drawable *m_drawable;							// +0x080
	char m_pad084[0x110 - 0x84];
	ModelConditionFlags m_modelConditionFlags;		// +0x110
	char m_pad138[0x1dc - 0x138];
	ObjectSMCHelper *m_smcHelper;					// +0x1dc
};

static __forceinline void clearModelConditionFlagsInline(Object *object, const ModelConditionFlags &clr)
{
	ModelConditionFlags empty;
	object->clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(clr), (const PinnedModelConditionFlags &)(empty));
}

void Object::rva001CD6B0(BodyDamageType newState, Int variant)
{
	static const ModelConditionFlagType TheDamageMap[4] =
	{
		MODELCONDITION_INVALID,
		(ModelConditionFlagType)3,
		(ModelConditionFlagType)4,
		(ModelConditionFlagType)5,
	};

	// Retail reuses newDamage's stack slot for the later masks, so its lifetime ends here.
	{
		ModelConditionFlags newDamage;
		if (TheDamageMap[newState] != MODELCONDITION_INVALID)
			newDamage.set(TheDamageMap[newState]);

		clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(ModelConditionFlags(ModelConditionFlags::kInit, 3, 4, 5)), (const PinnedModelConditionFlags &)(newDamage));
	}

	if (!TheGameLogic->isLoadingMap() && m_drawable)
	{
		union
		{
			void (*freeFunction)();
			Rva00417AE0Call memberFunction;
		} ambient;
		ambient.freeFunction = j_00039301;
		(m_drawable->*ambient.memberFunction)(newState);
	}

	if (TheDamageMap[newState] == 5)
	{
		if (m_modelConditionFlags.test(0x44))
			m_smcHelper->setModelConditionState(0x12d, 0xf);
	}

	if (TheDamageMap[newState] != 5 && m_modelConditionFlags.test(4))
	{
		ModelConditionFlags selected;
		if (variant == 1)
		{
			selected.set(0x83);
			clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(ModelConditionFlags(ModelConditionFlags::kInit, 0x84, 0x85, 0x86)), (const PinnedModelConditionFlags &)(selected));
		}
		else if (variant == 2)
		{
			selected.set(0x84);
			clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(ModelConditionFlags(ModelConditionFlags::kInit, 0x83, 0x85, 0x86)), (const PinnedModelConditionFlags &)(selected));
		}
		else if (variant == 3)
		{
			selected.set(0x85);
			clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(ModelConditionFlags(ModelConditionFlags::kInit, 0x83, 0x84, 0x86)), (const PinnedModelConditionFlags &)(selected));
		}
		else if (variant == 4)
		{
			selected.set(0x86);
			clearAndSetModelConditionFlags((const PinnedModelConditionFlags &)(ModelConditionFlags(ModelConditionFlags::kInit, 0x83, 0x84, 0x85)), (const PinnedModelConditionFlags &)(selected));
		}
	}
	else
	{
		clearModelConditionFlagsInline(this, ModelConditionFlags(ModelConditionFlags::kInit, 0x83, 0x84, 0x85, 0x86));
	}
}

#pragma comment(linker, "/alternatename:?setModelConditionState@ObjectSMCHelper@@QAEXHI@Z=?j_00012b70@@YAXXZ")
