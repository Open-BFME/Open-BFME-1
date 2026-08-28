// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<PlayerTemplate>'s destructor, retail 0x000E3D80, 171
// bytes. The name was parked on a 5-byte incremental-link thunk that jumps
// here.
//
// STLport's own destructor out of the real header: destroy every element, then
// hand the buffer back. The element stride is 0x124, which is what sizes
// PlayerTemplate here, and its destructor stays a call through the ILT at
// 0x000181CE.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	PlayerTemplate(const PlayerTemplate &other);
	~PlayerTemplate();					// ILT 0x000181CE

private:
	char m_bfmeBody[0x124];					// the stride the element loop steps by
};

void BfmePlayerTemplateVectorAnchor(void)
{
	_STL::vector<PlayerTemplate> templates;
}

void BfmePlayerTemplateVectorInsertAnchor(_STL::vector<PlayerTemplate> &v, const PlayerTemplate &value)
{
	v.insert(v.begin(), value);
}
