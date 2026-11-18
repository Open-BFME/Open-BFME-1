// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
// stlport
// W3DFloorBuffer::DoXfer, retail RVA 0x006F9CD0, 589 bytes (ret 4 at +0x24A).
// Identity: W3DFloorBuffer's constructor 0x006F92D0 and destructor 0x006F91F0
// install vftable 0x01120360. Its slot 0 is ??_GW3DFloorBuffer (0x006F92A0)
// and slot 3, the BFME Snapshot DoXfer slot, reaches this body through ILT
// 0x0000242D. tools/ilt_oracle.py check confirms
// Body: skip a light-CRC pass, version {1, 2}, then the element count of the
// +0x20 floor list. Loading resets the buffer (0x006F9050), then per element
// transfers a stack BaseHeightMapFloorElement (constructor 0x006F81E0,
// transfer 0x006F87D0, destructor 0x006F8290), re-adds it through the
// add-element body 0x006F9A90 (drawable ID, by-value name, two flag bytes),
// copies the remaining fields onto the new element, and from version 2 reads
// the +0x95 flag. Saving transfers each listed element and its +0x95 flag.
// The two callees whose ledger rows still carry opaque placeholder owners
// (BfmeHostBG::bfmeSaveBG, Rva006F9900Owner::addElement006F9A90) are called
// through their ledger names.
// The element constructor has no provider in this tree: the body at 0x006F81E0
// is the ledger's ??0BfmeHostBG row, and the constructor name is only a pin
// (symbols.csv, 0x006F81E0). Retail spells the call through the
// incremental-link thunk 0x000253F6 (the stack element is built at +0x97 and
// destroyed through 0x00011C3E), so link the constructor name to that thunk:
// alias_guard follows the gen-thunk row to FUN_00af81e0, the same body the
// name is pinned to, and the call bytes stay the ones the body was matched on.

#include <list>

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../GameEngine/Source/Common/System/xfer.h"

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


class BaseHeightMapFloorElement
{
public:
	BaseHeightMapFloorElement();
	virtual ~BaseHeightMapFloorElement();

	char m_pad04[0x44];
	Int m_drawableID;		// +0x48
	Int m_4C;
	Int m_50;
	Int m_54;
	Int m_58;
	Int m_5C;
	Int m_60;
	Int m_64;
	Int m_68;
	Int m_6C;
	Int m_70;
	Int m_74;
	Int m_78;
	unsigned char m_7C;
	unsigned char m_flag;		// +0x7D
	unsigned char m_atFront;	// +0x7E
	Int m_80;
	Int m_84;
	AsciiString m_name;		// +0x88
	Int m_8C;
	Int m_90;
	unsigned char m_94;
	Bool m_95;
};

#pragma comment(linker, "/alternatename:??0BaseHeightMapFloorElement@@QAE@XZ=?j_000253f6@@YAXXZ")

// 0x006F87D0: the element's own transfer (ledger row keeps the opaque name).
class BfmeAgentBG;
class BfmeHostBG
{
public:
	void bfmeSaveBG(BfmeAgentBG *xfer);
};

// 0x006F9A90: W3DFloorBuffer's add-element (ledger row keeps the opaque owner).
class Rva006F9900Owner
{
public:
	BaseHeightMapFloorElement *addElement006F9A90(int id, AsciiString name,
		unsigned char atFront, unsigned char flag);
};

class W3DFloorBuffer
{
public:
	void rva006F9050();

protected:
	virtual void DoXfer(Xfer &xfer);

private:
	char m_pad04[0x1c];
	_STL::list<BaseHeightMapFloorElement *> m_elements;	// +0x20
};

void W3DFloorBuffer::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 2;
	xfer == version;

	Int count = m_elements.size();
	xfer.xferInt(&count);

	if (xfer.IsLoading())
	{
		rva006F9050();
		for (Int i = 0; i < count; ++i)
		{
			BaseHeightMapFloorElement element;
			reinterpret_cast<BfmeHostBG *>(&element)->bfmeSaveBG(
				reinterpret_cast<BfmeAgentBG *>(&xfer));
			BaseHeightMapFloorElement *added =
				reinterpret_cast<Rva006F9900Owner *>(this)->addElement006F9A90(
					element.m_drawableID, element.m_name, element.m_atFront, element.m_flag);
			if (added)
			{
				added->m_4C = element.m_4C;
				added->m_50 = element.m_50;
				added->m_54 = element.m_54;
				added->m_58 = element.m_58;
				added->m_5C = element.m_5C;
				added->m_60 = element.m_60;
				added->m_64 = element.m_64;
				added->m_68 = element.m_68;
				added->m_6C = element.m_6C;
				added->m_70 = element.m_70;
				added->m_74 = element.m_74;
				added->m_78 = element.m_78;
				added->m_7C = element.m_7C;
				added->m_flag = element.m_flag;
				added->m_atFront = element.m_atFront;
				added->m_80 = element.m_80;
				added->m_84 = element.m_84;
				added->m_8C = element.m_8C;
				added->m_90 = element.m_90;
				added->m_94 = element.m_94;
			}
			if (version.data[1] >= 2)
			{
				Bool flag = true;
				xfer.xferBool(&flag);
				if (added)
					added->m_95 = flag;
			}
		}
	}
	else
	{
		for (_STL::list<BaseHeightMapFloorElement *>::iterator it = m_elements.begin();
			it != m_elements.end(); ++it)
		{
			BaseHeightMapFloorElement *element = *it;
			reinterpret_cast<BfmeHostBG *>(element)->bfmeSaveBG(
				reinterpret_cast<BfmeAgentBG *>(&xfer));
			if (version.data[1] >= 2)
				xfer.xferBool(&element->m_95);
		}
	}
}
