class Image;

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline bool StringBase<char>::isNotEmpty() const { return !isEmpty(); }

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

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
	if (m_bfmePortraitName.StringBase<char>::isNotEmpty() && TheMappedImageCollection)
	{
		m_bfmeCachedPortrait = TheMappedImageCollection->findImageByName(m_bfmePortraitName);
		m_bfmePortraitName.StringBase<char>::clear();
	}

	return m_bfmeCachedPortrait;
}
