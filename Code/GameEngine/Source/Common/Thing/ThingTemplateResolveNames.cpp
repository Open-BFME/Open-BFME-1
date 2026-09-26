// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();

	void *m_data;
};

class ThingTemplate;

class ProductionPrerequisite
{
public:
	void resolveNames();
	Int getAllPossibleBuildFacilityTemplates(const ThingTemplate *templates[], Int maxTemplates) const;

	char m_body[0x24];
};

class Image
{
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

#pragma comment(linker, "/alternatename:?resolveNames@ProductionPrerequisite@@QAEXXZ=?j_0002dfbf@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAllPossibleBuildFacilityTemplates@ProductionPrerequisite@@QBEHPAPBVThingTemplate@@H@Z=?j_000335c8@@YAXXZ")
#pragma comment(linker, "/alternatename:?findImageByName@MappedImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")
#pragma comment(linker, "/alternatename:?releaseBuffer@AsciiString@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

class ThingTemplate
{
public:
	void resolveNames();

private:
	char m_pad30[0x30];
	AsciiString m_selectedPortraitImageName;
	AsciiString m_buttonImageName;
	char m_padC8[0xC8 - 0x38];
	UnsignedInt m_kindof;
	char m_pad2C4[0x2C4 - 0xCC];
	_STL::vector<ProductionPrerequisite> m_prereqInfo;
	char m_pad390[0x390 - 0x2D0];
	const Image *m_selectedPortraitImage;
	const Image *m_buttonImage;
	char m_pad486[0x486 - 0x398];
	unsigned char m_isBuildFacility;
};

void ThingTemplate::resolveNames()
{
	Int prerequisiteIndex, facilityIndex;
	for (prerequisiteIndex = 0; prerequisiteIndex < m_prereqInfo.size(); prerequisiteIndex++)
	{
		m_prereqInfo[prerequisiteIndex].resolveNames();
	}

	const Int maxBuildFacilities = 32;
	const ThingTemplate *buildFacilities[maxBuildFacilities];
	for (prerequisiteIndex = 0; prerequisiteIndex < m_prereqInfo.size(); prerequisiteIndex++)
	{
		Int facilityCount = m_prereqInfo[prerequisiteIndex].getAllPossibleBuildFacilityTemplates(buildFacilities, maxBuildFacilities);
		for (facilityIndex = 0; facilityIndex < facilityCount; facilityIndex++)
		{
			if (buildFacilities[facilityIndex])
				const_cast<ThingTemplate *>(buildFacilities[facilityIndex])->m_isBuildFacility = 1;
		}
	}

	if (m_kindof & 0x00020000)
		m_isBuildFacility = 1;

	if (m_selectedPortraitImageName.isNotEmpty())
	{
		if (TheMappedImageCollection)
		{
			m_selectedPortraitImage = TheMappedImageCollection->findImageByName(m_selectedPortraitImageName);
			m_selectedPortraitImageName.clear();
		}
	}
	if (m_buttonImageName.isNotEmpty())
	{
		if (TheMappedImageCollection)
		{
			m_buttonImage = TheMappedImageCollection->findImageByName(m_buttonImageName);
			m_buttonImageName.clear();
		}
	}
}
