// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Igame/GameEngine/Source /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/LogicRandomValue.h"
#include "Common/BitFlags.h"

class BfmeConditionFlags
{
	public:
	unsigned int m_bits[10];
};

struct BfmeConditionChoice
{
	BfmeConditionFlags m_flags;
	int m_bfmeValue;
	int m_bfmeUnused;
};

// Retail ILTs 0x000095ED and 0x0001E402 reach these Object members.
// Keep the local mask storage, but use the ledger owner's BitFlags signature.
#define OBJECT_TU_MEMBERS \
	void clearAndSetModelConditionFlags(const BitFlags<320> &, const BitFlags<320> &); \
	void setDisabled(DisabledType);
#include "../object.h"

struct BfmeConditionChoiceOwner
{
	char m_bfmeFields[8];
	BfmeConditionChoice *m_bfmeBegin;
	BfmeConditionChoice *m_bfmeEnd;
};

// Retail ILT 0x000157DA reaches the matched UpdateModule wake-frame helper.
class Rva0028D8F0WakeAccess : public UpdateModule
{
public:
	__forceinline void wake(Object *object, int delay)
	{
		setWakeFrame(object, (UpdateSleepTime)delay);
	}
};

class Gen_0028D8F0
{
public:
	void bfmeSelectCondition(void);

private:
	char m_bfmeFields[4];
	BfmeConditionChoiceOwner *m_bfmeOwner;
	Object *m_bfmeObject;
	char m_bfme0C[0x14];
	unsigned char m_bfmeActive;
	unsigned char m_bfmeAlternate;
};

// ?bfmeSelectCondition@Gen_0028D8F0@@QAEXXZ
void Gen_0028D8F0::bfmeSelectCondition(void)
{
	Object *object = m_bfmeObject;
	BfmeConditionChoiceOwner *owner = m_bfmeOwner;
	int count = owner->m_bfmeEnd - owner->m_bfmeBegin;
	if (count < 1)
		return;

	bool alternate = GetGameLogicRandomValue(0, count - 1,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\DetachableRiderUpdate.cpp", 276) != 0;
	BfmeConditionFlags clear = {};
	m_bfmeAlternate = alternate;
	object->clearAndSetModelConditionFlags(
		reinterpret_cast<const BitFlags<320> &>(clear),
		reinterpret_cast<const BitFlags<320> &>(owner->m_bfmeBegin[alternate].m_flags));
	object->setDisabled((DisabledType)4);
	m_bfmeActive = 1;
	((Rva0028D8F0WakeAccess *)this)->wake(
		object, owner->m_bfmeBegin[m_bfmeAlternate].m_bfmeValue);
}
