// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0092BAA0 is the TexBufferClass copy constructor: it forwards the
// source through the ShareBufferClass<Vector2> copy constructor at
// 0x00929EA0 (BfmeOwnVVE in BfmeConv1665.cpp), installs vtable 0x0113C340,
// and returns this (mov eax,esi idiom). The owner is identified by the
// installed vtable, shared with the (int, name) constructor at 0x0092BA60.

// Retail installs vtable 0x0113C340, whose linker name is ??_7TexBufferClass@@6B@
// (targets/game/reverse/dir32_addresses.csv). The extern binds the object file
// to that exact symbol, so no stand-in name or linker alias is needed.
extern "C" const void *__identifier("??_7TexBufferClass@@6B@")[];

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
	*(unsigned int *)this = (unsigned int)__identifier("??_7TexBufferClass@@6B@");
}
