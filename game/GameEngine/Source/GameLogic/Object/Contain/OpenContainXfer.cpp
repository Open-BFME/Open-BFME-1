// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/System
// stlport
// readable body of ?xfer@OpenContain@@: game/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp
//
// Retail 0x002298B0 (1397 bytes, ret 4 at +0x572): OpenContain's snapshot
// transfer, BFME spelling ?DoXfer@OpenContain@@MAEXAAVXfer@@@Z (ilt_oracle
// CONFIRMS it at ILT 0x000489DC; the ZH ?xfer@...PAVXfer name and every other
// access spelling are CONTRADICTED, and the same holds for GarrisonContain). The
// OpenContain vtable 0x010AC2B8 slot 3 reaches it through ILT 0x000489DC and
// the matched GarrisonContain::xfer calls it as its base transfer.
//
// [BFME 2 donor] flow from Open-BFME-2 45afcff3
// Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainXfer.cpp (BFME 2
// 0x00465EF1, 1191 bytes): base transfer, light-CRC gate, version 1/1, the
// contain list as object IDs (load empties it through destroyObject and
// queues IDs on the ID list), the id->name map, the id->int map, scalars,
// the model-condition flags, the rally point, the enter/exit map with a
// 16-bit count and XferException(5) on a non-empty load, the exit path, the
// counted map and three trailing Bools. BFME 1 offsets, transfer widths and
// helpers come from the retail body itself; the BFME 1 layout matches
// OpenContainDestructors.cpp (lists at +0x38/+0x70, maps at +0x40, +0x4C,
// +0x58, +0xC8). Members other than the donor-named ones keep offset labels.
//
// Map subscripts: +0x40 reaches 0x00228310 through ILT 0x0004352C, a separate
// map<int, AsciiString> instantiation byte-identical (modulo calls) to the
// generic one at 0x000AB0C0, so it takes an address-qualified comparator
// like 0x00226FA0; +0x4C reaches 0x00226FA0 (the Rva00226FA0Less
// map of the matched sibling transfers); +0x58 reaches 0x00227110 through the
// plain map<int,int> pin at ILT 0x00018818; +0xC8 reaches 0x00228410 through
// the ??AEmotionMap pin at ILT 0x000033AA (the same instantiation Emotion::xfer
// calls).
#define _STLP_NO_EXCEPTIONS 1
#include "object.h"
#include "xfer.h"
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "Libraries/Source/WWVegas/WWMath/coord3d.h"
#include <list>
#include <map>

struct Rva00226FA0Less : std::less<int> {};
struct Rva00228310Less : std::less<int> {};

namespace _STL {
// out of line in retail (0x00227110, plain map<int,int> pin); call it, do not emit a copy
template <> int &map<int, int, less<int>, allocator<pair<const int, int> > >::operator[](const int &key);
}

class EmotionMap : public _STL::map<int, int>
{
public:
	int &operator[](const int &key);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

class FlagPairTarget;
class Gen002B2080 { public: void handle(FlagPairTarget *target); };
class Rva001CB270BitFlags { public: void xfer(Xfer *xfer); unsigned int m_bits[10]; };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *target, void *context);
class GameLogic { public: void destroyObject(Object *object); };
extern GameLogic *TheGameLogic;

struct Rva002298B0Version { Xfer::Version v; unsigned char pad[2]; };

class OpenContain
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	char m_unmodelled004[0x38 - 0x04];
	std::list<Object *> m_containList;				// +0x38
	unsigned int m_containListSize;					// +0x3C
	std::map<int, AsciiString, Rva00228310Less> m_unk40;				// +0x40
	std::map<int, int, Rva00226FA0Less> m_unk4C;	// +0x4C
	std::map<int, int> m_unk58;						// +0x58
	unsigned int m_unk64;
	int m_unk68;
	unsigned int m_unk6C;
	std::list<int> m_xferContainIDList;				// +0x70
	unsigned short m_unk74;
	unsigned int m_unk78;
	unsigned int m_unk7C;
	Rva001CB270BitFlags m_unk80;
	Coord3DBase m_rallyPoint;						// +0xA8
	bool m_rallyPointExists;						// +0xB4
	bool m_unkB5;
	bool m_unkB6;
	bool m_unkB7;
	bool m_unkB8;
	bool m_unkB9;
	int m_unkBC;
	int m_unkC0;
	int m_unkC4;
	EmotionMap m_unkC8;
};

