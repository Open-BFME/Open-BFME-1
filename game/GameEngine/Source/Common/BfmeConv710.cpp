extern "C" unsigned char bfmeInfoDIG[];

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

// bfmeGoDIG's own mangled name carries this type, so the receiver stays
// spelled BfmeThingDIG.
class BfmeThingDIG
{
public:
	void bfmeOneDIG(void *p);
};

void *__stdcall bfmeAllocDIG(unsigned int size);

void bfmeGoDIG(void *spare, BfmeThingDIG *self)
{
	MultiIniFieldParse *parse = reinterpret_cast<MultiIniFieldParse *>(self);
	self->bfmeOneDIG(bfmeAllocDIG(8));
	parse->add(reinterpret_cast<const FieldParse *>(bfmeInfoDIG), 0);
}
