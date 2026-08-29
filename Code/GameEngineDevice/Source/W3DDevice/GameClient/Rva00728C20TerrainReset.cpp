void W3DRadarResetLock( void );
void W3DRadarResetUnlock( void );

class W3DTerrainBackground
{
protected:
	void freeTerrainBuffers( void );
};

class Rva00728C20TerrainReset : private W3DTerrainBackground
{
public:
	void resetBuffers( void );

private:
	unsigned char m_padding[ 0x52 ];
	unsigned char m_reset;
};

void Rva00728C20TerrainReset::resetBuffers( void )
{
	W3DRadarResetLock();
	freeTerrainBuffers();
	W3DRadarResetUnlock();
	m_reset = 1;
}
