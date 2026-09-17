// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

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

enum DisabledType
{
	DISABLED_HELD = 3
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
float bfmeCosVNB(float value);
float bfmeSinVNB(float value);

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

class Object
{
public:
	UnsignedInt getID() const { return m_id; }
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void clearStatus(const ObjectStatusMaskType &status)
	{
		setStatus(status, false);
	}
	Bool clearDisabled(DisabledType type);

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
private:
	void startSlavedEffects(const Object *slaver);
	void stopSlavedEffects();

public:
	Object *getObject() const
	{
		return *(Object **)((unsigned char *)this + 8);
	}
	SlavedUpdateModuleData *getSlavedUpdateModuleData() const
	{
		return *(SlavedUpdateModuleData **)((unsigned char *)this + 4);
	}

private:
	unsigned int m_unmodelled_00;
	SlavedUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0x24 - 0x0c];
	UnsignedInt m_slaver;
	union
	{
		struct
		{
			Real m_offsetX;
			Real m_offsetY;
			Real m_offsetZ;
		};
		Coord3D m_guardPointOffset;
	};
};

void SlavedUpdate::startSlavedEffects(const Object *slaver)
{
	if (slaver == 0)
		return;

	m_slaver = slaver->getID();
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	Real direction = (Real)GetGameLogicRandomValue(
		0,
		6,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
		0x2db);
	m_offsetX = 0;
	m_offsetY = 0;
	m_offsetZ = 0;
	m_offsetX += data->m_guardMaxRange * bfmeCosVNB(direction);
	m_offsetY += data->m_guardMaxRange * bfmeSinVNB(direction);
	getObject()->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_UNSELECTABLE), true);
}

// ?stopSlavedEffects@SlavedUpdate@@AAEXXZ
void SlavedUpdate::stopSlavedEffects()
{
	m_slaver = 0;
	__asm { }
	m_guardPointOffset.zero();
	m_object->clearStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_UNSELECTABLE));
	m_object->clearDisabled(DISABLED_HELD);
}
