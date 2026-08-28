// cl: /EHsc
// stlport
// Open-BFME: vector<W3DAnimationInfo>::_M_clear, retail 0x003B0E90, 81
// bytes.  The generated shape row is retired here after the element identity
// was confirmed by W3DModelDraw's animation vector and its real destructor.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	~W3DAnimationInfo();

private:
	char m_bfmeBody[16];
};

void BfmeW3DAnimationInfoVectorClearAnchor(
	_STL::vector<W3DAnimationInfo> &out,
	const _STL::vector<W3DAnimationInfo> &in)
{
	out = in;
}
