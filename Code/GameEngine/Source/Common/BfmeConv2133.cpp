#include <string.h>

extern "C" void *_bfmeVfAXZ[];
extern "C" void *_bfmeVfBXZ[];
extern "C" char _bfmeNullNameXZ[];

class RenderObjClass
{
public:
	RenderObjClass();

	unsigned char m_bfmeRocPadXZ[0xc8];
};

class BfmeThingXZ : public RenderObjClass
{
public:
	__forceinline BfmeThingXZ()
	{
		*(void **)this = _bfmeVfAXZ;
		*(void **)((char *)this + 8) = _bfmeVfBXZ;
		strcpy(m_bfmeNameXZ, _bfmeNullNameXZ);
	}

	char m_bfmeNameXZ[0x20];
};

BfmeThingXZ *bfmeCreateXZ()
{
	return new BfmeThingXZ;
}
