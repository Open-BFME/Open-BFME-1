// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: PreorderCreate::onBuildComplete, retail 0x00250000, 85 bytes.
// Zero Hour twin: getObject()->getControllingPlayer()->didPlayerPreorder() then
// set or clear MODELCONDITION_PREORDER. this is CreateModuleInterface at +0x10
// so getObject is [this-8]. PREORDER is bit 119 (dword +0x11C mask 0x800000).
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum ModelConditionFlagType
{
	MODELCONDITION_PREORDER = 119
};

template<int NUMBITS>
class BitFlags
{
public:
	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }
	void reset(Int idx) { m_bits.reset(idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<288> ModelConditionFlags;

class Player
{
public:
	Bool didPlayerPreorder() const { return m_didPreorder != 0; }

private:
	unsigned char m_unmodelled_000[0x297];
	unsigned char m_didPreorder;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged(void);

	void setModelConditionState(ModelConditionFlagType bit)
	{
		if (!m_conditionFlags.test(bit))
		{
			m_conditionFlags.set(bit);
			notifyModelConditionChanged();
		}
	}

	void clearModelConditionState(ModelConditionFlagType bit)
	{
		if (m_conditionFlags.test(bit))
		{
			m_conditionFlags.reset(bit);
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_conditionFlags;
};

class PreorderCreate
{
public:
	virtual void onBuildComplete();

	Object *getObject() const { return *(Object **)((char *)this - 8); }
};

// ?onBuildComplete@PreorderCreate@@UAEXXZ
void PreorderCreate::onBuildComplete()
{
	if (getObject()->getControllingPlayer()->didPlayerPreorder())
	{
		getObject()->setModelConditionState(MODELCONDITION_PREORDER);
	}
	else
	{
		getObject()->clearModelConditionState(MODELCONDITION_PREORDER);
	}
}
