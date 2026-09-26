// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: peerParseQuery, retail 0x00857570, 34 bytes.
//
// The query record is whichever of the peer's two slots is set. When one is,
// the function overwrites its own first argument and tail-jumps into
// qr2_parse_queryA, which is what lets MSVC drop the frame entirely.
//
// The bare `ret` sits AFTER that jump, not before it: the null path falls off
// the end of the function rather than executing a `return 0;`. Written with an
// explicit `return 0;` MSVC lays the `ret` out first and the jump second, two
// bytes different -- so the missing return is load-bearing, not an oversight.

struct sockaddr;

extern "C" int qr2_parse_queryA(void *qrec, char *query, int len, struct sockaddr *sender);

struct PeerRva00857570
{
	unsigned char m_unmodelled_0000[0xaf0];
	void *m_primaryQueryRecord;			// peer+0x0AF0
	unsigned char m_unmodelled_0af4[0x1400];
	void *m_secondaryQueryRecord;		// peer+0x1EF4
};

int peerParseQuery(void *peer, char *query, int len, struct sockaddr *sender);

int peerParseQuery(void *peer, char *query, int len, struct sockaddr *sender)
{
	PeerRva00857570 *p = (PeerRva00857570 *)peer;
	void *qrec = p->m_primaryQueryRecord;

	if (qrec != 0 || (qrec = p->m_secondaryQueryRecord) != 0)
		return qr2_parse_queryA(qrec, query, len, sender);
}
