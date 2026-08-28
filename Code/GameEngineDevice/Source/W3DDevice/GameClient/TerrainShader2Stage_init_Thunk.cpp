// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@TerrainShader2Stage@@UAEHXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// Open-BFME5: retail two-stage terrain shader one-time initialisation in C++.

typedef unsigned long DWORD;

class W3DShaderInterface
{
public:
	virtual int set(int) = 0;
	virtual int init() = 0;
private:
	DWORD m_pad;
};

class TerrainShader2Stage : public W3DShaderInterface
{
public:
	float m_xSlidePerSecond;
	float m_ySlidePerSecond;
	int   m_curTick;
	float m_xOffset;
	float m_yOffset;
	virtual int set(int);
	virtual int init(void);
};

extern TerrainShader2Stage OpenBFME5_terrainShader2Stage;
extern W3DShaderInterface *OpenBFME5_W3DShaders_terrainBase[4];
extern DWORD OpenBFME5_W3DShadersPassCount_terrainBase[4];
extern unsigned int OpenBFME5_WW3D_SyncTime;

int TerrainShader2Stage::init(void)
{
	m_xSlidePerSecond = -0.012f;
	m_ySlidePerSecond = 1.50f * m_xSlidePerSecond;
	m_curTick = 0;
	m_curTick = OpenBFME5_WW3D_SyncTime;
	m_xOffset = 0;
	m_yOffset = 0;

	OpenBFME5_W3DShaders_terrainBase[0] = &OpenBFME5_terrainShader2Stage;
	OpenBFME5_W3DShadersPassCount_terrainBase[0] = 2;
	OpenBFME5_W3DShaders_terrainBase[1] = &OpenBFME5_terrainShader2Stage;
	OpenBFME5_W3DShadersPassCount_terrainBase[1] = 3;
	OpenBFME5_W3DShaders_terrainBase[2] = &OpenBFME5_terrainShader2Stage;
	OpenBFME5_W3DShadersPassCount_terrainBase[2] = 3;
	OpenBFME5_W3DShaders_terrainBase[3] = &OpenBFME5_terrainShader2Stage;
	OpenBFME5_W3DShadersPassCount_terrainBase[3] = 3;

	return 1;
}
