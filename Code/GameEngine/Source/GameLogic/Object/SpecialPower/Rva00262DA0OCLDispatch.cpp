class Coord3D
{
	public:
	int m_x;
	int m_y;
	int m_z;
};

struct Rva00262DA0Owner
{
	unsigned char m_pad00[ 0x38 ];
	volatile int m_x;
	volatile int m_y;
	volatile int m_z;
	unsigned char m_pad48[ 0x160 ];
	int m_ready;
};

class Object;
class Rva00262DA0OCLDispatch;

class Rva0026A620Owner
{
public:
	void apply( const Coord3D *loc, unsigned int commandOptions );
};

class ObjectCreationList
{
	private:
	friend class Rva00262DA0OCLDispatch;
	Object *createInternal( const Object *primaryObj, const Coord3D *primary,
		const Coord3D *secondary, float angle, unsigned int lifetimeFrames ) const;
};

class OCLSpecialPower
{
public:
	const ObjectCreationList *findOCL() const;
};

class Rva00262DA0OCLDispatch : public Rva0026A620Owner
{
public:
	void run( void *argument );
};

void Rva00262DA0OCLDispatch::run( void *argument )
{
	Rva00262DA0Owner *owner = *(Rva00262DA0Owner **)( (char *)this - 8 );
	if ( owner->m_ready == 0 )
	{
		volatile Coord3D triple;
		triple.m_x = owner->m_x;
		triple.m_y = owner->m_y;
		triple.m_z = owner->m_z;
		apply( (const Coord3D *)&triple, (unsigned int)argument );
		const ObjectCreationList *ocl =
			((const OCLSpecialPower *)( (char *)this - 0x10 ))->findOCL();
		if ( ocl != 0 )
		{
			owner = *(Rva00262DA0Owner **)( (char *)this - 8 );
			ocl->createInternal( (const Object *)owner,
				(const Coord3D *)&triple, 0, 0.0f, 0 );
		}
	}
}
