// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the SkyboxSettings chunk writer at retail
// 0x0079F480.

class AsciiString
{
private:
	void *m_data;
};

struct Vector3
{
	float X;
	float Y;
	float Z;
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void writeReal(float value);
	void writeAsciiString(const AsciiString &value);
	void closeDataChunk(void);
};

class SkyBoxRenderObject
{
private:
	unsigned char m_beforeScale[0x48];
	float m_scale;

	friend class WaterRenderObjClass;
};

class WaterRenderObjClass
{
public:
	void writeSkyBoxSettings0079F480(DataChunkOutput *output);

private:
	Vector3 bfmeSkyBoxPosition0079F360(void) const;
	float bfmeSkyBoxZRotation0079F3E0(void) const;

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *m_skyBox;
	unsigned char m_beforeSkyBoxTextureName[0x74];
	AsciiString m_skyBoxTextureName;
};

void WaterRenderObjClass::writeSkyBoxSettings0079F480(DataChunkOutput *output)
{
	output->openDataChunk("SkyboxSettings", 1);

	Vector3 position = bfmeSkyBoxPosition0079F360();
	float scale = 1.0f;
	if (m_skyBox != 0)
		scale = m_skyBox->m_scale;
	float rotation = bfmeSkyBoxZRotation0079F3E0();

	output->writeReal(position.X);
	output->writeReal(position.Y);
	output->writeReal(position.Z);
	output->writeReal(scale);
	output->writeReal(rotation);
	output->writeAsciiString(m_skyBoxTextureName);
	output->closeDataChunk();
}
