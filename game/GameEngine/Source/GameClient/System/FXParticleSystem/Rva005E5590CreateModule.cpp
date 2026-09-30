// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

extern "C" const void *bfmeVftRva005EB2F0_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB2F0_V3Slot0N=??_7Rva005EB2F0@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EB2F0_V3Slot1W[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB2F0_V3Slot1W=??_7Rva005EB2F0@@6BV3Slot1W@@@")
extern "C" const void *bfmeVftRva005EB2F0_V3Slot2[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB2F0_V3Slot2=??_7Rva005EB2F0@@6BV3Slot2@@@")
extern "C" const void *bfmeVftRva005EAF40_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAF40_V3Slot0N=??_7Rva005EAF40@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EAF40_V3Slot1W[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAF40_V3Slot1W=??_7Rva005EAF40@@6BV3Slot1W@@@")
extern "C" const void *bfmeVftRva005EAF40_V3Slot2[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAF40_V3Slot2=??_7Rva005EAF40@@6BV3Slot2@@@")

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
		*(volatile unsigned int *)this = (unsigned int)bfmeVftRva005EB2F0_V3Slot0N;
		*(volatile unsigned int *)((unsigned char *)this + 8) = (unsigned int)bfmeVftRva005EB2F0_V3Slot1W;
		*(volatile unsigned int *)((unsigned char *)this + 0x10) = (unsigned int)bfmeVftRva005EB2F0_V3Slot2;
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
		*(volatile unsigned int *)this = (unsigned int)bfmeVftRva005EAF40_V3Slot0N;
		*(volatile unsigned int *)((unsigned char *)this + 8) = (unsigned int)bfmeVftRva005EAF40_V3Slot1W;
		*(volatile unsigned int *)((unsigned char *)this + 0x10) = (unsigned int)bfmeVftRva005EAF40_V3Slot2;
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
