// ?startSlavedEffects@SlavedUpdate@@QAEXPBVObject@@@Z
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// SlavedUpdate::startSlavedEffects, retail 0x002A4660 (Ghidra-split 12+134).
// Null slaver bails; else cache slaver id, random heading 0..6, offset =
// (cos,sin)*guardMaxRange, setStatus(UNSELECTABLE, true).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;
typedef float Real;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3
};

template <int Bits>
class BitFlags
{
public:
	enum InitType { kInit };

	BitFlags() {}

	BitFlags(InitType, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float bfmeCosVNB(float a);
float bfmeSinVNB(float a);

class Object
{
public:
	UnsignedInt getID() const { return m_id; }
	void setStatus(const ObjectStatusMaskType &status, Bool set);

private:
	unsigned char m_unmodelled[0x74];
	UnsignedInt m_id;
};

class SlavedUpdateModuleData
{
public:
	unsigned char m_unmodelled[8];
	Int m_guardMaxRange;
};

class SlavedUpdate
{
public:
	void startSlavedEffects(const Object *slaver);

private:
	unsigned int m_unmodelled_00;
	SlavedUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0x24 - 0x0c];
	UnsignedInt m_slaver;
	Real m_offsetX;
	Real m_offsetY;
	Real m_offsetZ;
};

// ?startSlavedEffects@SlavedUpdate@@AAEXPBVObject@@@Z
void SlavedUpdate::startSlavedEffects(const Object *slaver)
{
	if (slaver == 0)
		return;

	m_slaver = slaver->getID();
	Real dir = (Real)GetGameLogicRandomValue(
		0,
		6,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
		0x2db);
	m_offsetX = 0;
	m_offsetY = 0;
	m_offsetZ = 0;
	m_offsetX += bfmeCosVNB(dir) * m_moduleData->m_guardMaxRange;
	m_offsetY += bfmeSinVNB(dir) * m_moduleData->m_guardMaxRange;
	m_object->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_UNSELECTABLE), true);
}
