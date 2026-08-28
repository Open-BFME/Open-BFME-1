// cl: /O2 /Ob0
// readable body of ?setShroudClearingRange@Object@@QAEXM@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::setShroudClearingRange, retail 0x001BF3B0.  BFME updates the
// shroud-side spatial data only when the range actually changes.  The pointer
// at +0x3B0 is intentionally represented by the established PartitionData
// shim name: its exact makeDirty() body is already recovered at 0x008F7B30,
// although this Object field belongs to the shroud manager rather than the
// partition-manager field at +0x3B4.

typedef float Real;

class PartitionData
{
public:
	void makeDirty( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setShroudClearingRange( Real newShroudClearingRange );

private:
	unsigned char m_unmodelled_000[ 0x198 ];
	Real m_shroudClearingRange;                         // +0x198
	unsigned char m_unmodelled_19C[ 0x3B0 - 0x19C ];
	PartitionData *m_shroudData;                        // +0x3B0
};

// ?setShroudClearingRange@Object@@QAEXM@Z
void Object::setShroudClearingRange( Real newShroudClearingRange )
{
	if( newShroudClearingRange != m_shroudClearingRange )
	{
		m_shroudClearingRange = newShroudClearingRange;
		if( m_shroudData )
			m_shroudData->makeDirty();
	}
}
