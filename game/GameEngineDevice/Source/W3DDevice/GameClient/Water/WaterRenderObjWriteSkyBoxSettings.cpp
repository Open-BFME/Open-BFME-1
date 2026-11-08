// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Clean reconstruction of the SkyboxSettings chunk writer at retail
// 0x0079F480.

#include "ascii_string.h"

// Retail's accessor row returns the class-keyed Vector3 (?AVVector3@@).
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
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

// Row at 0x0079F360 (ILT 0x00010F14): the sky-box position getter is a method of this accessor view.
class WaterSkyBoxPositionAccessor
{
public:
	Vector3 getSkyBoxPosition(void) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	void writeSkyBoxSettings0079F480(DataChunkOutput *output);
	float bfmeSkyBoxZRotation0079F3E0(void) const;	// row ?bfmeSkyBoxZRotation0079F3E0@WaterRenderObjClass@@QBEMXZ

private:

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *m_skyBox;
	unsigned char m_beforeSkyBoxTextureName[0x74];
	AsciiString m_skyBoxTextureName;
};

void WaterRenderObjClass::writeSkyBoxSettings0079F480(DataChunkOutput *output)
{
	output->openDataChunk("SkyboxSettings", 1);

	Vector3 position = ((const WaterSkyBoxPositionAccessor *)this)->getSkyBoxPosition();
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
