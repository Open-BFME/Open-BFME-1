// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0092BAA0 is the TexBufferClass copy constructor: it forwards the
// source through the ShareBufferClass<Vector2> copy constructor at
// 0x00929EA0 (BfmeOwnVVE in BfmeConv1665.cpp), installs vtable 0x0113C340,
// and returns this (mov eax,esi idiom). The owner is identified by the
// installed vtable, shared with the (int, name) constructor at 0x0092BA60.

extern "C" const void *bfmeVftTexBufferClass[];
#pragma comment(linker, "/alternatename:_bfmeVftTexBufferClass=??_7TexBufferClass@@6B@")

class BfmeOwnVVE
{
public:
	BfmeOwnVVE(const BfmeOwnVVE &other);
};

class TexBufferClass : public BfmeOwnVVE
{
public:
	TexBufferClass(const TexBufferClass &other);
};

TexBufferClass::TexBufferClass(const TexBufferClass &other)
	: BfmeOwnVVE(other)
{
	*(unsigned int *)this = (unsigned int)bfmeVftTexBufferClass;
}
