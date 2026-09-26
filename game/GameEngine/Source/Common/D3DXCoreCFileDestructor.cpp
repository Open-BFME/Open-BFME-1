// cl: /O1
// The archive-derived Close member immediately precedes this destructor; the
// -1 handle test is the ownership guard that makes its tail call conditional.

namespace D3DXCore {
class CFile
{
public:
	~CFile();
	long Close();

private:
	int m_handle;
};

CFile::~CFile()
{
	if ( m_handle != -1 )
		Close();
}
}
