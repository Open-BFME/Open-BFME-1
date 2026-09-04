// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTruckDraw constructor at retail 0x0077FB20.
// The BFME vehicle layout carries three 12-byte particle handles and two
// 0x70-byte AudioEventRTS members after the scripted-model base.

typedef bool Bool;
typedef char Char;

class Thing;
class ModuleData;

// Reuse the proven dual-vtable scripted-model base layout from
// W3DSupplyDrawConstructors.cpp.  Its constructor is the retail ILT at
// 0x000285EC.
class DrawModule
{
public:
	virtual void drawModuleAnchor();

private:
	Char m_data[ 8 ];
};

class W3DModelDrawInterface
{
public:
	virtual void w3dModelDrawInterfaceAnchor();
};

class W3DScriptedModelDraw : public DrawModule, public W3DModelDrawInterface
{
public:
	W3DScriptedModelDraw( Thing *, const ModuleData * );
	~W3DScriptedModelDraw() throw();

private:
	Char m_unmodelled_10[ 0x27C - 0x10 ];
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle( void *system ) throw(...)
	{
		m_system = system;
		m_next = 0;
		m_previous = 0;
	}

	~BfmeParticleSystemHandle() throw();

private:
	void *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class BfmeTruckZeroSlots
{
public:
	BfmeTruckZeroSlots()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
		m_28 = 0;
		m_2c = 0;
		m_30 = 0;
		m_34 = 0;
		m_38 = 0;
		m_3c = 0;
		m_40 = 0;
		m_44 = 0;
		m_48 = 0;
		m_4c = 0;
		m_50 = 0;
		m_54 = 0;
		m_58 = 0;
		m_5c = 0;
		m_60 = 0;
	}

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	int m_60;
};

class AsciiString
{
public:
	Char *m_data;
};

extern AsciiString TheEmptyString;

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &, int );
	virtual ~AudioEventRTS();

private:
	Char m_storage[ 0x6C ];
};

class W3DTruckDraw : public W3DScriptedModelDraw
{
public:
	W3DTruckDraw( Thing *, const ModuleData * );

private:
	Bool m_effectsInitialized;
	Bool m_wasAirborne;
	Bool m_isPowersliding;
	BfmeParticleSystemHandle m_dustEffect;
	BfmeParticleSystemHandle m_dirtEffect;
	BfmeParticleSystemHandle m_powerslideEffect;
	BfmeTruckZeroSlots m_unmodelled_2a4;
	AudioEventRTS m_powerslideSound;
	AudioEventRTS m_landingSound;
	int m_unmodelled_3e8;
};

// ??0W3DTruckDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DTruckDraw::W3DTruckDraw( Thing *thing, const ModuleData *moduleData )
	: W3DScriptedModelDraw( thing, moduleData )
	, m_effectsInitialized( false )
	, m_wasAirborne( false )
	, m_isPowersliding( false )
	, m_dustEffect( 0 )
	, m_dirtEffect( 0 )
	, m_powerslideEffect( 0 )
	, m_unmodelled_2a4()
	, m_powerslideSound( TheEmptyString, 0 )
	, m_landingSound( TheEmptyString, 0 )
	, m_unmodelled_3e8( 0 )
{
}
