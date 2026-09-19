// Rva003A5A10::xfer, retail 0x003A5A10. The owner identity is address-derived.
// Field offsets and Xfer slots follow the complete retail body.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <vector>

struct Rva003A5A10Version
{
	unsigned char data[2];
};

struct Rva003A5A10Coord2D
{
	int x;
	int y;
};

class Rva003A5A10XferView
{
public:
	virtual void slot00();
	virtual bool IsLoading();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(Rva003A5A10Version *version);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void xferCoord2D(Rva003A5A10Coord2D *value);
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferFloat(float *value);
	virtual void slot70();
	virtual void slot74();
	virtual void xferInt(int *value);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void xferBool(bool *value);
	virtual void XferEnum(const char *name, void *data, unsigned int size);
};

class Open2Rec3A4420
{
public:
	Open2Rec3A4420() : m_at08(), m_at0c() {}
	Open2Rec3A4420(const Open2Rec3A4420 &source);
	~Open2Rec3A4420();

	int m_at00;
	int m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	int m_at10;
};

struct Rva003A5500Placement;
inline void *operator new(unsigned int, Rva003A5500Placement *place)
{
	return place;
}
void operator delete(void *, Rva003A5500Placement *);

namespace _STL
{
struct Rva003A5500Element
{
	char m_body[20];
};

template <>
__forceinline void _Construct<Rva003A5500Element, Rva003A5500Element>(Rva003A5500Element *destination, const Rva003A5500Element &source)
{
	new ((Rva003A5500Placement *)destination) Open2Rec3A4420(
		reinterpret_cast<const Open2Rec3A4420 &>(source));
}

template <typename T, typename Allocator>
class public_vector : public vector<T, Allocator>
{
public:
	using vector<T, Allocator>::_M_finish;
	using vector<T, Allocator>::_M_end_of_storage;
	using vector<T, Allocator>::_M_insert_overflow;
};
}

