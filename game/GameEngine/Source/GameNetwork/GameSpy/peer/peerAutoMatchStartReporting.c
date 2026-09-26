// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

#include <string.h>

typedef int PEERBool;

typedef struct qr2_implementation
{
	unsigned char pad_0000[0xC4];
	PEERBool read_socket;
} qr2_implementation;

typedef qr2_implementation *qr2_t;

typedef struct piOperation
{
	unsigned char pad_0000[0x2C];
	int socket;
	unsigned short port;
	unsigned char pad_0032[2];
	PEERBool socketClose;
} piOperation;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x60];
	char title[0x20];
	unsigned char pad_0080[0xAF4 - 0x80];
	char qrSecretKey[0x40];
	PEERBool natNegotiate;
	unsigned char pad_0B38[0x1EF0 - 0xB38];
	piOperation *autoMatchOperation;
	qr2_t autoMatchReporting;
	unsigned char pad_1EF8[8];
	PEERBool autoMatchQRFailed;
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

void piQRServerKeyCallback(void);
void piQRPlayerKeyCallback(void);
void piQRTeamKeyCallback(void);
void piQRKeyListCallback(void);
void piQRCountCallback(void);
void piQRAddErrorCallback(void);

extern __declspec(dllimport) char *__cdecl strzcpy(char *dest,
	const char *source, unsigned int len);
extern __declspec(dllimport) char *__cdecl strzcat(char *dest,
	const char *source, unsigned int len);

PEERBool piStartAutoMatchReporting(PEER peer)
{
	piOperation *operation;
	char autoMatchTitle[0x20];
	int result;

	if (peer->autoMatchReporting)
	{
		qr2_shutdown(peer->autoMatchReporting);
		peer->autoMatchReporting = 0;
	}

	operation = peer->autoMatchOperation;
	strzcpy(autoMatchTitle, peer->title, sizeof(autoMatchTitle));
	autoMatchTitle[sizeof(autoMatchTitle) - 1] = '\0';
	strzcat(autoMatchTitle, "am",
		sizeof(autoMatchTitle) - strlen(autoMatchTitle));
	autoMatchTitle[sizeof(autoMatchTitle) - 1] = '\0';

	if (operation->socket == -1)
	{
		result = qr2_initA(&peer->autoMatchReporting, 0, 6500,
			autoMatchTitle, peer->qrSecretKey, 1, peer->natNegotiate,
			piQRServerKeyCallback, piQRPlayerKeyCallback,
			piQRTeamKeyCallback, piQRKeyListCallback,
			piQRCountCallback, piQRAddErrorCallback, peer);
	}
	else
	{
		result = qr2_init_socketA(&peer->autoMatchReporting,
			operation->socket, operation->port, autoMatchTitle,
			peer->qrSecretKey, 1, peer->natNegotiate,
			piQRServerKeyCallback, piQRPlayerKeyCallback,
			piQRTeamKeyCallback, piQRKeyListCallback,
			piQRCountCallback, piQRAddErrorCallback, peer);

		if (operation->socketClose)
		{
			operation->socketClose = 0;
			peer->autoMatchReporting->read_socket = 1;
		}
	}

	peer->autoMatchQRFailed = (result == 0);
	if (result != 0)
		return 0;

	return 1;
}
