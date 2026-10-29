// ?xfer@Rva001A78B0Record@@QAEXPAVXfer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/Libraries/Include/Lib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x001A78B0, 329 bytes (RET 4 at +0x146, INT3 after): a snapshot
// xfer(Xfer*) of a record whose owner is not proven, so the class keeps the
// address. Version {1, 2}; position (Coord3D overload, slot 0x60); an enum
// at +0x0C through the slot-0x90 forwarder Rva0010C3E0 unless the xfer is a
// CRC; the ThingTemplate at +0x14 by name (template +0x20), re-resolved with
// BfmeThingFactory::findTemplate on load; then +0x18 Bool, +0x1C Coord3D,
// +0x28 Int, +0x2E Short, +0x2C/+0x2D Bools, and +0x10 from version 2.
// Retail inlines StringBase<char>::isNotEmpty() here.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef short Short;

#include "ascii_string.h"
#include "xfer.h"
template<> inline bool StringBase<char>::isNotEmpty() const { return m_data != 0 && m_data->length != 0; }
#include "../../../Libraries/Source/WWVegas/WWMath/coord3d.h"

class ThingTemplate;
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
class ThingFactory;
extern ThingFactory *TheThingFactory;
#define TheThingFactory ((BfmeThingFactory *)TheThingFactory)

class MidVirtualSlot90Receiver;
void Rva0010C3E0(MidVirtualSlot90Receiver *receiver, void *context);

struct Rva001A78B0TemplateView
{
	unsigned char m_pad00[0x20];
	AsciiString m_name;
};

class Rva001A78B0Record
{
public:
	void xfer(Xfer *xfer);

private:
	Coord3DBase m_position;			// +0x00
	Int m_enum0C;					// +0x0C
	UnsignedInt m_value10;			// +0x10 (version 2)
	const ThingTemplate *m_template;	// +0x14
	Bool m_flag18;					// +0x18
	Coord3DBase m_position1C;		// +0x1C
	Int m_value28;					// +0x28
	Bool m_flag2C;					// +0x2C
	Bool m_flag2D;					// +0x2D
	Short m_value2E;				// +0x2E
};

void Rva001A78B0Record::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 2;
	*xfer == version;
	*xfer == m_position;
	if (!xfer->IsCRC())
		Rva0010C3E0((MidVirtualSlot90Receiver *)xfer, &m_enum0C);

	AsciiString templateName;
	if (!xfer->IsLoading() && m_template)
		templateName = ((const Rva001A78B0TemplateView *)m_template)->m_name;
	*xfer == templateName;
	if (xfer->IsLoading()) {
		if (templateName.isNotEmpty())
			m_template = TheThingFactory->findTemplate(templateName);
		else
			m_template = 0;
	}
	*xfer == m_flag18;
	*xfer == m_position1C;
	*xfer == m_value28;
	*xfer == m_value2E;
	*xfer == m_flag2C;
	*xfer == m_flag2D;
	if (version.data[1] >= 2)
		*xfer == m_value10;
}
