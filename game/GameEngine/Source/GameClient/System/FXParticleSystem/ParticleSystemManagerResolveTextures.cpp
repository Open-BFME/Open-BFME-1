// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x005CB720 (460 bytes, plain RET at +0x1CB, no stack arguments):
// slot 14 (+0x38) of the FXParticleSystem::ParticleSystemManager vtable
// 0x0110FDCC (the ctor 0x005CBF60 and dtor 0x005CB360 install it; ILT
// confirms both under FXParticleSystem). It walks the template map at +0x9C
// (as in ParticleSystemManagerFindParentTemplate.cpp and _writeOutINI) and,
// for every particle-type template (type 1 at +0x0C) with a texture name,
// strips the four-character extension, looks the result up in
// TheMappedImageCollection and copies the image's UV region (+0x14) to the
// template (+0x84) and the image's file name to the template's texture
// name (+0x10). Zero Hour's preloadAssets(TimeOfDay) has a stack argument,
// so the method name is not proven: the address-derived name stays.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "ascii_string.h"

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};

	// Zero Hour's STLDefs.h: hash the string's characters by value copy.
	template <>
	struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString ast) const
		{
			_STL::hash<const char *> tmp;
			return tmp((const char *)ast.str());
		}
	};
}

// Retail tests the name's string header in line (no data, or a zero 16-bit
// length), as ParticleSystemManagerFindParentTemplate.cpp does.
struct BfmeAsciiHeaderView
{
	int m_refCount;
	unsigned short m_length;
};

inline bool bfmeNameIsEmpty(const AsciiString &name)
{
	const BfmeAsciiHeaderView *data = *(const BfmeAsciiHeaderView *const *)&name;
	return data == 0 || data->m_length == 0;
}

struct Region2D
{
	float loX;
	float loY;
	float hiX;
	float hiY;
};

class Image
{
public:
	const Region2D *getUV() const { return &m_UVCoords; }
	AsciiString getFilename() const;

private:
	unsigned char m_pad0[0x14];
	Region2D m_UVCoords;				// +0x14
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	AsciiString getTextureFilename() const;

	unsigned char m_prefix[0x0C];
	int m_particleType;					// +0x0C
	AsciiString m_particleTypeName;		// +0x10
	unsigned char m_unmodelled[0x84 - 0x14];
	Region2D m_uv;						// +0x84
};

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > TemplateMap;

class ParticleSystemManager
{
public:
	virtual void rva005CB720();

private:
	unsigned char m_managerPrefix[0x98];
	TemplateMap m_templateMap;			// +0x9C
};

// ?rva005CB720@ParticleSystemManager@FXParticleSystem@@UAEXXZ
void ParticleSystemManager::rva005CB720()
{
	for (TemplateMap::iterator it = m_templateMap.begin(); it != m_templateMap.end(); ++it) {
		ParticleSystemTemplate *tmplate = (*it).second;
		if (tmplate->m_particleType == 1 && !bfmeNameIsEmpty(tmplate->getTextureFilename())) {
			AsciiString name = tmplate->getTextureFilename();
			for (int i = 0; i < 4; ++i)
				name.removeLastChar();

			const Image *image = TheMappedImageCollection->findImageByName(name);
			if (image) {
				const Region2D *uv = image->getUV();
				if (uv)
					tmplate->m_uv = *uv;
				tmplate->m_particleTypeName = image->getFilename();
			}
		}
	}
}

}
