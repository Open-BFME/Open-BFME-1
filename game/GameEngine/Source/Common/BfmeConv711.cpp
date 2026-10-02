extern "C" unsigned char bfmeInfoDIH[];

struct FieldParse;

// The register call at 0x00850920 is MultiIniFieldParse::add, which retail's
// own INI.h declares as void add(const FieldParse *f, unsigned int e).
// No game header carries a body for MultiIniFieldParse, so the TU-scoped
// declaration below follows W3DModelDrawModuleData_buildFieldParse.cpp.
class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extraOffset);
};

// bfmeGoDIH's own mangled name carries this type, so the receiver stays
// spelled BfmeThingDIH.
class BfmeThingDIH
{
public:
	void bfmeOneDIH(void *p);
};

void *__stdcall bfmeAllocDIH(unsigned int size);

void bfmeGoDIH(void *spare, BfmeThingDIH *self)
{
	MultiIniFieldParse *parse = reinterpret_cast<MultiIniFieldParse *>(self);
	self->bfmeOneDIH(bfmeAllocDIH(8));
	parse->add(reinterpret_cast<const FieldParse *>(bfmeInfoDIH), 0);
}
