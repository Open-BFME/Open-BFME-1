// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerQR.c */

typedef int PEERBool;

typedef struct qr2_implementation *qr2_t;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x60];
	char title[0x20];
	unsigned char pad_0080[0x9A8 - 0x80];
	int groupID;
	unsigned char pad_09AC[0xAF0 - 0x9AC];
	qr2_t queryReporting;
	char qrSecretKey[0x40];
	PEERBool natNegotiate;
	PEERBool reportingOptions;
	int reportingGroupID;
} PEERConnection;

typedef PEERConnection *PEER;
typedef void (*qr2_callback)(void);

void qr2_shutdown(qr2_t qrec);
int qr2_initA(qr2_t *qrec, const char *ip, int baseport,
	const char *gamename, const char *secretKey, int isPublic,
	int natNegotiate, qr2_callback serverKeyCallback,
	qr2_callback playerKeyCallback, qr2_callback teamKeyCallback,
	qr2_callback keyListCallback, qr2_callback countCallback,
	qr2_callback addErrorCallback, void *userData);
int qr2_init_socketA(qr2_t *qrec, int socket, int boundPort,
	const char *gamename, const char *secretKey, int isPublic,
	int natNegotiate, qr2_callback serverKeyCallback,
	qr2_callback playerKeyCallback, qr2_callback teamKeyCallback,
	qr2_callback keyListCallback, qr2_callback countCallback,
	qr2_callback addErrorCallback, void *userData);
void qr2_register_natneg_callback(qr2_t qrec, qr2_callback callback);
void qr2_register_publicaddress_callback(qr2_t qrec,
	qr2_callback callback);

void piQRServerKeyCallback(void);
void piQRPlayerKeyCallback(void);
void piQRTeamKeyCallback(void);
void piQRKeyListCallback(void);
void piQRCountCallback(void);
void piQRAddErrorCallback(void);
void piQRNatNegotiateCallback(void);
void piQRPublicAddressCallback(void);

PEERBool piStartReporting(PEER peer, int socket, unsigned short port)
{
	int result;

	if (peer->queryReporting)
	{
		qr2_shutdown(peer->queryReporting);
		peer->queryReporting = 0;
	}

	if (socket == -1)
	{
		result = qr2_initA(&peer->queryReporting, 0, 6500,
			peer->title, peer->qrSecretKey, 1, peer->natNegotiate,
			piQRServerKeyCallback, piQRPlayerKeyCallback,
			piQRTeamKeyCallback, piQRKeyListCallback,
			piQRCountCallback, piQRAddErrorCallback, peer);
	}
	else
	{
		result = qr2_init_socketA(&peer->queryReporting, socket, port,
			peer->title, peer->qrSecretKey, 1, peer->natNegotiate,
			piQRServerKeyCallback, piQRPlayerKeyCallback,
			piQRTeamKeyCallback, piQRKeyListCallback,
			piQRCountCallback, piQRAddErrorCallback, peer);
	}

	if (result != 0)
		return 0;

	peer->reportingGroupID = peer->groupID;
	qr2_register_natneg_callback(peer->queryReporting,
		piQRNatNegotiateCallback);
	qr2_register_publicaddress_callback(peer->queryReporting,
		piQRPublicAddressCallback);
	peer->reportingOptions = 0;
	return 1;
}
