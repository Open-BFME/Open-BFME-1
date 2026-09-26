// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the helper at retail 0x008667A0, 24 bytes. The body carried only
// a machine byte-dump row; the pin naming it went in with peerStopGame at
// 0x00857E50, which calls it on the peer when the field at +0x398 is set.
//
// All it does is hand the pointer at +0xAF0 to _qr2_send_statechanged, and
// nothing at all when that pointer is null. The compiler writes the field back
// over its own argument slot and leaves through a jump, because the callee
// takes exactly the one argument this function was given.

class Rva00866770Owner
{
public:
	char m_bfmeHeadA[0xAF0];
	void *m_bfmeAF0;					// +0xAF0
};

extern "C" void qr2_send_statechanged(void *record);		// retail 0x00857030

// ?Rva008667A0@@YAXPAVRva00866770Owner@@@Z
void Rva008667A0(Rva00866770Owner *peer)
{
	void *record = peer->m_bfmeAF0;

	if (record)
		qr2_send_statechanged(record);
}
