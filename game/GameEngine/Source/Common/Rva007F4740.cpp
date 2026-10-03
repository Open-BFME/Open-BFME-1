// Retail 0x007F4740: cdecl callback; first argument unused.
// Native null-preserving receiver adjustment selects the interface at +4.
class Rva007EA0A0Owner
{
public:
	void forwardSentinel();
};

class Rva007F4740Primary
{
public:
	virtual void slot0();
	virtual void *slot1();
};

class Rva007F4740Slot
{
public:
	virtual Rva007EA0A0Owner *slot0();
};

class Rva007F4740Context : public Rva007F4740Primary, public Rva007F4740Slot
{
};

class Rva007F4740
{
public:
	static void __cdecl bfmeCbBZC(void *, Rva007F4740Context *);
};

void __cdecl Rva007F4740::bfmeCbBZC(void *, Rva007F4740Context *context)
{
	static_cast<Rva007F4740Slot *>(context)->slot0()->forwardSentinel();
}
