// readable body of ?init@RoadShaderPixelShader@@EAEHXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// Open-BFME: RoadShaderPixelShader::init, retail 0x007CCE70, 179 bytes.
//
// Reset the four FE shader-table slots, require chipset >= 3, then load
// roadnoise1/2/3.pso into this+8/0xC/0x10. On success the last three table
// pointers switch to the alternate default.

extern int g_bfmeDefaultFE[];
extern int g_bfmeAltFE[];
extern int g_bfmeFlagsFE[4];
extern int *g_bfmePointersFE[4];

enum ChipsetType
{
	BFME_DC_GENERIC_PIXEL_SHADER_1_1 = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	static ChipsetType getChipset(void);
};

class BfmeShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, unsigned long *shader);
};

class RoadShaderPixelShader
{
private:
	virtual int init(void);

	unsigned char m_pad[4];
	unsigned long m_roadNoise1;
	unsigned long m_roadNoise2;
	unsigned long m_roadNoise3;
};

int RoadShaderPixelShader::init(void)
{
	int *def = g_bfmeDefaultFE;
	int one = 1;

	g_bfmePointersFE[0] = def;
	g_bfmeFlagsFE[0] = one;
	g_bfmePointersFE[1] = def;
	g_bfmeFlagsFE[1] = one;
	g_bfmePointersFE[2] = def;
	g_bfmeFlagsFE[2] = one;
	g_bfmePointersFE[3] = def;
	g_bfmeFlagsFE[3] = one;

	if (W3DShaderManager::getChipset() >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
	{
		if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise1.pso", &m_roadNoise1) >= 0)
		{
			if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise2.pso", &m_roadNoise2) >= 0)
			{
				if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise3.pso", &m_roadNoise3) >= 0)
				{
					int *alt = g_bfmeAltFE;
					g_bfmePointersFE[1] = alt;
					g_bfmePointersFE[2] = alt;
					g_bfmePointersFE[3] = alt;
					g_bfmeFlagsFE[1] = one;
					g_bfmeFlagsFE[2] = one;
					g_bfmeFlagsFE[3] = one;
					return one;
				}
			}
		}
	}

	return 0;
}
