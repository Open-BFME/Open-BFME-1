// cl: /DNDEBUG /MD /GX

class AsciiString;

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class GameSlot
{
public:
	bool isHuman() const;
	bool hasMap() const { return m_hasMap; }

private:
	char m_pad[9];
	bool m_hasMap;
};

// No authored GameInfo header covers this measured BFME layout. Keep the
// local accessor out of the external GameInfo COMDAT contract.
class GameInfo;
static __forceinline int getMapContentsMask(const GameInfo *game);

class GameInfo
{
public:
	const GameSlot *getConstSlot(int slot) const;
	AsciiString getMap() const;
	friend int getMapContentsMask(const GameInfo *game);

private:
	char m_pad[0x48];
	int m_mapContentsMask;
};

static __forceinline int getMapContentsMask(const GameInfo *game)
{
	return game->m_mapContentsMask;
}

extern GameInfo *TheGameInfo;

bool _bfme_showMapTransferLoadScreen(void *context);
void Rva0050FE20();

AsciiString GetPreviewFromMap(AsciiString path);
AsciiString GetArtPreviewFromMap(AsciiString path);
AsciiString GetPicPreviewFromMap(AsciiString path);
AsciiString GetINIFromMap(AsciiString path);
AsciiString GetStrFileFromMap(AsciiString path);
AsciiString GetSoloINIFromMap(AsciiString path);
AsciiString GetAssetUsageFromMap(AsciiString path);
AsciiString GetReadmeFromMap(AsciiString path);

bool doFileTransfer(AsciiString filename, int mask);

bool DoAnyMapTransfers(GameInfo *game)
{
	TheGameInfo = game;
	int mask = 0;
	for (int i = 1; i < 8; ++i)
	{
		if (TheGameInfo->getConstSlot(i)->isHuman() &&
			!TheGameInfo->getConstSlot(i)->hasMap())
		{
			mask |= 1 << i;
		}
	}

	if (!mask)
		return true;

	_bfme_showMapTransferLoadScreen(game);
	bool ok = true;
	if (getMapContentsMask(TheGameInfo) & 0x200)
		ok = false;

	if (ok && (getMapContentsMask(TheGameInfo) & 2))
		ok = doFileTransfer(GetPreviewFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 4))
		ok = doFileTransfer(GetINIFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 8))
		ok = doFileTransfer(GetStrFileFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 16))
		ok = doFileTransfer(GetSoloINIFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 32))
		ok = doFileTransfer(GetAssetUsageFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 64))
		ok = doFileTransfer(GetReadmeFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 128))
		ok = doFileTransfer(GetArtPreviewFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(TheGameInfo) & 256))
		ok = doFileTransfer(GetPicPreviewFromMap(game->getMap()), mask);
	if (ok)
		ok = doFileTransfer(game->getMap(), mask);

	Rva0050FE20();
	return ok;
}
