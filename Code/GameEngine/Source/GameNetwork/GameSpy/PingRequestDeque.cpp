// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<PingRequest>::_M_push_back_aux_v (236B at 0x00660750) and
// its PingResponse twin (236B at 0x00660880). Both names were parked on 5-byte
// thunks, at 0x0002F6A3 and 0x0003C650.
//
// STLport's own body out of the real header: take a copy of the element,
// reserve one more block at the back, construct into it and advance the
// cursor, all under the frame the copy's destructor needs.
//
// The element's shape is in that copy. It opens with basic_string<char>'s copy
// constructor over the whole object's front and then moves two dwords from
// +0x0C and +0x10, which is a twelve-byte STLport string followed by two ints
// -- twenty bytes, exactly the temporary the frame reserves.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <string>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PingThread.h
class PingRequest
{
	_STL::string m_bfmeText;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PingThread.h
class PingResponse
{
	_STL::string m_bfmeText;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

void BfmePingRequestDequeAnchor(_STL::deque<PingRequest> &d, const PingRequest &value)
{
	d.push_back(value);
}

void BfmePingResponseDequeAnchor(_STL::deque<PingResponse> &d, const PingResponse &value)
{
	d.push_back(value);
}
