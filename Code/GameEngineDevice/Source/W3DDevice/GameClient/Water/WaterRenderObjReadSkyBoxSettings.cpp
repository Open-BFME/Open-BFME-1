// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class DataChunkInput
{
public:
	float readReal();
	AsciiString readAsciiString();
};

struct DataChunkInfo;

struct Vector3
{
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

#define SKYBOX_SLOT(n) virtual void slot##n();

class SkyBoxRenderObject
{
public:
	SKYBOX_SLOT(0) SKYBOX_SLOT(1) SKYBOX_SLOT(2) SKYBOX_SLOT(3)
	SKYBOX_SLOT(4) SKYBOX_SLOT(5) SKYBOX_SLOT(6) SKYBOX_SLOT(7)
	SKYBOX_SLOT(8) SKYBOX_SLOT(9) SKYBOX_SLOT(10) SKYBOX_SLOT(11)
	SKYBOX_SLOT(12) SKYBOX_SLOT(13) SKYBOX_SLOT(14) SKYBOX_SLOT(15)
	SKYBOX_SLOT(16) SKYBOX_SLOT(17) SKYBOX_SLOT(18) SKYBOX_SLOT(19)
	SKYBOX_SLOT(20) SKYBOX_SLOT(21)
	virtual void setPosition(const Vector3 &position);
};

#undef SKYBOX_SLOT

class WaterSkyBoxSettingsOwner
{
public:
	void setSkyBoxPosition(float x, float y, float z)
	{
		m_skyBox->setPosition(Vector3(x, y, z));
	}

	void setSkyBoxScale(const float *scale);
	void setSkyBoxRotation007A15A0(const float *rotation);
	void setSkyBoxTexture007A58C0(const AsciiString *texture);

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *volatile m_skyBox;
};

extern WaterSkyBoxSettingsOwner *TheWaterRenderObj;

bool parseSkyBoxSettings007A5BA0(DataChunkInput &file, DataChunkInfo *, void *)
{
	Vector3 position;
	position.X = file.readReal();
	position.Y = file.readReal();
	position.Z = file.readReal();
	float scale = file.readReal();
	float rotation = file.readReal();
	AsciiString texture = file.readAsciiString();

	if (TheWaterRenderObj->m_skyBox != 0) {
		TheWaterRenderObj->setSkyBoxPosition(position.X, position.Y, position.Z);
	}

	TheWaterRenderObj->setSkyBoxScale(&scale);
	TheWaterRenderObj->setSkyBoxRotation007A15A0(&rotation);
	TheWaterRenderObj->setSkyBoxTexture007A58C0(&texture);
	return true;
}
