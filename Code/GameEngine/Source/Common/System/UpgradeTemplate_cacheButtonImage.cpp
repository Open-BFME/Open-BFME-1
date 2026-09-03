// cl: /DNDEBUG /MD /EHsc
// readable body of ?cacheButtonImage@UpgradeTemplate@@QAEXXZ: Code/GameEngine/Source/Common/System/Upgrade.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isNotEmpty() const
	{
		return m_data && *(unsigned short *)(m_data + 4) != 0;
	}

	void clear();

private:
	char *m_data;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	void cacheButtonImage();

private:
	char m_bfmeLayout[0x110];
	AsciiString m_buttonImageName;
	const Image *m_buttonImage;
};

void UpgradeTemplate::cacheButtonImage()
{
	if (m_buttonImageName.isNotEmpty())
	{
		m_buttonImage =
			TheMappedImageCollection->findImageByName(m_buttonImageName);
		m_buttonImageName.clear();
	}
}
