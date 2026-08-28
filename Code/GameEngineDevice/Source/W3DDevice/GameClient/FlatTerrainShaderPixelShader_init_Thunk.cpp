// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@FlatTerrainShaderPixelShader@@UAEHXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// Open-BFME5: lift the retail six-variant flat-terrain shader setup to C++.

typedef unsigned long DWORD;
typedef long HRESULT;

enum ChipsetType
{
	DC_UNKNOWN = 0,
	DC_GENERIC_PIXEL_SHADER_1_1 = 3
};

class W3DShaderInterface
{
public:
	virtual int set(int) = 0;
	virtual int init() = 0;
private:
	DWORD m_pad;
};

class FlatTerrainShaderPixelShader : public W3DShaderInterface
{
public:
	virtual int set(int);
	virtual int init();
private:
	DWORD m_dwBasePixelShader;
	DWORD m_dwBaseNoise1PixelShader;
	DWORD m_dwBaseNoise2PixelShader;
	DWORD m_dwBase0PixelShader;
	DWORD m_dwTaintPixelShader;
	DWORD m_dwTaint2PixelShader;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	static ChipsetType getChipset();
	static HRESULT LoadAndCreateD3DShader(const char *filename, DWORD *shader);
};

extern W3DShaderInterface *OpenBFME5_W3DShaders_flatTerrainBase[4];
extern DWORD OpenBFME5_W3DShadersPassCount_flatTerrainBase[4];
extern FlatTerrainShaderPixelShader OpenBFME5_flatTerrainShaderPixelShader;

int FlatTerrainShaderPixelShader::init()
{
	int res;
	if ((res = W3DShaderManager::getChipset()) >= DC_GENERIC_PIXEL_SHADER_1_1) {
		if (res >= DC_GENERIC_PIXEL_SHADER_1_1) {
			HRESULT hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\fterrain.pso", &m_dwBasePixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\terraintaint.pso", &m_dwTaintPixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\terraintaint2.pso", &m_dwTaint2PixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\fterrain0.pso", &m_dwBase0PixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\fterrainnoise.pso", &m_dwBaseNoise1PixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\fterrainnoise2.pso", &m_dwBaseNoise2PixelShader);
			if (hr < 0) return 0;

			OpenBFME5_W3DShaders_flatTerrainBase[0] = &OpenBFME5_flatTerrainShaderPixelShader;
			OpenBFME5_W3DShaders_flatTerrainBase[1] = &OpenBFME5_flatTerrainShaderPixelShader;
			OpenBFME5_W3DShaders_flatTerrainBase[2] = &OpenBFME5_flatTerrainShaderPixelShader;
			OpenBFME5_W3DShaders_flatTerrainBase[3] = &OpenBFME5_flatTerrainShaderPixelShader;
			OpenBFME5_W3DShadersPassCount_flatTerrainBase[0] = 2;
			OpenBFME5_W3DShadersPassCount_flatTerrainBase[1] = 2;
			OpenBFME5_W3DShadersPassCount_flatTerrainBase[2] = 2;
			OpenBFME5_W3DShadersPassCount_flatTerrainBase[3] = 2;
			return 1;
		}
	}
	return 0;
}
