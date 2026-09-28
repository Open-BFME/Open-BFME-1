// cl: /O2 /MD
class WaterSetting
{
public:
	WaterSetting(void);
	virtual ~WaterSetting(void);

	unsigned char m_skyTextureFile[4];
	unsigned char m_waterTextureFile[4];
	unsigned char m_rest[0x7c - 0x0c];
};

WaterSetting WaterSettings[6];
