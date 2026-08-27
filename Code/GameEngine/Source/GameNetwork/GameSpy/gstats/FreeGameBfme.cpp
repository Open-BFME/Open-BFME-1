// cl: /DNDEBUG /MD /O2
// BFME retail variant of GameSpy's FreeGame: passing the global game also clears it.

typedef struct statsgame_s
{
	unsigned char pad0[8];
	int usebuckets;
	void *buckets;
	unsigned char pad10[12];
	void *playernums;
	void *teamnums;
} *statsgame_t;

extern statsgame_t g_statsgame;
extern "C" void __cdecl FreeBucketSet(void *);
extern "C" void __cdecl ArrayFree(void *);
extern "C" __declspec(dllimport) void __cdecl free(void *);

extern "C" void __cdecl FreeGame(statsgame_t game)
{
	statsgame_t globalGame = g_statsgame;
	if (game == 0 || game == globalGame)
	{
		game = globalGame;
		g_statsgame = 0;
	}
	if (game == 0)
		return;

	if (game->usebuckets)
	{
		if (game->buckets != 0)
			FreeBucketSet(game->buckets);
		if (game->playernums != 0)
			ArrayFree(game->playernums);
		if (game->teamnums != 0)
			ArrayFree(game->teamnums);
	}
	free(game);
}
