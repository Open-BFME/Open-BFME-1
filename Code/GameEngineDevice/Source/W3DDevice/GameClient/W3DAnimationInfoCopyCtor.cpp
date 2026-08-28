// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DAnimationInfo@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp

// W3DAnimationInfo's copy constructor, retail 0x00783D90.
//
// The whole body is a two-iteration loop moving eight bytes an iteration, so
// the class is an array of two eight-byte entries and nothing else. The loop
// is what says the entry is a CLASS: an array of PODs would be copied
// straight-line, and it is MSVC's elementwise array copy that walks the source
// in edx and the destination in esi with the first dword reached through the
// this-minus-source displacement it computed once.
//
// The constructor itself is not written here. It is the compiler's - a
// user-written one cannot copy an array member at all - so the class declares
// none and a helper below forces it to be emitted.

struct BfmeW3DAnimationInfoEntry
{
	BfmeW3DAnimationInfoEntry( const BfmeW3DAnimationInfoEntry &that )
	{
		m_00 = that.m_00;
		m_04 = that.m_04;
	}

	unsigned int m_00;
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	W3DAnimationInfo();

private:
	BfmeW3DAnimationInfoEntry m_entries[ 2 ];
};

// ??0W3DAnimationInfo@@QAE@ABV0@@Z is the compiler's; this is only here to
// make it emit one.
W3DAnimationInfo bfmeCopyW3DAnimationInfo( const W3DAnimationInfo &that )
{
	return that;
}
