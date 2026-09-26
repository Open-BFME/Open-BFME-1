// ?preloadAssets@ParticleSystemManager@@UAEXW4TimeOfDay@@@Z
// partial score=0.7 date=2026-09-10
// Candidate source for ParticleSystemManager::preloadAssets at 0x005CB720.
// This is a complete real-C++ reconstruction retained for the next converter;
// its current compiler shape is not byte verified.

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	AsciiString getTextureFilename() const;
};
}

class Image
{
public:
	AsciiString getFilename() const;
};

class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

#pragma comment(linker, "/alternatename:?getTextureFilename@ParticleSystemTemplate@FXParticleSystem@@QBE?AVAsciiString@@XZ=?j_00018755@@YAXXZ")
#pragma comment(linker, "/alternatename:?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFilename@Image@@QBE?AVAsciiString@@XZ=?j_000336ae@@YAXXZ")

struct ParticleTextureNameView
{
	unsigned int data;

	Bool isEmpty() const
	{
		return data == 0 ||
			*reinterpret_cast<const unsigned short *>( data + 4 ) == 0;
	}
};

// BFME's particle-template prefix differs from the ZH class definition:
// retail reads the type at +0x0C, stores the resolved texture name at +0x10,
// and copies the image region to +0x84.
struct BFMEParticleSystemTemplateView
{
	char m_prefix[0x0C];
	Int m_particleType;
	AsciiString m_particleTypeName;
	char m_unmodelled[0x70];
	unsigned int m_uv[4];
};

void ParticleSystemManager::preloadAssets( TimeOfDay timeOfDay )
{
	TemplateMap::iterator begin(m_templateMap.begin());
	TemplateMap::iterator end(m_templateMap.end());

	for (; begin != end; ++begin) {
		BFMEParticleSystemTemplateView *tmplate =
			reinterpret_cast<BFMEParticleSystemTemplateView *>( (*begin).second );
		if (tmplate->m_particleType == ParticleSystemInfo::PARTICLE)
		{
			FXParticleSystem::ParticleSystemTemplate *fxTemplate =
				reinterpret_cast<FXParticleSystem::ParticleSystemTemplate *>(tmplate);
			if (!reinterpret_cast<const ParticleTextureNameView &>(
				fxTemplate->getTextureFilename()).isEmpty())
			{
				AsciiString textureFilename = fxTemplate->getTextureFilename();
				for (Int i = 0; i < 4; ++i)
					textureFilename.removeLastChar();

				const Image *image = TheMappedImageCollection->findImageByName(textureFilename);
				if (image)
				{
					const unsigned int *imageUV = reinterpret_cast<const unsigned int *>(
						reinterpret_cast<const unsigned char *>(image) + 0x14);
					if (imageUV)
					{
						tmplate->m_uv[0] = imageUV[0];
						tmplate->m_uv[1] = imageUV[1];
						tmplate->m_uv[2] = imageUV[2];
						tmplate->m_uv[3] = imageUV[3];
						tmplate->m_particleTypeName = image->getFilename();
					}
				}
			}
		}
	}
}
