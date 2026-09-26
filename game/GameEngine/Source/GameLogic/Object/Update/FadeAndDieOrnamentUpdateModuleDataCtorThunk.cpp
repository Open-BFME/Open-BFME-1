// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FadeAndDieOrnamentUpdate module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00125BD0 allocates 0x38
// bytes and calls this body. Its matched destructor at 0x00126E70 independently
// fixes the retail AsciiString at +0x08.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

struct FadeAndDieSettings
{
	FadeAndDieSettings()
		: m_zero18( 0 ), m_one1C( 1 ), m_one20( 1 ), m_one24( 1 ),
		  m_negative28( -1 ), m_negative2C( -1 ), m_zero30( 0 )
	{
	}

	unsigned int m_zero18;
	unsigned int m_one1C;
	unsigned int m_one20;
	unsigned int m_one24;
	int m_negative28;
	int m_negative2C;
	unsigned int m_zero30;
};

class __declspec(novtable) FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	virtual ~FadeAndDieOrnamentUpdateModuleDataBase();

private:
	unsigned int m_moduleData;
};

class FadeAndDieOrnamentUpdateModuleData
	: public FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	virtual ~FadeAndDieOrnamentUpdateModuleData();

private:
	BFMERetailAsciiString m_name;
	float m_value0C;
	float m_value10;
	float m_value14;
	FadeAndDieSettings m_settings;
	unsigned char m_enabled;
	unsigned char m_pad35[ 3 ];
};

// ??0FadeAndDieOrnamentUpdateModuleData@@QAE@XZ
FadeAndDieOrnamentUpdateModuleData::FadeAndDieOrnamentUpdateModuleData()
	: m_value0C( 1.0f ),
	  m_value10( 1.0f ),
	  m_value14( 1.0f )
{
	m_settings.m_zero18 = 0;
	m_settings.m_zero30 = 0;
	m_name.clear();
	m_enabled = 1;
}
