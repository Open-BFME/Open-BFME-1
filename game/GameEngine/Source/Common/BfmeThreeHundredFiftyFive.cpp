// cl: /O2 /Os
// Retail 0x01158598 is the d3dx9 archive vftable ??_7CPSProgram@D3DXShader@@6B@; the stand-in name resolved nothing.
extern "C" const char __identifier("??_7CPSProgram@D3DXShader@@6B@")[];


// The base destructor this deleting destructor calls is at 0x00AB8350, which
// d3dx9's archive proves is D3DXShader::CShaderProgram::~CShaderProgram
// (vendored=d3dx9-summer2003). Declared here, defined by the archive.
namespace D3DXShader
{
class CShaderProgram
{
public:
	virtual ~CShaderProgram();
};
}

class BfmeThingUD
{
public:
	void *bfmeKillUD(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUD::bfmeKillUD(int flags)
{
	m_bfmeVft = (void *)__identifier("??_7CPSProgram@D3DXShader@@6B@");
	reinterpret_cast<D3DXShader::CShaderProgram *>(this)->D3DXShader::CShaderProgram::~CShaderProgram();
	if ((flags & 1) != 0)
		::operator delete(this);
	return this;
}
