void W3DRadarResetLock( void );
void W3DRadarResetUnlock( void );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainBackground.h
class W3DTerrainBackground
{
public:
	void resetBuffers( void );

protected:
	void freeTerrainBuffers( void );

private:
	unsigned char m_padding[ 0x52 ];
	unsigned char m_reset;
};

void W3DTerrainBackground::resetBuffers( void )
{
	W3DRadarResetLock();
	freeTerrainBuffers();
	W3DRadarResetUnlock();
	m_reset = 1;
}
