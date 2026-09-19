// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef float Real;

struct DamageInfo
{
	unsigned char m_unmodelled_00[0x08];
	Int m_sourceObject;
	unsigned char m_unmodelled_0c[0x04];
	Int m_damageType;
	unsigned char m_unmodelled_14[0x08];
	Real m_amount;
};

class BodyModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getHealth() = 0;
};

class Object
{
public:
	unsigned char m_unmodelled_00[0x200];
	BodyModule *m_body;
};

class EvacuateDamageModuleData
{
public:
	unsigned char m_unmodelled_00[0x0c];
	Int m_damageType;
	Real m_evacuationScale;
};

class GameLogic
{
public:
	unsigned char m_unmodelled_00[0x3c];
	Int m_frame;
	Object *findObjectByID(Int id);
};

struct EvacuationRecord
{
	Real m_amount;
	Int m_frame;
};

class Gen_00250F50
{
public:
	Real bfmeSum();
};

class BfmeThingFDD
{
public:
	void bfmeGoFDD(void *object);
};

class EvacuateDamage
{
public:
	virtual void onDamage(DamageInfo *damageInfo);

	private:
	EvacuateDamageModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0x08];
	_STL::list<EvacuationRecord> m_pendingEvacuations;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

// ?onDamage@EvacuateDamage@@UAEXPAUDamageInfo@@@Z
void EvacuateDamage::onDamage(DamageInfo *damageInfo)
{
	if (damageInfo == 0)
		return;

	Int damageType = damageInfo->m_damageType;
	EvacuateDamageModuleData *moduleData = m_moduleData;
	if (moduleData->m_damageType != damageType)
		return;

	if (m_object->m_body == 0)
		return;

	EvacuationRecord record;
	record.m_amount = damageInfo->m_amount;
	record.m_frame = TheGameLogic->m_frame;
	m_pendingEvacuations.push_back(record);

	Real health = m_object->m_body->getHealth();
	if (reinterpret_cast<Gen_00250F50 *>(this)->bfmeSum() >=
		health * moduleData->m_evacuationScale)
	{
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceObject);
		if (source != 0)
			reinterpret_cast<BfmeThingFDD *>(this)->bfmeGoFDD(source);
	}
}
