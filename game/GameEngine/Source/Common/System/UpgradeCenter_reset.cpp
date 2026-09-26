// cl: /DNDEBUG /MD /EHsc

class Image;

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

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

class UpgradeTemplate
{
public:
	void cacheButtonImage()
	{
		if (m_buttonImageName.isNotEmpty())
		{
			m_buttonImage = TheMappedImageCollection->findImageByName(m_buttonImageName);
			m_buttonImageName.clear();
		}
	}

	UpgradeTemplate *friend_getNext()
	{
		return m_next;
	}

private:
	char m_padding[0x108];
	UpgradeTemplate *m_next;
	UpgradeTemplate *m_prev;
	AsciiString m_buttonImageName;
	const Image *m_buttonImage;
};

class UpgradeCenter
{
public:
	virtual void reset();

private:
	char m_vtable[4];
	UpgradeTemplate *m_upgradeList;
	int m_nextTemplateMaskBit;
	bool buttonImagesCached;
};

#pragma comment(linker, "/alternatename:?findImageByName@MappedImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")

void UpgradeCenter::reset()
{
	if (TheMappedImageCollection && !buttonImagesCached)
	{
		UpgradeTemplate *upgrade;
		for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		{
			upgrade->cacheButtonImage();
		}
		buttonImagesCached = true;
	}
}
