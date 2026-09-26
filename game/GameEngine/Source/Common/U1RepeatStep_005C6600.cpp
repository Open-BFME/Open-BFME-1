// cl: /DNDEBUG /MD /O2 /Ob2
// cdecl: call U1CallReceiver_005C5BD0::step(0x20) n times, return the receiver.

class U1CallReceiver_005C5BD0
{
public:
	void step( int amount );
};

U1CallReceiver_005C5BD0 *__cdecl bfmeRepeatStep_005C6600( U1CallReceiver_005C5BD0 *p, unsigned n )
{
	unsigned left = n;
	if ( left > 0 )
	{
		U1CallReceiver_005C5BD0 *recv = p;
		do
			recv->step( 0x20 );
		while ( --left );
		return recv;
	}
	return p;
}
