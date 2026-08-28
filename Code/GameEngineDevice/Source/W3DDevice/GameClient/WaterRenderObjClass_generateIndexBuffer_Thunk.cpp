// cl: /DNDEBUG /MD /EHsc
// readable body of ?generateIndexBuffer@WaterRenderObjClass@@IAEJHH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// Open-BFME5: lift the water index-buffer generator to clean C++.

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef long HRESULT;

class RetailIndexBuffer
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0;
	virtual HRESULT __stdcall Lock(unsigned int, unsigned int, BYTE **, unsigned int) = 0;
	virtual HRESULT __stdcall Unlock() = 0;
};

class RetailDevice
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual HRESULT __stdcall CreateIndexBuffer(unsigned int, unsigned int, unsigned int,
		unsigned int, RetailIndexBuffer **, void *) = 0;
};

extern RetailDevice *g_retailWaterDevice;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
protected:
	HRESULT generateIndexBuffer(Int sizeX, Int sizeY);

private:
	unsigned char m_gap0[0x128];
	RetailIndexBuffer *m_indexBufferD3D;
	unsigned char m_gap1[0x14];
	Int m_numIndices;
};

// ?generateIndexBuffer@WaterRenderObjClass@@IAEJHH@Z
HRESULT WaterRenderObjClass::generateIndexBuffer(Int sizeX, Int sizeY)
{
	HRESULT hr;
	m_numIndices = (sizeY - 1) * (sizeX * 2 + 2) - 2;
	WORD *pIndices;

	if ((hr = g_retailWaterDevice->CreateIndexBuffer((m_numIndices + 2) * sizeof(WORD),
		8, 101, 1, &m_indexBufferD3D, 0)) < 0)
		return hr;

	if ((hr = m_indexBufferD3D->Lock(0, m_numIndices * sizeof(WORD), (BYTE **)&pIndices, 0)) < 0)
		return hr;

	Int i, j, k;
	for (i = 0, j = 0, k = 0; i < m_numIndices; j++)
	{
		for (; k < sizeX * (j + 1); k++, i += 2)
		{
			pIndices[i] = (UnsignedShort)k + sizeX;
			pIndices[i + 1] = (UnsignedShort)k;
		}
		if (i < m_numIndices)
		{
			pIndices[i] = k - 1;
			pIndices[i + 1] = k + sizeX;
			i += 2;
		}
	}

	if ((hr = m_indexBufferD3D->Unlock()) < 0)
		return hr;
	return 0;
}
