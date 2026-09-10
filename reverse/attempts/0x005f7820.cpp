// ?d_005f7820@@YAXXZ
// partial score=0.985 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

// RenderObjectDrawModule constructs the two-vtable module base and copies the
// draw settings held by the module template.  The caller at 0x005E59C0 is the
// DefaultParticleModule<5> forwarding constructor; its source argument is the
// template object, not another RenderObjectDrawModule.

template <typename Character>
class StringBase
{
public:
	void set( const StringBase &other );

	void *m_data;
};

class BfmeR0
{
public:
	virtual void slot0();
	virtual ~BfmeR0();
	int m_pad[4];
};

class BfmeR1
{
public:
	virtual void slot1();
};

class BfmeRMiddle : public BfmeR0, public BfmeR1
{
public:
	BfmeRMiddle( void *first, void *second );
};

namespace FXParticleSystem
{

class ParticleSystem;

template <typename T>
class TrackingPtr
{
};

extern "C" char RenderObjectDrawModuleInfo_vtbl;

class __declspec(novtable) RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleInfo()
	{
		*reinterpret_cast<char *volatile *>(this) = &RenderObjectDrawModuleInfo_vtbl;
		*reinterpret_cast<unsigned int volatile *>(&m_name0) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_name1) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_name2) = 0;
		*reinterpret_cast<unsigned char volatile *>(&m_flag) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value00) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value01) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value02) = 8;
		*reinterpret_cast<unsigned int volatile *>(&m_value10) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value11) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value12) = 8;
		*reinterpret_cast<unsigned int volatile *>(&m_value20) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value21) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_value22) = 8;
		*reinterpret_cast<unsigned char volatile *>(&m_enabled) = 0;
		*reinterpret_cast<unsigned int volatile *>(&m_type) = 0;
	}

	virtual ~RenderObjectDrawModuleInfo();

	unsigned char m_enabled;
	unsigned int m_type;
	unsigned char m_flag;
	::StringBase<char> m_name0;
	unsigned int m_value00;
	unsigned int m_value01;
	unsigned int m_value02;
	::StringBase<char> m_name1;
	unsigned int m_value10;
	unsigned int m_value11;
	unsigned int m_value12;
	::StringBase<char> m_name2;
	unsigned int m_value20;
	unsigned int m_value21;
	unsigned int m_value22;
};

class RenderObjectDrawModule
	: public ::BfmeRMiddle, public RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModule(
		TrackingPtr<ParticleSystem> &system, const void *source );

	unsigned int m_field58;
};

RenderObjectDrawModule::RenderObjectDrawModule(
	TrackingPtr<ParticleSystem> &system, const void *source )
	: ::BfmeRMiddle( &system, const_cast<void *>( source ) ),
	  RenderObjectDrawModuleInfo()
{
	const unsigned char *bytes = static_cast<const unsigned char *>( source );
	const ::StringBase<char> *name0 =
		reinterpret_cast<const ::StringBase<char> *>( bytes + 0x18 );
	const ::StringBase<char> *name1 =
		reinterpret_cast<const ::StringBase<char> *>( bytes + 0x28 );
	const ::StringBase<char> *name2 =
		reinterpret_cast<const ::StringBase<char> *>( bytes + 0x38 );

	m_flag = bytes[0x14];
	m_name0.set( *name0 );
	m_value00 = *reinterpret_cast<const unsigned int *>( bytes + 0x1c );
	m_value01 = *reinterpret_cast<const unsigned int *>( bytes + 0x20 );
	m_value02 = *reinterpret_cast<const unsigned int *>( bytes + 0x24 );
	m_name1.set( *name1 );
	m_value10 = *reinterpret_cast<const unsigned int *>( bytes + 0x2c );
	m_value11 = *reinterpret_cast<const unsigned int *>( bytes + 0x30 );
	m_value12 = *reinterpret_cast<const unsigned int *>( bytes + 0x34 );
	m_name2.set( *name2 );
	m_value20 = *reinterpret_cast<const unsigned int *>( bytes + 0x3c );
	m_value21 = *reinterpret_cast<const unsigned int *>( bytes + 0x40 );
	m_value22 = *reinterpret_cast<const unsigned int *>( bytes + 0x44 );
	m_enabled = bytes[0x0c];
	m_type = *reinterpret_cast<const unsigned int *>( bytes + 0x10 );
	m_field58 = 8;
}

}
