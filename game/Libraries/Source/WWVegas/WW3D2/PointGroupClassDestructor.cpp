// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "sharebuf.h"
#include "texture.h"
#include "vector3.h"
#include "vector4.h"

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent)
		{
			Referent->Release_Ref();
		}
	}

private:
	T *Referent;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
class PointGroupClass
{
public:
	virtual ~PointGroupClass();

protected:
	ShareBufferClass<Vector3> *PointLoc;
	ShareBufferClass<Vector4> *PointDiffuse;
	ShareBufferClass<unsigned int> *APT;
	ShareBufferClass<float> *PointSize;
	ShareBufferClass<unsigned char> *PointOrientation;
	ShareBufferClass<unsigned char> *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	RefCountPtr<TextureClass> Texture;
};

PointGroupClass::~PointGroupClass()
{
	REF_PTR_RELEASE(PointLoc);
	REF_PTR_RELEASE(PointDiffuse);
	REF_PTR_RELEASE(APT);
	REF_PTR_RELEASE(PointSize);
	REF_PTR_RELEASE(PointOrientation);
	REF_PTR_RELEASE(PointFrame);
}
