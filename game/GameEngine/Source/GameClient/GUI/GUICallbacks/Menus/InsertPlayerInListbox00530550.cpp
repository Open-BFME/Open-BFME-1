// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00530550, ZH insertPlayerInListbox twin; owner address-derived (one caller 0x005337E0 via ILT 0x00019141).

#include <map>
#include <string>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef int Color;

template <typename T>
inline const T &rva00530550Min(const T &left, const T &right)
{
	return left < right ? left : right;
}

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

private:
	void releaseBuffer();
};

#include "string_base.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

class GameWindow
{
};

class Image
{
public:
	char m_prefix[0x24];
	Int m_imageWidth;
};

// Retail's singleton is ?TheMappedImageCollection@@3PAVImageCollection@@A: the
// class is ImageCollection. No game header declares it (its Zero Hour
// GameClient/Image.h cannot be used here), so this TU declares the member it
// calls only.
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class GameSpyInfo
{
public:
#define RVA00530550_SLOT(n) virtual void slot##n();
	RVA00530550_SLOT(00) RVA00530550_SLOT(01) RVA00530550_SLOT(02)
	RVA00530550_SLOT(03) RVA00530550_SLOT(04) RVA00530550_SLOT(05)
	RVA00530550_SLOT(06) RVA00530550_SLOT(07) RVA00530550_SLOT(08)
	RVA00530550_SLOT(09) RVA00530550_SLOT(0A) RVA00530550_SLOT(0B)
	RVA00530550_SLOT(0C) RVA00530550_SLOT(0D) RVA00530550_SLOT(0E)
	RVA00530550_SLOT(0F) RVA00530550_SLOT(10) RVA00530550_SLOT(11)
	RVA00530550_SLOT(12) RVA00530550_SLOT(13) RVA00530550_SLOT(14)
	RVA00530550_SLOT(15) RVA00530550_SLOT(16) RVA00530550_SLOT(17)
	RVA00530550_SLOT(18) RVA00530550_SLOT(19) RVA00530550_SLOT(1A)
	RVA00530550_SLOT(1B) RVA00530550_SLOT(1C) RVA00530550_SLOT(1D)
	RVA00530550_SLOT(1E) RVA00530550_SLOT(1F) RVA00530550_SLOT(20)
	RVA00530550_SLOT(21) RVA00530550_SLOT(22) RVA00530550_SLOT(23)
	RVA00530550_SLOT(24) RVA00530550_SLOT(25) RVA00530550_SLOT(26)
	RVA00530550_SLOT(27) RVA00530550_SLOT(28) RVA00530550_SLOT(29)
	RVA00530550_SLOT(2A) RVA00530550_SLOT(2B) RVA00530550_SLOT(2C)
	RVA00530550_SLOT(2D) RVA00530550_SLOT(2E) RVA00530550_SLOT(2F)
	RVA00530550_SLOT(30) RVA00530550_SLOT(31) RVA00530550_SLOT(32)
	RVA00530550_SLOT(33) RVA00530550_SLOT(34) RVA00530550_SLOT(35)
	RVA00530550_SLOT(36) RVA00530550_SLOT(37) RVA00530550_SLOT(38)
	RVA00530550_SLOT(39) RVA00530550_SLOT(3A) RVA00530550_SLOT(3B)
	RVA00530550_SLOT(3C) RVA00530550_SLOT(3D) RVA00530550_SLOT(3E)
	RVA00530550_SLOT(3F) RVA00530550_SLOT(40) RVA00530550_SLOT(41)
	RVA00530550_SLOT(42) RVA00530550_SLOT(43) RVA00530550_SLOT(44)
	RVA00530550_SLOT(45) RVA00530550_SLOT(46) RVA00530550_SLOT(47)
	RVA00530550_SLOT(48) RVA00530550_SLOT(49) RVA00530550_SLOT(4A)
	RVA00530550_SLOT(4B) RVA00530550_SLOT(4C) RVA00530550_SLOT(4D)
	RVA00530550_SLOT(4E) RVA00530550_SLOT(4F) RVA00530550_SLOT(50)
	RVA00530550_SLOT(51) RVA00530550_SLOT(52) RVA00530550_SLOT(53)
	RVA00530550_SLOT(54) RVA00530550_SLOT(55) RVA00530550_SLOT(56)
	RVA00530550_SLOT(57);
#undef RVA00530550_SLOT
	virtual Bool didPlayerPreorder(Int profileID) const;
};

typedef std::map<Int, UnsignedInt> PerGeneralMap;

class PSPlayerStats
{
public:
	PSPlayerStats();
	PSPlayerStats(const PSPlayerStats &other);
	~PSPlayerStats();

