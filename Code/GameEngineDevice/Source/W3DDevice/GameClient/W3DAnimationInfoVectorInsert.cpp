// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<W3DAnimationInfo>::_M_insert_overflow, retail 0x00788030,
// 308 bytes. The body carried no ledger row; its name sat on a 5-byte thunk.
//
// The element is sixteen bytes -- not the reference's twenty -- and it needs
// exactly two things from the model: that size, and an out-of-line copy
// constructor, which is the four calls between the allocation and the release.
//
// It must NOT be given a destructor here. The element does have one in the
// game -- its first member is an AsciiString -- but this body never destroys
// anything, and modelling the destructor makes MSVC add a destroy loop retail
// does not have, 38 bytes short of the real body.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	W3DAnimationInfo(const W3DAnimationInfo &other);

private:
	char m_bfmeBody[0x10];
};

void BfmeW3DAnimationInfoVectorInsertAnchor(_STL::vector<W3DAnimationInfo> &v, const W3DAnimationInfo &value)
{
	v.insert(v.begin(), value);
}
