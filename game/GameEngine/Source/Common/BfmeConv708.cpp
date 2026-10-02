extern "C" unsigned char bfmeInfoDIE[];

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

// bfmeGoDIE's own mangled name carries this type, so the receiver stays
// spelled BfmeThingDIE. 0x00123690's first register call pushes only the table,
// so that call keeps its own one-argument spelling; respelling it as add would
// make MSVC materialise the default extraOffset and shift every byte after it.
class BfmeThingDIE
{
public:
	void bfmeOneDIE(void *p);
};

void *__stdcall bfmeAllocDIE(unsigned int size);

void bfmeGoDIE(void *spare, BfmeThingDIE *self)
{
	MultiIniFieldParse *parse = reinterpret_cast<MultiIniFieldParse *>(self);
	self->bfmeOneDIE(bfmeAllocDIE(8));
	parse->add(reinterpret_cast<const FieldParse *>(bfmeInfoDIE), 0);
}
