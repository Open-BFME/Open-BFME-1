extern "C" unsigned char bfmeInfoDIF[];

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

// bfmeGoDIF's own mangled name carries this type, so the receiver stays
// spelled BfmeThingDIF.
class BfmeThingDIF
{
public:
	void bfmeOneDIF(void *p);
};

void *__stdcall bfmeAllocDIF(unsigned int size);

void bfmeGoDIF(void *spare, BfmeThingDIF *self)
{
	MultiIniFieldParse *parse = reinterpret_cast<MultiIniFieldParse *>(self);
	self->bfmeOneDIF(bfmeAllocDIF(8));
	parse->add(reinterpret_cast<const FieldParse *>(bfmeInfoDIF), 0);
}
