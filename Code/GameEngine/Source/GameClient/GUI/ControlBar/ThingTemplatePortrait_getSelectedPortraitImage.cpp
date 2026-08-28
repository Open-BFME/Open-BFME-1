class Image;

struct AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
};

class AsciiString
{
public:
	bool isNotEmpty(void) const
	{
		return m_data != 0 && m_data->m_length != 0;
	}

	void clear(void);

private:
	AsciiStringData *m_data;
};

class MappedImageCollectionPortraitShim
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollectionPortraitShim *TheMappedImageCollection;

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage(void) const;

private:
	char m_bfmeBeforePortraitName[0x34];
	mutable AsciiString m_bfmePortraitName;
	char m_bfmeBeforeCachedPortrait[0x394 - 0x38];
	mutable const Image *m_bfmeCachedPortrait;
};

// ?getSelectedPortraitImage@ThingTemplatePortraitShim@@QBEPBVImage@@XZ
const Image *ThingTemplatePortraitShim::getSelectedPortraitImage(void) const
{
	if (m_bfmePortraitName.isNotEmpty() && TheMappedImageCollection)
	{
		m_bfmeCachedPortrait = TheMappedImageCollection->findImageByName(m_bfmePortraitName);
		m_bfmePortraitName.clear();
	}

	return m_bfmeCachedPortrait;
}
