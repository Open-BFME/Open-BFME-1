// Retail vtable 0x011453D0 is Pipe's vftable, i.e. ??_7Pipe@@6B@
// (targets/game/reverse/dir32_addresses.csv, row _bfmeVftPipe).  A class
// vftable has no C++ spelling to take its address, so the declaration spells
// the retail symbol exactly with __identifier and the store below references
// that defining name directly, with no linker alias stand-in.
extern "C" int __identifier("??_7Pipe@@6B@")[];

struct Rva009E1E90Owner
{
	void *vftable;
	unsigned int field4;
	unsigned int field8;

	Rva009E1E90Owner();
};

Rva009E1E90Owner::Rva009E1E90Owner()
	: vftable(reinterpret_cast<void *>(__identifier("??_7Pipe@@6B@"))), field4(0), field8(0)
{
}
