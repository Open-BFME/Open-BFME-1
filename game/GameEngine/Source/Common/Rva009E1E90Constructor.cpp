extern "C" const void *bfmeVftPipe[];
#pragma comment(linker, "/alternatename:_bfmeVftPipe=??_7Pipe@@6B@")

struct Rva009E1E90Owner
{
	void *vftable;
	unsigned int field4;
	unsigned int field8;

	Rva009E1E90Owner();
};

Rva009E1E90Owner::Rva009E1E90Owner()
	: vftable(reinterpret_cast<void *>(bfmeVftPipe)), field4(0), field8(0)
{
}
