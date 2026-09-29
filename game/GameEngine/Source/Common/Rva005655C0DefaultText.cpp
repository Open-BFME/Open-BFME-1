// Open-BFME5: clean C++ conversion of the default-player-text copier.

struct Rva005655C0Player
{
	unsigned char m_padding[0x28];
	char *m_nameStorage;
};

struct Rva005655C0PlayerList
{
	unsigned char m_padding[0x0C];
	Rva005655C0Player *m_localPlayer;
};

extern Rva005655C0PlayerList *g_rva005655C0PlayerList;
extern const char Rva006A16B0Empty[];

void __cdecl rva005655C0CopyDefaultText(void *value, char *output,
	unsigned char preserveText)
{
	if (output == 0) {
		return;
	}

	if (!preserveText) {
		output[1] = 0;
		output[0] = 0;
	}

	if (value == 0 && !preserveText && g_rva005655C0PlayerList != 0 &&
		g_rva005655C0PlayerList->m_localPlayer != 0) {
		char *storage = g_rva005655C0PlayerList->m_localPlayer->m_nameStorage;
		const char *text = storage != 0 ? storage + 8 :
			Rva006A16B0Empty;
		char character;
		do {
			character = *text++;
			*output++ = character;
		} while (character != 0);
	}
}