	Int id;
	PerGeneralMap wins;
	PerGeneralMap losses;
	PerGeneralMap map1c;
	PerGeneralMap map28;
	PerGeneralMap map34;
	PerGeneralMap map40;
	PerGeneralMap games;
	PerGeneralMap map58;
	PerGeneralMap map64;
	PerGeneralMap map70;
	PerGeneralMap map7c;
	PerGeneralMap map88;
	PerGeneralMap map94;
	PerGeneralMap mapa0;
	PerGeneralMap mapac;
	PerGeneralMap discons;
	PerGeneralMap desyncs;
	PerGeneralMap mapd0;
	PerGeneralMap mapdc;
	PerGeneralMap mape8;
	PerGeneralMap mapf4;
	PerGeneralMap map100;
	PerGeneralMap map10c;
	PerGeneralMap map118;
	PerGeneralMap map124;
	PerGeneralMap map130;
	PerGeneralMap map13c;
	Int locale;
	std::string hole;
	Int gamesAsRandom;
	std::string options;
	std::string systemSpec;
	Real lastFPS;
	Int lastGeneral;
	Int gamesInRowWithLastGeneral;
	Int builtParticleCannon;
	Int builtNuke;
	Int builtSCUD;
	Int challengeMedals;
	Int battleHonors;
	Int winsInARow;
	Int maxWinsInARow;
	Int lossesInARow;
	Int maxLossesInARow;
	Int disconsInARow;
	Int maxDisconsInARow;
	Int desyncsInARow;
	Int maxDesyncsInARow;
	Int lastLadderPort;
	std::string lastLadderHost;
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual Bool isThreadRunning();
	virtual void addRequest(const void *request);
	virtual Bool getRequest(void *request);
	virtual void addResponse(const void *response);
	virtual Bool getResponse(void *response);
	virtual void trackPlayerStats(PSPlayerStats stats);
	virtual PSPlayerStats findPlayerStatsByID(Int profileID);
};

class Gen_uw_00025c1b
{
public:
	Int id;
	PerGeneralMap wins;
	PerGeneralMap losses;
};

extern GameSpyInfo *TheGameSpyInfo;
extern ImageCollection *TheMappedImageCollection;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

extern Int GadgetListBoxGetColumnWidth(GameWindow *listbox, Int column);
extern Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	Int row, Int column, Int width, Int height, Bool overwrite, Int color);
extern Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite);
extern void GadgetListBoxSetItemData(GameWindow *listbox, void *data,
	Int row, Int column);
extern void *bfmeLookupDL(void *context, Int side);
extern Int bfmeBandChecked(Int value);
extern Int bfmePickBestRankSide(Gen_uw_00025c1b *stats);
extern Int bfmeRankPointsFromStats(Gen_uw_00025c1b *stats, Int side);

class PlayerInfo;

struct Rva00530550PlayerInfoLayout
{
	char m_prefix[4];
	AsciiString m_baseName;
	char m_fields08[12];
	Int m_profileID;
	char m_fields18[4];
};

namespace Rva00530550
{
Int insertPlayerInListbox(GameWindow *listbox, const PlayerInfo &info, Int color)
{
	const Rva00530550PlayerInfoLayout &player =
		*reinterpret_cast<const Rva00530550PlayerInfoLayout *>(&info);
	Bool isPreorder = TheGameSpyInfo->didPlayerPreorder(player.m_profileID);
	const Image *preorderImg;
	{
		BFMERetailAsciiString imageName("Aptfellowship_clup");
		preorderImg = TheMappedImageCollection->findImageByName(imageName);
	}

	Int width = preorderImg ? preorderImg->m_imageWidth : 10;
	Int oldWidth = width;
	UnicodeString uStr;
	Int imageMarker = 1;
	uStr.translate(player.m_baseName);
	width = rva00530550Min(GadgetListBoxGetColumnWidth(listbox, 0), oldWidth);
	Int height = width;
	if (!isPreorder)
	{
		preorderImg = 0;
		imageMarker = 0;
	}

	Int side;
	Int rank;
	PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(player.m_profileID);
	side = bfmePickBestRankSide(reinterpret_cast<Gen_uw_00025c1b *>(&stats));
	rank = bfmeBandChecked(bfmeRankPointsFromStats(
		reinterpret_cast<Gen_uw_00025c1b *>(&stats), side));

	Int index = GadgetListBoxAddEntryImage(
		listbox, preorderImg, -1, 0, width, height, true, -1);
	if (stats.id != 0)
	{
		const Image *sideImg = reinterpret_cast<const Image *>(
			bfmeLookupDL(reinterpret_cast<void *>(rank), side));
		GadgetListBoxAddEntryImage(
			listbox, sideImg, index, 1, width, height, true, -1);
	}
	GadgetListBoxAddEntryText(listbox, uStr, color, index, 2, true);
	GadgetListBoxSetItemData(listbox, reinterpret_cast<void *>(imageMarker), index, 1);
	GadgetListBoxSetItemData(listbox, reinterpret_cast<void *>(player.m_profileID), index, 0);
	return index;
}
}

class PlayerInfo
{
};
