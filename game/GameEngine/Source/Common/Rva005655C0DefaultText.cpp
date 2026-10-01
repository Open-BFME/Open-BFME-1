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

// ?ThePlayerList@@3PAVPlayerList@@A -- retail 0x012ED748, defined once in
// Common/RTS/PlayerList.cpp. The view above is this TU's own layout of it.
class PlayerList;
extern PlayerList *ThePlayerList;
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

	if (value == 0 && !preserveText && ((Rva005655C0PlayerList *)ThePlayerList) != 0 &&
		((Rva005655C0PlayerList *)ThePlayerList)->m_localPlayer != 0) {
		char *storage = ((Rva005655C0PlayerList *)ThePlayerList)->m_localPlayer->m_nameStorage;
		const char *text = storage != 0 ? storage + 8 :
			Rva006A16B0Empty;
		char character;
		do {
			character = *text++;
			*output++ = character;
		} while (character != 0);
	}
}
