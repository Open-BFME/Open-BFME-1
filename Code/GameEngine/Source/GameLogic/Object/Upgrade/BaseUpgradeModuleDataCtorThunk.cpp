// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BaseUpgrade module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0011D190 allocates 0x7C
// bytes and calls this constructor.  The matched destructor independently
// fixes the +0x08 0x68-byte upgrade subobject and two strings at +0x70/+0x74.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_unmodelled[ 0x68 ];
};

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data( 0 ) {}
	~RetailLayoutString();
	void set( const char *text, int length );

private:
	char *m_data;
};

class __declspec(novtable) BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~BaseUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_unmodelled_04;
};

class __declspec(novtable) BaseUpgradeModuleDataIntermediateBase
	: public BaseUpgradeModuleDataPrimaryBase
{
protected:
	UpgradeModuleDataSub m_upgradeData; // +0x08
};

class BaseUpgradeModuleData : public BaseUpgradeModuleDataIntermediateBase
{
public:
	BaseUpgradeModuleData();
	virtual ~BaseUpgradeModuleData();

private:
	RetailLayoutString m_upgradeName; // +0x70
	RetailLayoutString m_conflictName; // +0x74
	unsigned int m_unmodelled_78;
};

// ??0BaseUpgradeModuleData@@QAE@XZ
BaseUpgradeModuleData::BaseUpgradeModuleData()
{
	m_upgradeName.set( "NONE", 4 );
	m_conflictName.set( "NONE", 4 );
	m_unmodelled_78 = 0;
}
