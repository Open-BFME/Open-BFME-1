// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/linegrp.h
class LineGroupClass
{
public:
	virtual ~LineGroupClass();

protected:
	ShareBufferClass<Vector3> *StartLineLoc;
	ShareBufferClass<Vector3> *EndLineLoc;
	ShareBufferClass<Vector4> *LineDiffuse;
	ShareBufferClass<Vector4> *TailDiffuse;
	ShareBufferClass<unsigned int> *ALT;
	ShareBufferClass<float> *LineSize;
	ShareBufferClass<float> *LineUCoord;
	int LineCount;
	RefCountPtr<TextureClass> Texture;
};

LineGroupClass::~LineGroupClass()
{
	REF_PTR_RELEASE(StartLineLoc);
	REF_PTR_RELEASE(EndLineLoc);
	REF_PTR_RELEASE(LineDiffuse);
	REF_PTR_RELEASE(TailDiffuse);
	REF_PTR_RELEASE(ALT);
	REF_PTR_RELEASE(LineSize);
	REF_PTR_RELEASE(LineUCoord);
}
