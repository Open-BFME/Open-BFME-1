// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piSBFreeHostServer, retail 0x00864FB0, 38 bytes,
   reconstructed from the retail bytes rather than transcribed: the peer/
   module is not in the carrier this directory's siblings explain, so the
   declarations here are local as theirs are.

   The connection is the PEER handle itself and the hosted server pointer sits
   at its +0xB50. The free takes the address of that field, not its value --
   the body computes `connection + 0xB50` once and passes it -- and the field
   is cleared afterwards. */

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad0[0xb40];
	int hosting;					/* +0xB40 */
	int playing;					/* +0xB44 */
	unsigned char padb48[0xb50 - 0xb48];
	void *hostServer;				/* +0xB50 */
	int ready;					/* +0xB54 */
} piConnection;

void SBServerFree(void **server);
int piStartReporting(PEER peer, int socket, unsigned short port);
void piStopReporting(PEER peer);
void piSetLocalFlags(PEER peer);

void piSBFreeHostServer(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(connection->hostServer)
	{
		SBServerFree(&connection->hostServer);
		connection->hostServer = 0;
	}
}

int piStartHosting(PEER peer, int socket, unsigned short port)
{
	piConnection *connection = (piConnection *)peer;

	if(connection->hosting)
		return 0;

	connection->hosting = 1;

	if(!piStartReporting(peer, socket, port))
		return 0;

	return 1;
}

void piStopHosting(PEER peer, int stopReporting)
{
	piConnection *connection = (piConnection *)peer;

	if(stopReporting)
		piStopReporting(peer);

	if(!connection->hosting)
		return;

	connection->hosting = 0;
	connection->playing = 0;
	connection->ready = 0;

	piSetLocalFlags(peer);
}
