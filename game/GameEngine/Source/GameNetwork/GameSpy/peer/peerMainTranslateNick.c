// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

const char *chatTranslateNickA(char *nick, const char *extension);

const char *peerTranslateNickA(char *nick, const char *extension)
{
	return chatTranslateNickA(nick, extension);
}
