// ?getDeadImage@RespawnUpdate@@UAEPBVImage@@XZ
// cl: /DNDEBUG /MD /EHsc
// RespawnUpdate::getDeadImage at 0x002A1A80 (121 B, ret then int3 padding).
// Identity: retail's ??_7RespawnUpdate@@6BRU_DeepBase@@@ holds its ILT
// 0x00030EB3 in slot 12; ilt_oracle CONFIRMS the decorated name exactly at
// that thunk.  The name is carried from Open-BFME-2 (b5a7b8290,
// Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdateRva004AF25D.cpp,
// WorldBuilder RespawnUpdate::getDeadImage), whose BFME 2 body caches the same
// +0x24 image and has the same two-arm shape.  It caches the image named at
// module data +0xAC, else the portrait image of the object's final template.
// SHAPE: retail keeps two heads of the template null test (failed-find path
// +0x3A, empty-name path +0x56) over shared tails.  Writing the fallback in
// both arms with the null test of opposite polarity reproduces it; the same
// spelling in both arms cross-jumps into one head (114 B).

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Inline here, as in retail's caller: a null buffer or a zero length.
// AsciiString::isEmpty, expanded in place.  Calling the member would emit
// ?isEmpty@AsciiString@@QBE_NXZ and ?isEmpty@?$StringBase@D@@QBE_NXZ COMDATs
// that are not retail's bodies.  The buffer pointer is the string's first
// word; its length is at +4.
static __forceinline bool asciiIsEmpty( const AsciiString &string )
{
	const char *data = *reinterpret_cast<const char * const *>(&string);
	return !data || *reinterpret_cast<const unsigned short *>(data + 4) == 0;
}

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	const Overridable *finalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplatePortraitShim;

const Image *_bfme_getSelectedPortraitImage(const ThingTemplatePortraitShim *portraitTemplate,
	const ThingTemplatePortraitShim *objectTemplate);

class Object
{
public:
	const Overridable *getTemplate() const
	{
		return m_template ? m_template->finalOverride() : 0;
	}
	const Overridable *getTemplateOrNull() const
	{
		return !m_template ? 0 : m_template->finalOverride();
	}

private:
	void *m_vptr;
	Overridable *m_template;
};

struct RespawnUpdateModuleData
{
	unsigned char m_unmodelled_00[0xac];
	AsciiString m_imageName;
};

class RespawnUpdate
{
public:
	virtual const Image *getDeadImage();

private:
	RespawnUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0C[0x24 - 0x0c];
	const Image *m_cachedImage;
};

// ?getDeadImage@RespawnUpdate@@UAEPBVImage@@XZ
const Image *RespawnUpdate::getDeadImage()
{
	if (m_cachedImage)
		return m_cachedImage;

	Object *obj = m_object;
	if (!asciiIsEmpty(m_moduleData->m_imageName))
	{
		m_cachedImage = TheMappedImageCollection->findImageByName(m_moduleData->m_imageName);
		if (m_cachedImage)
			return m_cachedImage;
		obj = m_object;
		m_cachedImage = _bfme_getSelectedPortraitImage(
			(const ThingTemplatePortraitShim *)obj->getTemplate(),
			(const ThingTemplatePortraitShim *)obj);
		return m_cachedImage;
	}
	m_cachedImage = _bfme_getSelectedPortraitImage(
		(const ThingTemplatePortraitShim *)obj->getTemplateOrNull(),
		(const ThingTemplatePortraitShim *)obj);
	return m_cachedImage;
}
