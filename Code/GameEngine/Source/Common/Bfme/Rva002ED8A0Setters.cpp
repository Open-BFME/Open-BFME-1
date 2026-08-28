// 25-byte setter, 18-byte global write, and 36-byte audio dispatch

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/VictoryConditions.h
class VictoryConditionsInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19_4c();
};

extern VictoryConditionsInterface *TheVictoryConditions;

class Rva002ED8A0
{
public:
	void setByte08( bool val );

	char m_pad0[ 0x8 ];
	char m_byte08;
};

void Rva002ED8A0::setByte08( bool val )
{
	m_byte08 = val;
	if ( TheVictoryConditions )
	{
		TheVictoryConditions->v19_4c();
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char  m_pad[ 0xA28 ];
	float m_valA28;
};
extern GlobalData *TheWritableGlobalData;

void __stdcall setFloatA28( float val )
{
	TheWritableGlobalData->m_valA28 = val;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11_2c( int a, int b, int c );
	virtual void v12_30( int a, int b, int c );
};

extern AudioManager *TheAudio;

void __stdcall func002EF270( bool enable )
{
	if ( enable )
	{
		TheAudio->v11_2c( 0x10, 1, 1 );
	}
	else
	{
		TheAudio->v12_30( 0x10, 1, 1 );
	}
}
