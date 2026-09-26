// cl: /O1
// The archive-derived constructor identity and single zeroing store establish
// that the lock volume begins with one scalar lock state.

namespace D3DXTex {
class CLockVolume
{
public:
	CLockVolume();

private:
	int m_lockState;
};

CLockVolume::CLockVolume()
{
	m_lockState = 0;
}
}
