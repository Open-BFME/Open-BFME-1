// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: PeerThread.cpp's QR_TEAM_KEY callback, retail 0x0064E570,
// zh_sweep packet 0064e570.
//
// The reference body ports unchanged -- bail on a null thread pointer, stop
// hosting if we are not hosting, then answer the team query with an empty
// string, since BFME reports no teams either. One offset separates it from
// retail: isHosting() reads the byte at [this+0xAC], where PeerThread.cpp's
// reconstructed PeerThreadClass puts m_isHosting at +0xB0.
//
// Its own TU because that four-byte difference is above m_isHosting in the
// class, so correcting it inside PeerThread.cpp would move every member below
// it and disturb the thirty-two rows that file already lands. Here the class is
// a local stand-in sized to the one offset retail proves, and nothing else in
// the tree sees it.

typedef int Int;
typedef bool Bool;

typedef void *PEER;
typedef void *qr2_buffer_t;

void qr2_buffer_add( qr2_buffer_t buffer, const char *value );

// Only the hosting flag is reconstructed; everything above it is retail's
// spacing, not a claim about what lives there.
class PeerThreadClass
{
public:
	Bool isHosting( void ) { return m_isHosting; }
	void stopHostingAlready( PEER peer );

private:
	unsigned char m_unreconstructed_00[0xAC];
	Bool m_isHosting;										///< +0xAC
};

// ?QRTeamKeyCallback@@YAXPAXHH00@Z
static void QRTeamKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void * param
)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		return;
	}
	if (!t->isHosting())
		t->stopHostingAlready(peer);

	// we don't report teams, so this shouldn't get called
	qr2_buffer_add(buffer, "");
}

// The callback is static and reaches retail only as a registered function
// pointer; this keeps the TU emitting it with the __cdecl frame retail uses.
typedef void (*QRTeamKeyCallbackType)( PEER, int, int, qr2_buffer_t, void * );

QRTeamKeyCallbackType PeerThread_getQRTeamKeyCallback( void )
{
	return QRTeamKeyCallback;
}
