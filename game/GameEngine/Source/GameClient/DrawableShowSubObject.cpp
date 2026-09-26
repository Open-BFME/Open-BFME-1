// ?dispatch@Rva00416C20Owner@@QAEX_NVAsciiString@@@Z
// Neutral owner spelling: no named caller reaches this body in the shipped
// image.  Its proven operation is the Drawable-style subobject visibility
// fan-out: the owner carries the retail draw-module array at +0x150, each
// module exposes its object-draw interface at slot 39 (+0x9c), and the
// interface slot used here is slot 15 (+0x3c).  The retail parameter order is
// a Bool followed by an AsciiString object (both are four-byte stack values).

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

class Rva00416C20ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(bool show, AsciiString name);
};

class Rva00416C20DrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual Rva00416C20ObjectDrawInterface *getObjectDrawInterface();
};

class Rva00416C20Owner
{
public:
	void dispatch(bool show, AsciiString name);

private:
	char m_padding00[0x150];
	Rva00416C20DrawModule **m_drawModules;
};

void Rva00416C20Owner::dispatch(bool show, AsciiString name)
{
	for (Rva00416C20DrawModule **dm = m_drawModules; *dm; ++dm)
	{
		Rva00416C20ObjectDrawInterface *interface = (*dm)->getObjectDrawInterface();
		if (interface)
			interface->slot15(show, name);
	}
}
