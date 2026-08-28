// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift LookupSmallRankImage to clean C++.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef int Int;

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/RankPointValue.h
class RankPoints
{
public:
	Int m_ranks[11];
};

extern RankPoints *TheRankPointValues;
extern MappedImageCollection *TheMappedImageCollection;

static __forceinline const char *asciiStringText(const AsciiString &text)
{
	void *data = *(void * const *)&text;
	return data ? (const char *)data + 8 : "";
}

static const char *rankNames[] = {
	"Private",
	"Corporal",
	"Sergeant",
	"Lieutenant",
	"Captain",
	"Major",
	"Colonel",
	"General",
	"Brigadier",
	"Commander",
};

// ?LookupSmallRankImage@@YAPBVImage@@HH@Z
const Image * __cdecl LookupSmallRankImage(Int side, Int rankPoints)
{
	if (rankPoints == 0)
		return 0;

	Int rank = 0;
	while (rankPoints >= TheRankPointValues->m_ranks[rank + 1])
		++rank;

	if (rank < 0 || rank >= 10)
		return 0;

	AsciiString sideStr = "N";
	switch (side)
	{
		case 2:
			sideStr = "USA";
			break;

		case 3:
			sideStr = "CHA";
			break;

		case 4:
			sideStr = "GLA";
			break;
	}

	AsciiString fullImageName;
	fullImageName.format("%s-%s", rankNames[rank], asciiStringText(sideStr));
	return TheMappedImageCollection->findImageByName(fullImageName);
}
