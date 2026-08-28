// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<ModelConditionInfo::HideShowSubObjInfo>::_M_insert_overflow,
// retail 0x006A3DB0, 306 bytes.
//
// The element is the eight-byte one the copy loop at 0x0033A990 already
// measured -- an AsciiString and a dword -- and as with the other overflows it
// is modelled with an out-of-line copy constructor and no destructor, since
// this body copies but never destroys.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
		HideShowSubObjInfo(const HideShowSubObjInfo &other);

		char m_bfmeBody[8];
	};
};

void BfmeHideShowSubObjInfoVectorInsertAnchor(_STL::vector<ModelConditionInfo::HideShowSubObjInfo> &v, const ModelConditionInfo::HideShowSubObjInfo &value)
{
	v.insert(v.begin(), value);
}
