// ?updateAt00265510@RousingSpeechUpdate@@QAEXXZ
// partial score=0.24 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <list>
#include <vector>
#include <hash_map>
#include <bitset>
#include "ascii_string.h"
#include "Common/GameType.h"

class RousingSpeechObject;

class RousingSpeechConditionBits
{
public:
	bool test(int bit) const { return m_bits.test(bit); }
	void set(int bit) { m_bits.set(bit); }
private:
	_STL::bitset<320> m_bits;
};

class RousingSpeechContain
{
public:
#define RS_SLOT(N) virtual void slot##N();
	RS_SLOT(00) RS_SLOT(01) RS_SLOT(02) RS_SLOT(03)
	RS_SLOT(04) RS_SLOT(05) RS_SLOT(06) RS_SLOT(07)
	RS_SLOT(08) RS_SLOT(09) RS_SLOT(10) RS_SLOT(11)
	RS_SLOT(12) RS_SLOT(13) RS_SLOT(14) RS_SLOT(15)
	RS_SLOT(16) RS_SLOT(17) RS_SLOT(18) RS_SLOT(19)
	RS_SLOT(20) RS_SLOT(21) RS_SLOT(22) RS_SLOT(23)
	RS_SLOT(24) RS_SLOT(25) RS_SLOT(26) RS_SLOT(27)
	RS_SLOT(28) RS_SLOT(29) RS_SLOT(30) RS_SLOT(31)
	RS_SLOT(32) RS_SLOT(33) RS_SLOT(34) RS_SLOT(35)
	RS_SLOT(36) RS_SLOT(37) RS_SLOT(38) RS_SLOT(39)
	RS_SLOT(40) RS_SLOT(41) RS_SLOT(42) RS_SLOT(43)
	RS_SLOT(44) RS_SLOT(45) RS_SLOT(46) RS_SLOT(47)
	RS_SLOT(48) RS_SLOT(49) RS_SLOT(50) RS_SLOT(51)
	RS_SLOT(52) RS_SLOT(53) RS_SLOT(54) RS_SLOT(55)
	RS_SLOT(56) RS_SLOT(57) RS_SLOT(58) RS_SLOT(59)
	RS_SLOT(60) RS_SLOT(61) RS_SLOT(62)
	virtual void forEachContained(void (__cdecl *)(RousingSpeechObject *, void *),
		void *, Bool);
#undef RS_SLOT
};

class RousingSpeechLeveling
{
public:
	Bool gainExpForLevel(Int, Bool, Bool);
};

class RousingSpeechObject
{
public:
	Bool applyAttributeModifier(const AsciiString &, Int);
	void notifyModelConditionChanged();

	unsigned char m_00_to_74[0x74];
	ObjectID m_id;
	unsigned char m_78_to_110[0x98];
	RousingSpeechConditionBits m_conditions;
	unsigned char m_138_to_1fc[0xc4];
	RousingSpeechContain *m_contain;
	unsigned char m_200_to_210[0x10];
	RousingSpeechLeveling *m_leveling;
	unsigned char m_214_to_360[0x14c];
	ObjectID m_rousingOwner;
};

class RousingSpeechFXList
{
public:
	Bool bfmeIsBlocked();
	void doFXObj(const RousingSpeechObject *,
		const RousingSpeechObject *) const;
};

typedef _STL::hash_map<int, RousingSpeechObject *,
	_STL::hash<int>, _STL::equal_to<int> > RousingSpeechObjectHash;

class RousingSpeechGameLogic
{
public:
	__forceinline RousingSpeechObject *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;
		RousingSpeechObjectHash::iterator it =
			m_objects.find(static_cast<int>(id));
		if (it == m_objects.end())
			return 0;
		return (*it).second;
	}

	unsigned char m_00_to_b0[0xb0];
	RousingSpeechObjectHash m_objects;
};

extern RousingSpeechGameLogic *TheBfmeGameLogic;
void __cdecl rousingContainedCallbackAt00264AF0(
	RousingSpeechObject *object, void *)
{
	if (object != 0 && object->m_leveling != 0)
		object->m_leveling->gainExpForLevel(1, true, false);
}

struct RousingSpeechUpdateData
{
	unsigned char m_00_to_264[0x264];
	RousingSpeechFXList *m_fxList;
	unsigned char m_268_to_270[8];
	std::vector<AsciiString> m_modifiers;
	Bool m_applySecondaryPass;
};

class RousingSpeechUpdate
{
public:
	void prepareAt002A9850();
	void collectTargetsAt00265150();
	void updateAt00265510();

	unsigned char m_00_to_04[4];
	RousingSpeechUpdateData *m_data;
	RousingSpeechObject *m_object;
	unsigned char m_0c_to_e8[0xdc];
	_STL::list<ObjectID> m_ids;
};

static __forceinline void setRousingCondition(
	RousingSpeechObject *object, int bit)
{
	if (!object->m_conditions.test(bit))
	{
		object->m_conditions.set(bit);
		object->notifyModelConditionChanged();
	}
}

void RousingSpeechUpdate::updateAt00265510()
{
	const RousingSpeechUpdateData *data = m_data;
	prepareAt002A9850();
	collectTargetsAt00265150();
	if (m_ids.empty())
		return;

	std::vector<AsciiString> modifiers(data->m_modifiers);
	RousingSpeechGameLogic *logic = TheBfmeGameLogic;
	for (std::vector<AsciiString>::const_iterator modifier = modifiers.begin();
		modifier != modifiers.end(); ++modifier)
	{
		for (_STL::list<ObjectID>::iterator id = m_ids.begin();
			id != m_ids.end(); ++id)
		{
			RousingSpeechObject *object =
				logic->findObjectByID(*id);
			if (object != 0)
			{
				object->applyAttributeModifier(*modifier, -1);
				setRousingCondition(object, 191);
				object->m_rousingOwner = m_object->m_id;
				RousingSpeechFXList *fx = data->m_fxList;
				if (fx != 0 && !fx->bfmeIsBlocked())
					fx->doFXObj(object, 0);
				logic = TheBfmeGameLogic;
			}
		}
	}

	if (data->m_applySecondaryPass)
	{
		for (_STL::list<ObjectID>::iterator id = m_ids.begin();
			id != m_ids.end(); ++id)
		{
			RousingSpeechObject *object =
				logic->findObjectByID(*id);
			if (object != 0)
			{
				object->m_leveling->gainExpForLevel(1, true, false);
				logic = TheBfmeGameLogic;
			}
			RousingSpeechContain *contain = object->m_contain;
			if (contain != 0)
			{
				contain->forEachContained(
					rousingContainedCallbackAt00264AF0, 0, true);
				logic = TheBfmeGameLogic;
			}
		}
	}
}
