// cl: /EHsc
// stlport
// Open-BFME: vector<ParticleSysBoneInfo>::_M_clear, retail 0x000A8170, 81
// bytes.  The generated shape row is retired here after the element identity
// was confirmed by W3DModelDraw's vector member and the existing destructor.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ParticleSysBoneInfo
{
public:
	~ParticleSysBoneInfo();

private:
	char m_bfmeBody[8];
};

void BfmeParticleSysBoneInfoVectorClearAnchor(
	_STL::vector<ParticleSysBoneInfo> &out,
	const _STL::vector<ParticleSysBoneInfo> &in)
{
	out = in;
}
