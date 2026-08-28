// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ??0TexBufferClass@@: Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp

#include <string.h>

class ShareBufferClassBase
{
public:
	ShareBufferClassBase(int count, const char *name, int flags);
	virtual ~ShareBufferClassBase();

protected:
	int field04;
	int field08;
	void *Array;
	int Count;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
class TexBufferClass : public ShareBufferClassBase
{
public:
	TexBufferClass(int count, const char *name);
};

// ??0TexBufferClass@@QAE@HPBD@Z
TexBufferClass::TexBufferClass(int count, const char *name)
	: ShareBufferClassBase(count, name, 0)
{
	memset(Array, 0, (unsigned)Count * 4u);
}
