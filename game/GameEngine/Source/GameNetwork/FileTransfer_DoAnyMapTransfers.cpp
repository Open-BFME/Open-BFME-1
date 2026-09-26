// cl: /DNDEBUG /MD /GX

class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *str);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class GameSlot
{
public:
	bool isHuman() const;
	bool hasMap() const { return m_hasMap; }

private:
	char m_pad[9];
	bool m_hasMap;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int slot) const;
	AsciiString getMap() const;
	int getMapContentsMask() const { return m_mapContentsMask; }

private:
	char m_pad[0x48];
	int m_mapContentsMask;
};

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

extern "C" bool doFileTransfer(AsciiString filename, int mask);

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
	if (TheGameInfo->getMapContentsMask() & 0x200)
		ok = false;

	if (ok && (TheGameInfo->getMapContentsMask() & 2))
		ok = doFileTransfer(GetPreviewFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 4))
		ok = doFileTransfer(GetINIFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 8))
		ok = doFileTransfer(GetStrFileFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 16))
		ok = doFileTransfer(GetSoloINIFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 32))
		ok = doFileTransfer(GetAssetUsageFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 64))
		ok = doFileTransfer(GetReadmeFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 128))
		ok = doFileTransfer(GetArtPreviewFromMap(game->getMap()), mask);
	if (ok && (TheGameInfo->getMapContentsMask() & 256))
		ok = doFileTransfer(GetPicPreviewFromMap(game->getMap()), mask);
	if (ok)
		ok = doFileTransfer(game->getMap(), mask);

	Rva0050FE20();
	return ok;
}
