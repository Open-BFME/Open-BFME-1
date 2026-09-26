// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: constructor at retail 0x009F2730, 146 bytes. The address-derived
// owner is shared with the matched destructor at 0x009F2800; that destructor
// proves the SubsystemInterface/Snapshot layout and owned 0xF4-byte state.

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
};

class Rva009F5970State
{
public:
	Rva009F5970State();

private:
	unsigned char m_storage[0xF4];
};

class Rva009F2730Owner : public SubsystemInterface, public Snapshot
{
public:
	Rva009F2730Owner();
	virtual ~Rva009F2730Owner();

private:
	Rva009F5970State *m_ownedState;
};

// ??0Rva009F2730Owner@@QAE@XZ
Rva009F2730Owner::Rva009F2730Owner()
	: m_ownedState(new Rva009F5970State)
{
}
