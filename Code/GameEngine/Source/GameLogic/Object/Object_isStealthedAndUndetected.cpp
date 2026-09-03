// cl: /DNDEBUG /MD /EHsc
// isStealthedAndUndetected: status bit 15 (STEALTHED) set, bit 17 clear,
// and either no viewer, viewer->m_2C != 1, or this has no recently-active
// weapon.  Callee is Object::bfmeHasActiveOrRecentlyActiveWeapon.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;

private:
	unsigned char m_pad[0x90];
	UnsignedInt m_status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeHasActiveOrRecentlyActiveWeapon() const;

	unsigned char m_pad[0x2C];
	Int m_2C;
};

Bool BFMEObjectStealthQuery::isStealthedAndUndetected(const Object *viewer) const
{
	UnsignedInt status = m_status;
	if (status & 0x8000)
	{
		if (!(status & 0x20000))
		{
			if (viewer)
			{
				if (viewer->m_2C == 1)
				{
					if (((Object *)this)->bfmeHasActiveOrRecentlyActiveWeapon())
						return false;
				}
			}
			return true;
		}
	}
	return false;
}
