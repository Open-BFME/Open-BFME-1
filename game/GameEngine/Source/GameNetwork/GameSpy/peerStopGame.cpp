// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: peerStopGame, retail 0x00857E50, 65 bytes. The body carried only
// a machine byte-dump row; the symbols.csv pin names it from
// PeerThreadClass::stopHostingAlready, which calls it on the peer.
//
// The word at +0xB44 is cleared, one cdecl helper runs on the peer, and then
// the pointer at +0xAF0 decides whether anything else happens at all. When it
// is set, the field at +0x398 picks between two more helpers: the one at
// 0x008667A0 when it is set, and _piStopReporting when it is not. That second
// address is also the guarded release the ledger carries as Rva00866770, one of
// the seven bodies in R3GuardedReleaseAndClear.cpp -- the one that frees the
// very field at +0xAF0 this branch was taken on.
//
// The peer is pushed once, ahead of the branch, because both arms take it.

class Rva00866770Owner
{
public:
	char m_bfmeHeadA[0x398];
	void *m_bfme398;					// +0x398
	char m_bfmeHeadB[0xAF0 - 0x39C];
	void *m_bfmeAF0;					// +0xAF0
	char m_bfmeHeadC[0xB44 - 0xAF4];
	int m_bfmeB44;						// +0xB44
};

void Rva00863C00(Rva00866770Owner *peer);			// retail 0x00863C00
void Rva008667A0(Rva00866770Owner *peer);			// retail 0x008667A0

extern "C" void piStopReporting(Rva00866770Owner *peer);	// retail 0x00866770

// _peerStopGame
extern "C" void peerStopGame(Rva00866770Owner *peer)
{
	peer->m_bfmeB44 = 0;

	Rva00863C00(peer);

	if (peer->m_bfmeAF0)
	{
		if (peer->m_bfme398)
			Rva008667A0(peer);
		else
			piStopReporting(peer);
	}
}
