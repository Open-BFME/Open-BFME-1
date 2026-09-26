// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: the vector<ParticleSysBoneInfo> internals -- _M_clear at
// 0x000A8170, the const-source __copy at 0x000A78A0, _M_allocate_and_copy at
// 0x000A7E00 and the non-const __copy at 0x0036D980. Each name was parked on
// its own 5-byte thunk.
//
// The element is eight bytes: the stride the copy loops step by, and the
// divide-by-eight the size arithmetic carries. What fills it is an AsciiString
// and a pointer -- the copy calls StringBase<char>::set once per element and
// moves the second dword, and the clear calls releaseBuffer once.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Only the two members these bodies reach.
#include "string_base.h"

#include "ascii_string.h"

class ParticleSystemTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ParticleSysBoneInfo
{
	AsciiString boneName;
	ParticleSystemTemplate *particleSystemTemplate;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// The same eight-byte shape: one AsciiString and one dword.
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
		AsciiString subObjName;
		int hide;
	};
};

void BfmeHideShowSubObjInfoVectorAnchor(_STL::vector<ModelConditionInfo::HideShowSubObjInfo> &out, const _STL::vector<ModelConditionInfo::HideShowSubObjInfo> &in)
{
	out = in;
	out.erase(out.begin());
}

void BfmeParticleSysBoneInfoVectorAnchor(_STL::vector<ParticleSysBoneInfo> &out, const _STL::vector<ParticleSysBoneInfo> &in)
{
	out = in;
	out.erase(out.begin());
}
