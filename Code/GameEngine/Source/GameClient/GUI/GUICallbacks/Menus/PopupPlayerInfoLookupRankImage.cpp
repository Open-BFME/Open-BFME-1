// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift PopupPlayerInfo's rank-image helper to clean C++.

typedef int Int;

extern "C" int __cdecl strcmp(const char *left, const char *right);
#pragma intrinsic(strcmp)

template <typename T>
class StringBase
{
private:
	friend class AsciiString;
	StringBase();
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	int compare(const T *text) const;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	AsciiString &operator=(const char *text);
	void __cdecl format(AsciiString format, ...);
	int compare(const char *text) const
	{
		return ((const StringBase<char> *)this)->compare(text);
	}

private:
	void *m_data;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

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

static const char *asciiStringText(const AsciiString &text)
{
	void *data = *(void * const *)&text;
	return data ? (const char *)data + 8 : "";
}

static bool asciiStringIsEmpty(const AsciiString &text)
{
	void *data = *(void * const *)&text;
	return data == 0 || *(const unsigned short *)((const char *)data + 4) == 0;
}

static const Image *lookupRankImage(AsciiString side, Int rank)
{
	if (asciiStringIsEmpty(side))
		return TheMappedImageCollection->findImageByName("NewPlayer");

	if (rank < 0 || rank >= 10)
		return 0;

	if (side.compare("America") == 0)
		side = "_USA";
	else if (side.compare("China") == 0)
		side = "_China";
	else if (side.compare("GLA") == 0)
		side = "_GLA";
	else if (side.compare("Random") == 0)
		side = "Elite";

	AsciiString fullImageName;
	fullImageName.format("Rank_%s%s", rankNames[rank], asciiStringText(side));
	if (strcmp(asciiStringText(fullImageName), "Rank_PrivateElite") == 0)
		fullImageName = "Rank";
	return TheMappedImageCollection->findImageByName(fullImageName);
}

const Image *lookupRankImageForPopup(AsciiString side, Int rank)
{
	return lookupRankImage(side, rank);
}
