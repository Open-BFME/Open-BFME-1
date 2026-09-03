// readable body of ?ReAcquireResources@W3DProjectedShadowManager@@QAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
typedef long HRESULT;

class ShadowBuffer
{
};

#define DEVICE_SLOT(n) virtual void slot##n();

class ShadowDevice
{
public:
	DEVICE_SLOT(0) DEVICE_SLOT(1) DEVICE_SLOT(2) DEVICE_SLOT(3)
	DEVICE_SLOT(4) DEVICE_SLOT(5) DEVICE_SLOT(6) DEVICE_SLOT(7)
	DEVICE_SLOT(8) DEVICE_SLOT(9) DEVICE_SLOT(10) DEVICE_SLOT(11)
	DEVICE_SLOT(12) DEVICE_SLOT(13) DEVICE_SLOT(14) DEVICE_SLOT(15)
	DEVICE_SLOT(16) DEVICE_SLOT(17) DEVICE_SLOT(18) DEVICE_SLOT(19)
	DEVICE_SLOT(20) DEVICE_SLOT(21) DEVICE_SLOT(22) DEVICE_SLOT(23)
	DEVICE_SLOT(24) DEVICE_SLOT(25)
	virtual HRESULT __stdcall createVertexBuffer(unsigned int length, unsigned int usage,
		unsigned int fvf, unsigned int pool, ShadowBuffer **buffer, void *sharedHandle);
	virtual HRESULT __stdcall createIndexBuffer(unsigned int length, unsigned int usage,
		unsigned int format, unsigned int pool, ShadowBuffer **buffer, void *sharedHandle);
};

#undef DEVICE_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadowManager
{
public:
	bool ReAcquireResources();
};

bool W3DProjectedShadowManager::ReAcquireResources()
{
	ShadowDevice *device = *(ShadowDevice **)0x01340534;
	ShadowBuffer **indexBuffer = (ShadowBuffer **)0x01306E08;
	if (device->createIndexBuffer(0x20000, 0x208, 101, 0, indexBuffer, 0) < 0)
		return false;

	if (*(ShadowBuffer **)0x01306E04 == 0
		&& device->createVertexBuffer(0x100000, 0x208, 0, 0,
			(ShadowBuffer **)0x01306E04, 0) < 0)
		return false;

	return true;
}
