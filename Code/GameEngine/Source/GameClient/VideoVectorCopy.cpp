// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the vector<Video> copy loop, retail 0x00755100, 83 bytes. The
// name was parked on a 5-byte thunk.
//
// The element is twelve bytes and its assignment is one call, into
// basic_string<char>'s _M_assign_dispatch -- which is what a struct holding
// nothing but an STLport string assigns to.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/VideoPlayer.h
struct Video
{
	_STL::string m_bfmeName;
};

void BfmeVideoVectorAnchor(_STL::vector<Video> &v)
{
	v.erase(v.begin());
}

void BfmeVideoVectorInsertAnchor(_STL::vector<Video> &v, const Video &value)
{
	v.insert(v.begin(), value);
}
