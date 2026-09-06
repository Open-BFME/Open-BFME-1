// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatTranslateNickA, retail 0x00860690, 83 bytes.
   The 2007 SDK source keeps a namespace extension only when it matches the
   end of the nickname, then returns the shortened nickname. */

unsigned int __cdecl strlen(const char *string);
__declspec(dllimport) int __cdecl strcasecmp(const char *left,
	const char *right);

const char *chatTranslateNickA(char *nick, const char *extension)
{
	int nickLen;
	int extensionLen;

	nickLen = (int)strlen(nick);
	extensionLen = (int)strlen(extension);

	if((extensionLen < nickLen) &&
		(strcasecmp(nick + nickLen - extensionLen, extension) == 0))
	{
		nick[nickLen - extensionLen] = '\0';
		return nick;
	}

	return 0;
}
