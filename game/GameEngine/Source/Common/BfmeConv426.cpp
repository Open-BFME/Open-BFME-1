// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The list at +0x20C is the PeerThreadClass staging-server map of
// GameNetwork/GameSpy/Thread/PeerThreadRemoveServerFromMap.cpp
// (std::map<Int, Gen_t_00644050_p4pod>); this body is its inlined clear(),
// whose one call is the matched _Rb_tree::_M_erase at 0x00644050 (ILT 0x4A91C).
#include <map>

struct _SBServer;
struct Gen_t_00644050_p4pod
{
	_SBServer *value;
};

class BfmeListAVA : public std::map<int, Gen_t_00644050_p4pod>
{
};

class BfmeThingAVA
{
public:
	void bfmeGoAVA();
	unsigned char m_bfmeHead[0x20c];
	BfmeListAVA m_bfmeList;
};

void BfmeThingAVA::bfmeGoAVA()
{
	m_bfmeList.clear();
}
