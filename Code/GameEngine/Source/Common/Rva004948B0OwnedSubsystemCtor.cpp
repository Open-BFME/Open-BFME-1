// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Rva004948B0OwnedSubsystem constructor, retail 0x004945E0, 72 bytes.
// The body installs the vtable at 0x010FA1CC, which the ledger already names
// ??_7Rva004948B0OwnedSubsystem@@6B@, and its matched destructor sits at
// 0x004948B0 in Rva004948B0OwnedSubsystemDtor.cpp. The caller at 0x00596970
// allocates 0x38 bytes and passes one function pointer, which lands at +0x30.

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class Rva004948B0Resource;

class Rva004948B0OwnedSubsystem : public SubsystemInterface
{
public:
	Rva004948B0OwnedSubsystem( void *factory );
	virtual ~Rva004948B0OwnedSubsystem();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	Rva004948B0Resource *m_resource;
	void *m_field0C;
	void *m_field10;
	void *m_field14;
	void *m_field18;
	void *m_field1C;
	unsigned char m_bits : 3;
	int m_field24;
	void *m_field28;
	void *m_field2C;
	void *m_factory;
	void *m_field34;
};

Rva004948B0OwnedSubsystem::Rva004948B0OwnedSubsystem( void *factory )
	: m_resource( 0 ), m_field1C( 0 ), m_bits( 0 ), m_field24( -1 ),
	m_field28( 0 ), m_field2C( 0 ), m_factory( factory ), m_field34( 0 )
{
	m_field0C = 0;
	m_field10 = 0;
	m_field14 = 0;
	m_field18 = 0;
}
