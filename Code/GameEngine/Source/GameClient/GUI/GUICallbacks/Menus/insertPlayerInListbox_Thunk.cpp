// cl: /DNDEBUG /MD /EHsc
// BFME's lobby displays the base player name with the preorder and rank icons.

typedef int Int;
typedef bool Bool;

template <typename T>
inline const T &min(const T &left, const T &right)
{
	return left < right ? left : right;
}

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);

protected:
	~StringBase();
	void releaseBuffer();

	void *m_data;
};

class AsciiString
{
protected:
	void *m_data;
};

class BFMERetailAsciiString : public AsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
	public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	void translate(const AsciiString &text);
};

class PlayerInfo
{
};

class GameWindow
{
};

class Image
{
public:
	char m_prefix[0x24];
	Int m_imageWidth;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class GameSpyInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4A();
	virtual void slot4B();
	virtual void slot4C();
	virtual void slot4D();
	virtual void slot4E();
	virtual void slot4F();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual Bool didPlayerPreorder(Int profileID) const;
};

extern GameSpyInfo *TheGameSpyInfo;
extern MappedImageCollection *TheMappedImageCollection;
extern GameWindow *listboxLobbyPlayers;

Int GadgetListBoxGetColumnWidth(GameWindow *listbox, Int column);
Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	Int row, Int column, Int width, Int height, Bool overwrite, Int color);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite);
const Image *LookupSmallRankImage(Int side, Int rankPoints);

struct BFMEPlayerInfoLayout
{
	char m_prefix[4];
	AsciiString m_baseName;
	char m_fields08[12];
	Int m_profileID;
	char m_fields18[4];
	Int m_rankPoints;
	char m_fields20[12];
	Int m_side;
};

// ?insertPlayerInListbox@@YAHABVPlayerInfo@@H@Z
static Int insertPlayerInListbox(const PlayerInfo &info, Int color)
{
	const BFMEPlayerInfoLayout &player =
		*reinterpret_cast<const BFMEPlayerInfoLayout *>(&info);
	UnicodeString uStr;
	uStr.translate(player.m_baseName);

	Int currentRank = player.m_rankPoints;
	Int currentSide = player.m_side;
	Bool isPreorder = TheGameSpyInfo->didPlayerPreorder(player.m_profileID);

	const Image *preorderImg;
	{
		BFMERetailAsciiString imageName("OfficersClubsmall");
		preorderImg = TheMappedImageCollection->findImageByName(imageName);
	}
	Int w = preorderImg ? preorderImg->m_imageWidth : 10;
	Int oldW = w;
	w = min(GadgetListBoxGetColumnWidth(listboxLobbyPlayers, 0), oldW);
	Int h = w;
	if (!isPreorder)
		preorderImg = 0;

	const Image *rankImg = LookupSmallRankImage(currentSide, currentRank);
	Int index = GadgetListBoxAddEntryImage(
		listboxLobbyPlayers, preorderImg, -1, 0, w, h, true, -1);
	GadgetListBoxAddEntryImage(
		listboxLobbyPlayers, rankImg, index, 1, w, h, true, -1);
	GadgetListBoxAddEntryText(
		listboxLobbyPlayers, uStr, color, index, 2, true);
	return index;
}

__declspec(noinline) Int insertPlayerInListboxAnchor(const PlayerInfo &info, Int color)
{
	return insertPlayerInListbox(info, color);
}
