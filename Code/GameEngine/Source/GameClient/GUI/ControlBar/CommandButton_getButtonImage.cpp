// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

private:
	AsciiStringData *m_data;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	const Image *getButtonImage(void) const;

private:
	char m_beforeButtonImageName[0x40];
	AsciiString m_buttonImageName;
	char m_beforeButtonImage[0xf0 - 0x44];
	mutable const Image *m_buttonImage;
};

const Image *CommandButton::getButtonImage(void) const
{
	if (m_buttonImage)
		return m_buttonImage;

	if (m_buttonImageName.isEmpty())
		return 0;

	m_buttonImage = TheMappedImageCollection->findImageByName(m_buttonImageName);

	return m_buttonImage;
}
