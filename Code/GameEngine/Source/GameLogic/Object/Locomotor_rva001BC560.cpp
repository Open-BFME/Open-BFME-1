// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BC560 is the 210-byte BFME locomotor helper called by the
// appearance-2 branch of the typed dispatcher at 0x001BC820.  The first two
// calls are the established 1054 setup pair, and the third is the established
// 1282 movement finisher.  The tail is BFME's over-water model-condition
// synchronization, which is absent from the unchanged ZH helper.
// stlport

typedef bool Bool;
typedef int Int;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D() {}
	Coord3D(const Coord3D &other)
		: x(other.x), y(other.y), z(other.z) {}
};

class BfmeSubC1054
{
public:
	char m_pad000[4];
};

class BfmeD1054
{
public:
	void bfmeAdd1054(BfmeSubC1054 *item);
};

class BfmeC1054
{
public:
	void bfmeStep1054(BfmeD1054 *item, int value, int zero);
};

class BfmeQ1282
{
};

class BfmeA1282
{
public:
	void bfmeFinish1282(BfmeQ1282 *item, const Coord3D *goal,
		Real onPathDistToGoal, Real desiredSpeed);
};

template<int NUMBITS>
class BfmeBitFlags
{
public:
	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }
	void clear(Int idx) { m_bits.reset(idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BfmeBitFlags<288> BfmeModelConditionFlags;

enum BfmeModelConditionFlagType
{
	BFME_MODELCONDITION_OVER_WATER = 4
};

class TerrainLogic
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class BfmeObjectModelCondition
{
public:
	void notifyModelConditionChanged();
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x11c - 0x44];
	BfmeModelConditionFlags m_modelConditionFlags;
	const Coord3D *getPosition() const { return &m_position; }

	void setModelConditionState(BfmeModelConditionFlagType bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			((BfmeObjectModelCondition *)this)->notifyModelConditionChanged();
		}
	}

	void clearModelConditionState(BfmeModelConditionFlagType bit)
	{
		if (m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.clear(bit);
			((BfmeObjectModelCondition *)this)->notifyModelConditionChanged();
		}
	}

};

class Rva001BC560Mover
{
public:
	void move(Object *object, const Coord3D *goalPos,
		Real onPathDistToGoal, Real desiredSpeed);

private:
	void *m_vtable;
	char m_pad004[0x3c];
	unsigned m_flags;
	char m_pad044[0x20];
	BfmeSubC1054 m_bfmeSub;

	enum LocoFlag
	{
		OVER_WATER = 5
	};

	Bool getFlag(LocoFlag flag) const
	{
		return (m_flags >> flag) & 1;
	}

	void setFlag(LocoFlag flag, Bool value)
	{
		if (value)
			m_flags |= (1 << flag);
		else
			m_flags &= ~(1 << flag);
	}
};

void Rva001BC560Mover::move(Object *object, const Coord3D *goalPos,
	Real onPathDistToGoal, Real desiredSpeed)
{
	((BfmeC1054 *)this)->bfmeStep1054((BfmeD1054 *)object,
		(int)goalPos, 0);
	((BfmeD1054 *)object)->bfmeAdd1054(&m_bfmeSub);
	((BfmeA1282 *)this)->bfmeFinish1282((BfmeQ1282 *)object,
		goalPos, onPathDistToGoal, desiredSpeed);

	Coord3D newPosition = *object->getPosition();
	if (TheTerrainLogic->isUnderwater(newPosition.x, newPosition.y, 0, 0))
	{
		if (!getFlag(OVER_WATER))
		{
			setFlag(OVER_WATER, true);
			object->setModelConditionState(BFME_MODELCONDITION_OVER_WATER);
		}
	}
	else
	{
		if (getFlag(OVER_WATER))
		{
			setFlag(OVER_WATER, false);
			object->clearModelConditionState(BFME_MODELCONDITION_OVER_WATER);
		}
	}
}
