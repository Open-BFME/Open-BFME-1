// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWDebug

#include "matrix4.h"

typedef unsigned char Bool;
typedef unsigned char UnsignedByte;

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();

	void *m_vtable;
	Bool m_isEnabled;
	Bool m_isInvisibleEnabled;
	char m_padding[0x52];
};

struct BfmeVolumetricShadowRenderTask
{
	void *m_nextTask;
	void *m_parentShadow;
	UnsignedByte m_meshIndex;
	UnsignedByte m_lightIndex;
	char m_padding[2];
};

struct BfmeShadowLightPosition
{
	float x;
	float y;
	float z;
};

class W3DVolumetricShadow : public Rva007B12F0Base
{
	int m_field58;
	int m_field5c;
	float m_field60;
	UnsignedByte m_field64;
	char m_padding65[3];

	W3DVolumetricShadow *m_next;
	void *m_geometry;
	void *m_robj;
	float m_shadowLengthScale;
	float m_robjExtent;
	float m_extraExtrusionPadding;

	void *m_shadowVolume[160];
	void *m_shadowVolumeVB[160];
	void *m_shadowVolumeIB[160];
	BfmeVolumetricShadowRenderTask m_shadowVolumeRenderTask[160];
	int m_shadowVolumeCount[160];
	BfmeShadowLightPosition m_lightPosHistory[160];
	Matrix4 m_objectXformHistory[160];
	short *m_silhouetteIndex[160];
	short m_numSilhouetteIndices[160];
	short m_maxSilhouetteEntries[160];
	char m_padding4680[0x280];
	Bool m_shadowEnabled;

public:
	W3DVolumetricShadow();
};

W3DVolumetricShadow::W3DVolumetricShadow()
{
	int i, j;

	m_field58 = 0;
	m_field5c = 0;
	m_field60 = 20.0f;
	m_field64 = 0;
	*(unsigned int *)this = 0x011284CC;
	m_next = 0;
	m_geometry = 0;
	m_shadowLengthScale = 0.0f;
	m_extraExtrusionPadding = 0.0f;
	m_robj = 0;
	m_isEnabled = 1;
	m_isInvisibleEnabled = 0;
	m_shadowEnabled = 0;

	for (j = 0; j < 160; ++j)
	{
		m_numSilhouetteIndices[j] = 0;
		m_maxSilhouetteEntries[j] = 0;
		m_silhouetteIndex[j] = 0;
		m_shadowVolumeCount[j] = 0;
	}

	for (i = 0; i < 1; ++i)
	{
		for (j = 0; j < 160; ++j)
		{
			m_shadowVolume[i * 160 + j] = 0;
			m_shadowVolumeVB[i * 160 + j] = 0;
			m_shadowVolumeIB[i * 160 + j] = 0;
			m_shadowVolumeRenderTask[i * 160 + j].m_parentShadow = this;
			m_shadowVolumeRenderTask[i * 160 + j].m_meshIndex = (UnsignedByte)j;
			m_shadowVolumeRenderTask[i * 160 + j].m_lightIndex = (UnsignedByte)i;
			m_objectXformHistory[i * 160 + j].Make_Identity();
			m_lightPosHistory[i * 160 + j].x = 0;
			m_lightPosHistory[i * 160 + j].y = 0;
			m_lightPosHistory[i * 160 + j].z = 0;
		}
	}
}
