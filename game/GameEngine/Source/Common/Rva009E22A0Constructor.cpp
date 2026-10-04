// Retail stamps the GenericNode vftable (0x01145484, dir32 row
// ??_7GenericNode@@6B@) into this ctor; _bfmeVftGenericNode was a stand-in
// spelling kept alive by a linker alternate-name pragma.  Reference the real
// symbol directly instead.
extern "C" void *__identifier("??_7GenericNode@@6B@")[];

struct Rva009E22A0Owner
{
	void *vftable;
	unsigned int field4;
	unsigned int field8;

	Rva009E22A0Owner();
};

Rva009E22A0Owner::Rva009E22A0Owner()
	: vftable(__identifier("??_7GenericNode@@6B@")), field4(0), field8(0)
{
}
