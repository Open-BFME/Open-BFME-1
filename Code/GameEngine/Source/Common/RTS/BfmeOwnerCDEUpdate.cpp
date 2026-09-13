// cl: /EHsc

// Retail 0x008F8C70 (136 bytes).  The public ShroudManager-family forwarder
// at 0x008F73B0 loads its implementation at +0x0C and jumps here.  The
// adjacent owner allocator at 0x008FA850 and remover at 0x008F8D00 establish
// the CDE provider ABI and BfmeThingCDE layout used below.  The method's
// implementation does not read its owner; it accepts two provider objects,
// selects the first provider's CDE node when the second is not already bound,
// releases the node's old provider, then binds the second provider.

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *value);
	virtual void *f4();
};

class CDELeading
{
public:
	virtual void f0();
};

// This is the complete observed leading/virtual-base shape: the provider's
// vbptr is at +4, and f3/f4 are slots +0x0C/+0x10 in the virtual base.
class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class BfmeThingCDE
{
public:
	void *m_owner;
	CDEProvider *m_provider4;
	CDEProvider *m_provider8;
};

class ShroudManagerImpl008FBA40
{
public:
	void rva008F8C70(CDEProvider *first, CDEProvider *second);
};

// ?rva008F8C70@ShroudManagerImpl008FBA40@@QAEXPAVCDEProvider@@0@Z
void ShroudManagerImpl008FBA40::rva008F8C70(CDEProvider *first, CDEProvider *second)
{
	if (first == 0)
		return;
	if (first->f4() == 0)
		return;
	if (second == 0)
		return;
	if (second->f4() != 0)
		return;

	BfmeThingCDE *thing = (BfmeThingCDE *)first->f4();
	if (thing->m_provider8 != 0)
	{
		thing->m_provider8->f3(0);
		thing->m_provider8->f0();
	}
	thing->m_provider8 = second;
	second->f3(thing);
}
