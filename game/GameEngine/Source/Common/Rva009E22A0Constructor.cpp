extern "C" const void *bfmeVftGenericNode[];
#pragma comment(linker, "/alternatename:_bfmeVftGenericNode=??_7GenericNode@@6B@")

struct Rva009E22A0Owner
{
	void *vftable;
	unsigned int field4;
	unsigned int field8;

	Rva009E22A0Owner();
};

Rva009E22A0Owner::Rva009E22A0Owner()
	: vftable(reinterpret_cast<void *>(bfmeVftGenericNode)), field4(0), field8(0)
{
}
