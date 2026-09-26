// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The BFME command button stores image names at +0x94 and resolved images at
// +0x138. ControlBar::init calls this method while it walks its button list.

#include <functional>
#include "PreRTS.h"
#include "Common/STLTypedefs.h"

class BFMERetailAsciiString
{
public:
	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}

	void releaseBuffer();

private:
	void *m_data;
};

struct AsciiStringVector
{
	BFMERetailAsciiString *m_begin;
	BFMERetailAsciiString *m_finish;
	BFMERetailAsciiString *m_capacity;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

class CommandButton
{
public:
	void cacheButtonImage();

private:
	unsigned char m_unmodelled_00[0x94];
	AsciiStringVector m_buttonImageNames;
	unsigned char m_unmodelled_0a0[0x98];
	std::vector<const Image *> m_buttonImages;
};

// ?cacheButtonImage@CommandButton@@QAEXXZ
void CommandButton::cacheButtonImage()
{
	if (TheMappedImageCollection == 0)
		return;

	for (BFMERetailAsciiString *name = m_buttonImageNames.m_begin;
			name != m_buttonImageNames.m_finish; ++name)
	{
		if (name->isNotEmpty())
		{
			m_buttonImages.push_back(TheMappedImageCollection->findImageByName(
				*(const AsciiString *)name));
			name->releaseBuffer();
		}
	}
}
