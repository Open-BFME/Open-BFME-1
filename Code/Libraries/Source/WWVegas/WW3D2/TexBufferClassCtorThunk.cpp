// cl: /DNDEBUG /MD /GX- /O2 /Ob2

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
