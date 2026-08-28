#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <typename T>
const T &Rva003690A0Min(const T &left, const T &right)
{
	return right < left ? right : left;
}

class Rva00368C10Mask
{
public:
	unsigned int m_bits;
};

class Rva00368C10Values
{
public:
	int valueFor(const Rva00368C10Mask *mask) const;
};

class BfmeVisionBonusSource;
class Rva00369860State;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class Rva00369860State;

private:
	BfmeVisionBonusSource *bfmeGetBonusSource(void) const;
};

class Rva00369860Pair
{
public:
	int m_first;
	int m_second;
};

class Rva00369860Range
{
public:
	__forceinline void clear(void) { erase(m_begin, m_end); }

private:
	__forceinline Rva00369860Pair *erase(Rva00369860Pair *first, Rva00369860Pair *last)
	{
		int count = m_end - last;
		Rva00369860Pair *output = first;
		while( count > 0 )
		{
			*output = *last;
			++last;
			++output;
			--count;
		}
		m_end = output;
		return first;
	}

	Rva00369860Pair *m_begin;
	Rva00369860Pair *m_end;
	Rva00369860Pair *m_capacity;
};

class Rva00369860State
{
public:
	Rva00369860Range m_pairs;
	Rva00368C10Mask m_mask;
	char m_unreconstructed10[ 4 ];
	int m_mode;
	int m_field18;
	int m_firstValues[ 10 ];
	int m_secondValues[ 10 ];
	int m_primaryValues[ 3 ];
	int m_secondaryValues[ 3 ];
	char m_unreconstructed84[ 8 ];
	bool m_flag8C;

	void reset(int mode);
	int primaryValueFor(const Object *object) const;
	int secondaryValueFor(const Object *object) const;
};

void Rva00369860State::reset(int mode)
{
	m_mode = mode;
	m_field18 = 0;
	m_pairs.clear();
	memset(m_firstValues, 0, sizeof(m_firstValues));
	memset(m_secondValues, 0, sizeof(m_secondValues));
	m_flag8C = false;
	// Keep the flag store ahead of the saved-register restore, as in retail.
	_ReadWriteBarrier();
	m_primaryValues[0] = 0;
	m_secondaryValues[0] = 0;
	m_primaryValues[1] = 0;
	m_secondaryValues[1] = 0;
	m_primaryValues[2] = 0;
	m_secondaryValues[2] = 0;
}

// @?reset@Rva00369860State@@QAEXH@Z 0x00369860

int Rva00369860State::primaryValueFor(const Object *object) const
{
	if( !m_flag8C || object == 0 )
		return m_primaryValues[0];

	// Only this lookup interface is proven; the concrete bonus-source type is opaque.
	Rva00368C10Values *values =
		(Rva00368C10Values *)object->bfmeGetBonusSource();
	if( values == 0 )
		return m_primaryValues[0];

	int index = values->valueFor(&m_mask) - 1;
	index = Rva003690A0Min(index, 2);
	return index >= 0 ? m_primaryValues[index] : m_primaryValues[0];
}

// @?primaryValueFor@Rva00369860State@@QBEHPBVObject@@@Z 0x003690A0

int Rva00369860State::secondaryValueFor(const Object *object) const
{
	if( !m_flag8C || object == 0 )
		return m_secondaryValues[0];

	Rva00368C10Values *values =
		(Rva00368C10Values *)object->bfmeGetBonusSource();
	if( values == 0 )
		return m_secondaryValues[0];

	int index = values->valueFor(&m_mask) - 1;
	index = Rva003690A0Min(index, 2);
	return index >= 0 ? m_secondaryValues[index] : m_secondaryValues[0];
}

// @?secondaryValueFor@Rva00369860State@@QBEHPBVObject@@@Z 0x00369120
