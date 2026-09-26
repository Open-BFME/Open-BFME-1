// cl: /O2 /Ob0
//
// ICF twin of 0x002BBE10: same 18-byte guarded virtual tail at this+0x40
// / vtable+0x48, xor al,al on the null path.

class Rva002BBF10Slots00
{
public:
	virtual void slot00();
};

class Rva002BBF10Slots04 : public Rva002BBF10Slots00 { public: virtual void slot04(); };
class Rva002BBF10Slots08 : public Rva002BBF10Slots04 { public: virtual void slot08(); };
class Rva002BBF10Slots0C : public Rva002BBF10Slots08 { public: virtual void slot0C(); };
class Rva002BBF10Slots10 : public Rva002BBF10Slots0C { public: virtual void slot10(); };
class Rva002BBF10Slots14 : public Rva002BBF10Slots10 { public: virtual void slot14(); };
class Rva002BBF10Slots18 : public Rva002BBF10Slots14 { public: virtual void slot18(); };
class Rva002BBF10Slots1C : public Rva002BBF10Slots18 { public: virtual void slot1C(); };
class Rva002BBF10Slots20 : public Rva002BBF10Slots1C { public: virtual void slot20(); };
class Rva002BBF10Slots24 : public Rva002BBF10Slots20 { public: virtual void slot24(); };
class Rva002BBF10Slots28 : public Rva002BBF10Slots24 { public: virtual void slot28(); };
class Rva002BBF10Slots2C : public Rva002BBF10Slots28 { public: virtual void slot2C(); };
class Rva002BBF10Slots30 : public Rva002BBF10Slots2C { public: virtual void slot30(); };
class Rva002BBF10Slots34 : public Rva002BBF10Slots30 { public: virtual void slot34(); };
class Rva002BBF10Slots38 : public Rva002BBF10Slots34 { public: virtual void slot38(); };
class Rva002BBF10Slots3C : public Rva002BBF10Slots38 { public: virtual void slot3C(); };
class Rva002BBF10Slots40 : public Rva002BBF10Slots3C { public: virtual void slot40(); };
class Rva002BBF10Slots44 : public Rva002BBF10Slots40 { public: virtual void slot44(); };

class Rva002BBF10Pointee : public Rva002BBF10Slots44
{
public:
	virtual bool dispatch();
};

class Rva002BBF10
{
	char m_lead[0x40];
	Rva002BBF10Pointee *m_pointee;

public:
	bool call();
};

bool Rva002BBF10::call()
{
	if (!m_pointee)
		return false;
	return m_pointee->dispatch();
}
