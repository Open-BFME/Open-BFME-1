// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_AIR = 1 << 3
};

class LocomotorOverridable
{
public:
	virtual ~LocomotorOverridable();
	LocomotorOverridable *friend_getFinalOverride();

	LocomotorOverridable *m_nextOverride;
};

class Locomotor : public LocomotorOverridable
{
public:
	UnsignedInt getLegalSurfaces() const
	{
		LocomotorOverridable *override = m_nextOverride;
		if( override && override->m_nextOverride )
			override = override->m_nextOverride->friend_getFinalOverride();
		return static_cast<const Locomotor *>(override)->m_legalSurfaces;
	}

private:
	unsigned char m_unmodelled_008[ 0x10 - 8 ];
	UnsignedInt m_legalSurfaces;
};

class Object
{
public:
	__forceinline Bool isNotHeldDisabled() const
	{
		unsigned char disabled = m_disabledMask;
		disabled >>= 3;
		disabled = ~disabled;
		disabled &= 1;
		return disabled;
	}

	unsigned char m_unmodelled_000[ 0x1A4 ];
	unsigned char m_disabledMask;
};

class AIUpdateInterface
{
public:
	virtual Bool isDoingGroundMovement() const;

private:
	unsigned char m_unmodelled_004[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_00C[ 0x1B8 - 0x0C ];
	UnsignedInt m_validLocomotorSurfaces;
	unsigned char m_unmodelled_1BC[ 0x1CC - 0x1BC ];
	Locomotor *m_curLocomotor;
};

Bool AIUpdateInterface::isDoingGroundMovement() const
{
	if( m_validLocomotorSurfaces == LOCOMOTORSURFACE_AIR )
	{
		return false;
	}
	else
	{
		Locomotor *curLocomotor = m_curLocomotor;
		if( curLocomotor == 0 )
			return false;

		if( curLocomotor->getLegalSurfaces() & LOCOMOTORSURFACE_AIR )
			return false;

		return m_object->isNotHeldDisabled();
	}
}
