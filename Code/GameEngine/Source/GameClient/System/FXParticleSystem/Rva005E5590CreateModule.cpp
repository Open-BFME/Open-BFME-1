// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

inline void *operator new( unsigned int, void *place )
{
	return place;
}

struct ParticleModuleStateSource005FD300
{
	char m_pad00[ 8 ];
	unsigned char m_flag08;
	char m_pad09[ 7 ];
	unsigned int m_value10;
	unsigned int m_value14;
	unsigned char m_flag18;
};

class ParticleModuleOwnerBase005FD300
{
public:
	ParticleModuleOwnerBase005FD300( void *owner ) : m_owner( owner ) {}
	virtual void ownerSlot();

private:
	void *m_owner;
};

class ParticleModuleFlagBase005FD300
{
public:
	ParticleModuleFlagBase005FD300() : m_flag( 1 ) {}
	virtual void flagSlot();

protected:
	unsigned char m_flag;
	char m_pad[ 3 ];
};

class ParticleModuleValuesBase005FD300
{
public:
	ParticleModuleValuesBase005FD300()
		: m_value0( 0 ), m_value1( 0 ), m_flag( 0 ) {}
	virtual void valuesSlot();

protected:
	unsigned int m_value0;
	unsigned int m_value1;
	unsigned char m_flag;
	char m_pad[ 3 ];
	unsigned char m_trailingFlag;
};

class ParticleModuleState005FD300
	: public ParticleModuleOwnerBase005FD300,
	  public ParticleModuleFlagBase005FD300,
	  public ParticleModuleValuesBase005FD300
{
public:
	ParticleModuleState005FD300( void *owner,
		const ParticleModuleStateSource005FD300 *source );
	virtual void stateSlot();
};

class ParticleModuleStateAllocation005E5590
{
public:
	__forceinline ParticleModuleStateAllocation005E5590(
		void *owner, const ParticleModuleStateSource005FD300 *source )
	{
		new ( (void *)this ) ParticleModuleState005FD300( owner, source );
		*(volatile unsigned int *)this = 0x01111d54;
		*(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111d50;
		*(volatile unsigned int *)((unsigned char *)this + 0x10) = 0x01111d3c;
	}

private:
	unsigned char m_storage[ 0x24 ];
};

class Rva005E5590Template
{
public:
	void *createModule( void *sys );
};

void *Rva005E5590Template::createModule( void *sys )
{
	return (void *)new ParticleModuleStateAllocation005E5590(
		sys, (const ParticleModuleStateSource005FD300 *)this );
}

struct ParticleModuleStateSource005FC800
{
	char m_pad00[ 8 ];
	unsigned char m_flag08;
	char m_pad09[ 7 ];
	unsigned int m_value10;
	unsigned int m_value14;
};

class ParticleModuleOwnerBase005FC800
{
public:
	ParticleModuleOwnerBase005FC800( void *owner ) : m_owner( owner ) {}
	virtual void ownerSlot();

private:
	void *m_owner;
};

class ParticleModuleFlagBase005FC800
{
public:
	ParticleModuleFlagBase005FC800() : m_flag( 1 ) {}
	virtual void flagSlot();

protected:
	unsigned char m_flag;
	char m_pad[ 3 ];
};

class ParticleModuleValuesBase005FC800
{
public:
	ParticleModuleValuesBase005FC800()
		: m_value0( 0 ), m_value1( 0 ) {}
	virtual void valuesSlot();

protected:
	unsigned int m_value0;
	unsigned int m_value1;
};

class ParticleModuleState005FC800
	: public ParticleModuleOwnerBase005FC800,
	  public ParticleModuleFlagBase005FC800,
	  public ParticleModuleValuesBase005FC800
{
public:
	ParticleModuleState005FC800( void *owner,
		const ParticleModuleStateSource005FC800 *source );
	virtual void stateSlot();

private:
	unsigned char m_trailingFlag;
};

class ParticleModuleStateAllocation005E6350
{
public:
	__forceinline ParticleModuleStateAllocation005E6350(
		void *owner, const ParticleModuleStateSource005FC800 *source )
	{
		new ( (void *)this ) ParticleModuleState005FC800( owner, source );
		*(volatile unsigned int *)this = 0x01112144;
		*(volatile unsigned int *)((unsigned char *)this + 8) = 0x01112140;
		*(volatile unsigned int *)((unsigned char *)this + 0x10) = 0x0111212c;
	}

private:
	unsigned char m_storage[ 0x20 ];
};

class Rva005E6350Template
{
public:
	void *createModule( void *sys );
};

void *Rva005E6350Template::createModule( void *sys )
{
	return (void *)new ParticleModuleStateAllocation005E6350(
		sys, (const ParticleModuleStateSource005FC800 *)this );
}
