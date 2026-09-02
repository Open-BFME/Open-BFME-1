// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *first, void *second );
	virtual void primarySlot();
	virtual ~T1A1_005DD290();

private:
	unsigned int m_storage[ 4 ];
};

class ParticleModuleInterface005F2CA0
{
public:
	virtual void interfaceSlot();
};

void s4Second();

class ParticleModule005F2CA0
	: public T1A1_005DD290,
	  public ParticleModuleInterface005F2CA0
{
public:
	ParticleModule005F2CA0( void *first, void *second );
	virtual void moduleSlot();
};

ParticleModule005F2CA0::ParticleModule005F2CA0( void *first, void *second )
	: T1A1_005DD290( first, second )
{
	s4Second();
}
