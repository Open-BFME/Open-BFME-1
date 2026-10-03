// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// cdecl: call U1CallReceiver_005C5BD0::step(0x20) n times, return the receiver.
// stlport

// Retail reaches the receiver's step through the ILT thunk at 0x0001B77A, whose
// jump targets 0x0005C5BD0: _STL::basic_ostream<char, _STL::char_traits<char> >::
// put (row 127817, game/GameEngine/Source/GameClient/System/FXParticleSystem/
// FXParticleSystemOstreamPut.cpp, which spells the same instantiation).  The
// receiver pointer crosses as that stream type, so the call links; the ledger
// name of this row keeps its own address-derived parameter type, and the cast
// emits no code.
#include <ostream>

class U1CallReceiver_005C5BD0
{
};

typedef _STL::basic_ostream<char, _STL::char_traits<char> > StepReceiverStream;

U1CallReceiver_005C5BD0 *__cdecl bfmeRepeatStep_005C6600( U1CallReceiver_005C5BD0 *p, unsigned n )
{
	unsigned left = n;
	if ( left > 0 )
	{
		U1CallReceiver_005C5BD0 *recv = p;
		do
			((StepReceiverStream *)recv)->put( 0x20 );
		while ( --left );
		return recv;
	}
	return p;
}
