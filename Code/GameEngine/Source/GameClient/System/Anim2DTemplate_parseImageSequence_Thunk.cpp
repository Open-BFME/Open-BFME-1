// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// The Anim2D field table in Anim2D.cpp registers this protected parser.
// Retail places its body at RVA 0x005BB150 with a 381-byte boundary.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Header
	{
		int m_refCount;
		unsigned short m_len;
		unsigned short m_capacity;
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
	const char *str() const
	{
		return m_data ? (const char *)(m_data + 1) : "";
	}
	void __cdecl format(AsciiString format, ...);
};

class Image {};

class INI
{
public:
	AsciiString getNextAsciiString();
};

class INIException
{
public:
	INIException(Int, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_message;
	Int m_unreconstructed04;
};

class Anim2DTemplate
{
public:
	AsciiString getName() const { return m_name; }
	UnsignedShort getNumFrames() const { return m_numFrames; }
	void storeImage(const Image *image);

protected:
	static void parseImageSequence(INI *ini, void *instance, void *store, const void *userData);

private:
	void *m_vptr;
	Anim2DTemplate *m_nextTemplate;
	AsciiString m_name;
	const Image **m_images;
	UnsignedShort m_numFrames;
	UnsignedShort m_framesBetweenUpdates;
	int m_animMode;
	Bool m_randomizeStartFrame;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class ImageCollection;
extern ImageCollection *TheMappedImageCollection;

void Anim2DTemplate::parseImageSequence(INI *ini, void *instance,
	void *store, const void *userData)
{
	const Image *image;
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;

	if (animTemplate->getNumFrames() == 0) {
		throw INIException(3,
			"Anim2DTemplate::parseImageSequence - You must specify the number of animation frames for animation '%s' *BEFORE* specifying the image sequence name\n",
			animTemplate->getName().str());
	}

	AsciiString imageBaseName = ini->getNextAsciiString();
	AsciiString imageName;
	for (Int i = 0; i < animTemplate->getNumFrames(); ++i) {
		imageName.format("%s%03d", imageBaseName.str(), i);
		image = ((MappedImageCollection *)TheMappedImageCollection)->findImageByName(imageName);
		if (image == 0) {
			throw INIException(3,
				"Anim2DTemplate::parseImageSequence - Image '%s' not found for animation '%s'.  Check the number of images specified in INI and also make sure all the actual images exist.\n",
				imageName.str(), animTemplate->getName().str());
		}
		animTemplate->storeImage(image);
	}
}
