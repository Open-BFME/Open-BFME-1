// cl: /O1
extern "C" unsigned char bfmeVftUE[];

void bfmeFreeUE(void *what);

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

class BfmeThingUE
{
public:
	void *bfmeKillUE(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUE::bfmeKillUE(int flags)
{
	m_bfmeVft = bfmeVftUE;
	reinterpret_cast<D3DXShader::CShaderProgram *>(this)->D3DXShader::CShaderProgram::~CShaderProgram();
	if ((flags & 1) != 0)
		bfmeFreeUE(this);
	return this;
}