void OpenContain::DoXfer(Xfer &xfer)
{
	((Gen002B2080 *)this)->handle((FlagPairTarget *)&xfer);
	if (xfer.IsLightCRC())
		return;

	Rva002298B0Version versionStorage;
	Xfer::Version &version = versionStorage.v;
	version.data[0] = 1;
	version.data[1] = 1;
	xfer == version;

	int objectID;
	if (xfer.IsStoring())
	{
		xfer == m_containListSize;
		for (std::list<Object *>::iterator it = m_containList.begin(); it != m_containList.end(); ++it)
		{
			objectID = (*it)->m_id;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);
		}
	}
	else
	{
		if (!m_containList.empty())
		{
			m_containListSize = 0;
			for (std::list<Object *>::iterator it = m_containList.begin(); it != m_containList.end(); )
			{
				Object *object = *it;
				it = m_containList.erase(it);
				TheGameLogic->destroyObject(object);
			}
			m_containList.clear();
		}
		xfer == m_containListSize;
		for (unsigned int i = 0; i < m_containListSize; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);
			m_xferContainIDList.push_back(objectID);
		}
	}

	if (xfer.IsStoring())
	{
		int count = m_unk40.size();
		xfer == count;
		for (std::map<int, AsciiString, Rva00228310Less>::iterator it = m_unk40.begin(); it != m_unk40.end(); ++it)
		{
			AsciiString name;
			int id = it->first;
			name = it->second;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &id);
			xfer == name;
		}
	}
	else
	{
		int count;
		xfer == count;
		for (int i = 0; i < count; ++i)
		{
			int id;
			AsciiString name;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &id);
			xfer == name;
			m_unk40[id] = name;
		}
	}

	if (xfer.IsStoring())
	{
		int count = m_unk4C.size();
		xfer == count;
		for (std::map<int, int, Rva00226FA0Less>::iterator it = m_unk4C.begin(); it != m_unk4C.end(); ++it)
		{
			int key = it->first;
			int value = it->second;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &key);
			xfer == value;
		}
	}
	else
	{
		int count;
		xfer == count;
		for (int i = 0; i < count; ++i)
		{
			int key;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &key);
			int value;
			xfer == value;
			m_unk4C[key] = value;
		}
	}

	xfer == m_unk74;
	xfer == m_unk78;
	xfer == m_unk7C;
	xfer == m_unk64;
	xfer == m_unk6C;
	m_unk80.xfer(&xfer);
	xfer == m_rallyPoint;
	xfer == m_rallyPointExists;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_unkBC);
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_unkC0);
	xfer == m_unkC4;

	unsigned short enterExitCount = m_unk58.size();
	xfer == enterExitCount;
	int enterExitType;
	if (xfer.IsStoring())
	{
		for (std::map<int, int>::iterator it = m_unk58.begin(); it != m_unk58.end(); ++it)
		{
			objectID = it->first;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);
			enterExitType = it->second;
			xfer.XferRawBytes(&enterExitType, sizeof(enterExitType));
		}
	}
	else
	{
		if (m_unk58.size() != 0)
			throw XferException(5, 0);
		for (unsigned short i = 0; i < enterExitCount; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);
			xfer.XferRawBytes(&enterExitType, sizeof(enterExitType));
			m_unk58[objectID] = enterExitType;
		}
	}

	xfer == m_unk68;

	unsigned int countCount = m_unkC8.size();
	xfer == countCount;
	if (xfer.IsLoading())
	{
		int id = 0;
		unsigned int value = 0;
		for (unsigned int i = 0; i < countCount; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &id);
			xfer == value;
			m_unkC8[id] = value;
		}
	}
	else
	{
		for (EmotionMap::iterator it = m_unkC8.begin(); it != m_unkC8.end(); ++it)
		{
			// volatile copies keep retail's id store ahead of the value load
			volatile int id = it->first;
			unsigned int value = *(volatile int *)&it->second;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, (void *)&id);
			xfer == value;
		}
	}

	xfer == m_unkB6;
	xfer == m_unkB9;
	xfer == m_unkB5;
}