struct Rva005A00B0AudioClient
{
#define RVA_AUDIO_SLOT(n) virtual void slot##n();
	RVA_AUDIO_SLOT(00) RVA_AUDIO_SLOT(01) RVA_AUDIO_SLOT(02)
	RVA_AUDIO_SLOT(03) RVA_AUDIO_SLOT(04) RVA_AUDIO_SLOT(05)
	RVA_AUDIO_SLOT(06) RVA_AUDIO_SLOT(07) RVA_AUDIO_SLOT(08)
	RVA_AUDIO_SLOT(09) RVA_AUDIO_SLOT(10) RVA_AUDIO_SLOT(11)
	RVA_AUDIO_SLOT(12) RVA_AUDIO_SLOT(13) RVA_AUDIO_SLOT(14)
	RVA_AUDIO_SLOT(15) RVA_AUDIO_SLOT(16) RVA_AUDIO_SLOT(17)
	RVA_AUDIO_SLOT(18) RVA_AUDIO_SLOT(19) RVA_AUDIO_SLOT(20)
	RVA_AUDIO_SLOT(21) RVA_AUDIO_SLOT(22) RVA_AUDIO_SLOT(23)
	RVA_AUDIO_SLOT(24) RVA_AUDIO_SLOT(25) RVA_AUDIO_SLOT(26)
	RVA_AUDIO_SLOT(27) RVA_AUDIO_SLOT(28) RVA_AUDIO_SLOT(29)
	RVA_AUDIO_SLOT(30) RVA_AUDIO_SLOT(31) RVA_AUDIO_SLOT(32)
	RVA_AUDIO_SLOT(33) RVA_AUDIO_SLOT(34) RVA_AUDIO_SLOT(35)
	RVA_AUDIO_SLOT(36) RVA_AUDIO_SLOT(37) RVA_AUDIO_SLOT(38)
	RVA_AUDIO_SLOT(39) RVA_AUDIO_SLOT(40) RVA_AUDIO_SLOT(41)
	RVA_AUDIO_SLOT(42) RVA_AUDIO_SLOT(43) RVA_AUDIO_SLOT(44)
	RVA_AUDIO_SLOT(45) RVA_AUDIO_SLOT(46) RVA_AUDIO_SLOT(47)
	RVA_AUDIO_SLOT(48) RVA_AUDIO_SLOT(49) RVA_AUDIO_SLOT(50)
	RVA_AUDIO_SLOT(51) RVA_AUDIO_SLOT(52) RVA_AUDIO_SLOT(53)
	RVA_AUDIO_SLOT(54) RVA_AUDIO_SLOT(55) RVA_AUDIO_SLOT(56)
	RVA_AUDIO_SLOT(57) RVA_AUDIO_SLOT(58) RVA_AUDIO_SLOT(59)
	RVA_AUDIO_SLOT(60) RVA_AUDIO_SLOT(61) RVA_AUDIO_SLOT(62)
	RVA_AUDIO_SLOT(63) RVA_AUDIO_SLOT(64) RVA_AUDIO_SLOT(65)
	RVA_AUDIO_SLOT(66) RVA_AUDIO_SLOT(67) RVA_AUDIO_SLOT(68)
	RVA_AUDIO_SLOT(69) RVA_AUDIO_SLOT(70) RVA_AUDIO_SLOT(71)
	RVA_AUDIO_SLOT(72) RVA_AUDIO_SLOT(73) RVA_AUDIO_SLOT(74)
	RVA_AUDIO_SLOT(75) RVA_AUDIO_SLOT(76) RVA_AUDIO_SLOT(77)
	RVA_AUDIO_SLOT(78) RVA_AUDIO_SLOT(79) RVA_AUDIO_SLOT(80)
	RVA_AUDIO_SLOT(81)
	virtual void takeItem148(Rva003A5A10XferView *xfer, void *value);
#undef RVA_AUDIO_SLOT
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Rva003A5A10
{
public:
	virtual void slot00();
	void xfer(Rva003A5A10XferView *xfer);

	AsciiString m_field04;
	AsciiString m_field08;
	Rva003A5A10Coord2D m_field0C;
	Rva003A5A10Coord2D m_field14;
	bool m_field1C;
	bool m_field1D;
	bool m_field1E;
	bool m_field1F;
	float m_field20;
	int m_field24;
	_STL::public_vector<_STL::Rva003A5500Element,
		_STL::allocator<_STL::Rva003A5500Element> > m_entries;
	AsciiString m_field34;
	int m_field38;
	int m_field3C;
	AsciiString m_field40;
	bool m_field44;
};

void Rva003A5A10::xfer(Rva003A5A10XferView *xfer)
{
	Rva003A5A10Version version;
	version.data[0] = 1;
	version.data[1] = 2;
	xfer->xferVersion(&version);
	xfer->xferAsciiString(&m_field04);
	xfer->xferAsciiString(&m_field08);
	xfer->xferCoord2D(&m_field0C);
	xfer->xferCoord2D(&m_field14);
	xfer->xferBool(&m_field1C);
	xfer->xferBool(&m_field1D);
	xfer->xferBool(&m_field1E);
	xfer->xferBool(&m_field1F);
	xfer->xferFloat(&m_field20);
	xfer->xferAsciiString(&m_field34);
	xfer->XferEnum("ArmyIconSize", &m_field3C, 4);
	xfer->xferAsciiString(&m_field40);
	if (version.data[1] >= 2)
		xfer->xferBool(&m_field44);

	if (xfer->IsLoading())
	{
		int count;
		xfer->xferInt(&count);
		int i = 0;
		for (; i < count; ++i)
		{
			Open2Rec3A4420 local;
			xfer->xferCoord2D((Rva003A5A10Coord2D *)(void *)&local);
			xfer->xferAsciiString(&local.m_at08);
			xfer->xferAsciiString(&local.m_at0c);
			xfer->xferFloat((float *)(void *)&local.m_at10);

			_STL::public_vector<_STL::Rva003A5500Element,
				_STL::allocator<_STL::Rva003A5500Element> > *entries = &m_entries;
			if (entries->_M_finish != entries->_M_end_of_storage._M_data)
			{
				_STL::_Construct(entries->_M_finish, *(const _STL::Rva003A5500Element *)(void *)&local);
				++entries->_M_finish;
			}
			else
			{
				entries->_M_insert_overflow(entries->_M_finish,
					*(const _STL::Rva003A5500Element *)(void *)&local,
					reinterpret_cast<const _STL::__false_type &>(i), 1UL, true);
			}
		}
	}
	else
	{
		int count = (int)m_entries.size();
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			_STL::Rva003A5500Element *entry =
				m_entries.begin() + i;
			xfer->xferCoord2D((Rva003A5A10Coord2D *)(void *)entry);
			xfer->xferAsciiString((AsciiString *)(void *)(entry->m_body + 8));
			xfer->xferAsciiString((AsciiString *)(void *)(entry->m_body + 12));
			xfer->xferFloat((float *)(void *)(entry->m_body + 16));
		}
	}

	TheAudioClientUpdate->takeItem148(xfer, &m_field24);
}
