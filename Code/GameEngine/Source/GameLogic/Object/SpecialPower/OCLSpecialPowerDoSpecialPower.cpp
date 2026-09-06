// cl: /DNDEBUG /MD /EHsc
//
// OCLSpecialPowerInterface::doSpecialPower, retail RVA 0x00262DA0 -- what the
// OCLSpecialPower module does when its power fires.
//
// Identity: ??0OCLSpecialPower@@ stores vftable 0x00CB6010 at object offset
// +0x10, and this body is that table's doSpecialPower slot (the slot the shared
// base body 0x0026A550 occupies in every other power's table).  `this` is
// therefore the SpecialPowerModuleInterface sub-object; -0x08 is the Object and
// -0x10 the OCLSpecialPower module, whose findOCL is already named at
// 0x00262BC0.
//
// It copies the object's own position (Object +0x38), runs the base
// doSpecialPowerAtLocation there, then spawns the module's ObjectCreationList
// at the same spot.

class Coord3D
{
	public:
	int m_x;
	int m_y;
	int m_z;
};

struct ObjectFields
{
	unsigned char m_pad00[ 0x38 ];
	volatile int m_x;
	volatile int m_y;
	volatile int m_z;
	unsigned char m_pad48[ 0x160 ];
	int m_disabledMask;
};

class Object;
class OCLSpecialPowerInterface;

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation( const Coord3D *loc, unsigned int commandOptions );
};

class ObjectCreationList
{
	private:
	friend class OCLSpecialPowerInterface;
	Object *createInternal( const Object *primaryObj, const Coord3D *primary,
		const Coord3D *secondary, float angle, unsigned int lifetimeFrames ) const;
};

class OCLSpecialPower
{
public:
	const ObjectCreationList *findOCL() const;
};

class OCLSpecialPowerInterface : public SpecialPowerModuleInterface
{
public:
	void doSpecialPower( unsigned int commandOptions );
};

void OCLSpecialPowerInterface::doSpecialPower( unsigned int commandOptions )
{
	ObjectFields *owner = *(ObjectFields **)( (char *)this - 8 );
	if ( owner->m_disabledMask == 0 )
	{
		volatile Coord3D triple;
		triple.m_x = owner->m_x;
		triple.m_y = owner->m_y;
		triple.m_z = owner->m_z;
		doSpecialPowerAtLocation( (const Coord3D *)&triple, commandOptions );
		const ObjectCreationList *ocl =
			((const OCLSpecialPower *)( (char *)this - 0x10 ))->findOCL();
		if ( ocl != 0 )
		{
			owner = *(ObjectFields **)( (char *)this - 8 );
			ocl->createInternal( (const Object *)owner,
				(const Coord3D *)&triple, 0, 0.0f, 0 );
		}
	}
}
