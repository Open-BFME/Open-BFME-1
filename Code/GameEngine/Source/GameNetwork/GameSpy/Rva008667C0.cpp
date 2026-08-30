// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the helper at retail 0x008667C0, 45 bytes, the sibling of
// Rva008667A0.cpp next door. It gives each of the peer's two query records a
// think, skipping either one that is null. The second call is a tail jump: the
// compiler writes the record back over the incoming argument slot because the
// callee takes exactly the one argument this function was given.

class Rva008667C0Owner
{
public:
	char m_bfmeHeadA[0xAF0];
	void *m_bfmeAF0;					// +0xAF0
	char m_bfmeHeadB[0x1EF4 - 0xAF4];
	void *m_bfme1EF4;					// +0x1EF4
};

extern "C" void qr2_think(void *record);			// retail 0x008570F0

// ?Rva008667C0@@YAXPAVRva008667C0Owner@@@Z
void Rva008667C0(Rva008667C0Owner *peer)
{
	void *first = peer->m_bfmeAF0;

	if (first)
		qr2_think(first);

	void *second = peer->m_bfme1EF4;

	if (second)
		qr2_think(second);
}
