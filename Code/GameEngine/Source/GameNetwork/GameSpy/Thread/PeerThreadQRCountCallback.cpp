// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
//
// Open-BFME: PeerThread's QR count callback, retail 0x0064E5B0, 44 bytes.
//
// The retail PeerCallbacks table is assembled in Thread_Function at 0x0064FB90:
// its qrCount slot (+0x60, immediately after the proven qrKeyList slot +0x5C)
// receives 0x0064E5B0.  The reference PeerThread.cpp names this callback
// QRCountCallback and uses this exact (PEER, qr2_key_type, void *) ABI.
//
// This is a TU-local view because the retail callback reads m_isHosting at
// +0xAC, while the BFME PeerThreadClass reconstruction in PeerThread.cpp has
// later members at a different offset.  Only that byte and the existing
// stopHostingAlready callee are required by this body; the padding is not a
// claim about the rest of the class layout.

typedef bool Bool;
typedef void *PEER;

typedef enum
{
	key_server,
	key_player,
	key_team
} qr2_key_type;

class PeerThreadClass
{
public:
	Bool isHosting( void ) { return m_isHosting; }
	void stopHostingAlready( PEER peer );

private:
	unsigned char m_unreconstructed_00[0xAC];
	Bool m_isHosting;                                      ///< +0xAC
};

// ?QRCountCallback@@YAHPAXW4qr2_key_type@@0@Z
static int QRCountCallback( PEER peer, qr2_key_type type, void *param )
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (t)
	{
		if (!t->isHosting())
			t->stopHostingAlready(peer);
		// BFME retail returns a fixed eight for player keys.
		if (type == key_player)
			return 8;
	}
	return 0;
}

// Keep the callback's internal-linkage symbol in the object for the retail
// row; the table in Thread_Function is the runtime registration evidence.
typedef int (*QRCountCallbackType)( PEER, qr2_key_type, void * );
QRCountCallbackType PeerThread_getQRCountCallback( void )
{
	return QRCountCallback;
}
