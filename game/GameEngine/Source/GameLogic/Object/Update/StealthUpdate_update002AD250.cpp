// ?update002AD250@StealthUpdate@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc
//
// StealthUpdate::update002AD250, retail RVA 0x002AD250 (238 bytes).
// The ILT at 0x000272AF and the matched AIGroup::groupStealthIdle caller
// establish this as a StealthUpdate member helper.  The neutral RVA-derived
// method name is retained until a stronger retail symbol is recovered.
// Model-condition bits 248 (cleared) and 242 (set) live in Object's 320-bit
// array at +0x110 (word 7, +0x12C).  The flags' test() returns the masked WORD,
// not a bool: that keeps retail's mask in a register for the test and the set
// (docs/shape_levers.md, model-condition bit masks).  setDisabledUntil is
// called on a fresh getObject() read, as retail reloads [this+8].

typedef unsigned char Bool;
#include "../../../../Include/Common/ScalarTypes/UnsignedInt.h"

enum DisabledType
{
	DisabledTypeStealth = 3
};

class Object
{
public:
	void clearModelConditionState(int condition);
	void notifyModelConditionChanged();
	void setDisabledUntil(DisabledType type, UnsignedInt frame);

	struct ModelConditionFlags
	{
		UnsignedInt test(int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
		void set(int i) { m_bits[i >> 5] |= (1u << (i & 31)); }
		void clear(int i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }
		UnsignedInt m_bits[10];
	};

	void bfmeSetModelConditionState(int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			notifyModelConditionChanged();
		}
	}
	unsigned char m_pad00[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *first, void *second);
};

class BfmeObjE10
{
public:
	void actionA(int action);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class StealthUpdateModuleData
{
private:
	unsigned char m_pad00[0x310];

public:
	UnsignedInt m_stealthDelay;
	UnsignedInt m_detectionDelay;
	UnsignedInt m_enableState;
	UnsignedInt m_disableState;
	UnsignedInt m_blackMarketCheckFrames;
};

class UpdateModule
{
public:
	virtual void unused() = 0;

protected:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class StealthUpdate : public UpdateModule
{
protected:
	const StealthUpdateModuleData *getStealthUpdateModuleData() const
	{
		return (const StealthUpdateModuleData *)m_moduleData;
	}

	Object *getObject()
	{
		return m_object;
	}

public:
	void update002AD250();

private:
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	Bool m_enabled;
	Bool m_xferRestoreDisguise;
};

// ?update002AD250@StealthUpdate@@QAEXXZ
void StealthUpdate::update002AD250()
{
	Object *object = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	UnsignedInt now = TheGameLogic->m_frame;

	if (!data->m_enableState && !data->m_blackMarketCheckFrames)
		return;
	if (!m_xferRestoreDisguise)
	{
		if (now < m_nextBlackMarketCheckFrame)
			return;

		m_stealthAllowedFrame = data->m_stealthDelay + now;
		m_detectionExpiresFrame = 0;
		object->clearModelConditionState(0x10);

		if (object->m_modelConditionFlags.test(248))
		{
			object->m_modelConditionFlags.clear(248);
			object->notifyModelConditionChanged();
		}
		object->bfmeSetModelConditionState(242);

		((BfmeItemRY *)object)->bfmeDoRY(
			(void *)0xF9, (void *)data->m_enableState);
		getObject()->setDisabledUntil(DisabledTypeStealth, m_stealthAllowedFrame);
		((BfmeObjE10 *)object)->actionA(0x1C);
		m_xferRestoreDisguise = 1;
		return;
	}

	((BfmeItemRY *)object)->bfmeDoRY(
		(void *)0xFA, (void *)data->m_disableState);
	m_detectionExpiresFrame = data->m_detectionDelay + now;
}
