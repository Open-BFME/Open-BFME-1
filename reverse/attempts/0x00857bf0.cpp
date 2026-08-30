// _peerGetPlayerFlagsA
// partial score=0.9 date=2026-08-30
int peerGetPlayerFlagsA(PEER peer, const char *nick, int roomType, int *flags)
{
	piConnection *connection = (piConnection *)peer;
	piPlayer *player;

	if (!flags)
		return 0;
	if (connection->inRoom[roomType])
	{
		player = piGetPlayer(peer, nick);
		if (player && player->inRoom[roomType])
		{
			*flags = player->flags[roomType];
			return 1;
		}
	}

	return 0;
}
