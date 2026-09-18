// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x005207C0, 214 bytes. MpGameSetup's named initialization and
// shutdown both pass receiver+0x28 to this same AptMapPreview subobject.
// Callback 0x00521990 witnesses the four windows and eight child pointers.
// Constructor 0x00520670 writes through +0x3C; the containing constructor
// places the next member at preview+0x40. Unused tail fields remain opaque.

#include "ascii_string.h"

class GameWindow;
void _bfme_closeAptScreen(const AsciiString &screenName);
extern "C" void *memset(void *destination, int value, unsigned int size);

class AptMapPreview
{
public:
	void bfmeReset(void);

private:
	char m_unmodelled00[4];
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_children[8];
	class Ref
	{
	public:
		virtual void release(int count);
	};
	Ref *m_picture;
	bool m_pictureOwned;
	unsigned char m_unmodelled39[7];
};

class S4Holder0046DBB0
{
public:
	void take0046DEF0(const AsciiString &name);
};

// ?bfmeReset@AptMapPreview@@QAEXXZ
void AptMapPreview::bfmeReset(void)
{
	{
		AsciiString name("AptMapPreview::Picture");
		(reinterpret_cast<S4Holder0046DBB0 **>(0x012f19e8))[0]->take0046DEF0(name);
	}
	{
		AsciiString name("AptMapPreview::MapGadgetInit");
		_bfme_closeAptScreen(name);
	}

	m_currentMap = 0;
	m_mapPicture = 0;
	m_mapInfo = 0;
	m_mapDescription = 0;
	if (m_pictureOwned)
	{
		if (m_picture)
		{
			m_picture->release(1);
			m_picture = 0;
			m_pictureOwned = false;
		}
	}
	memset(m_children, 0, sizeof(m_children));
}

