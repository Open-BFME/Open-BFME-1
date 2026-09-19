// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DelayedLuaEventList::DelayedLuaEventList, retail 0x000EDBB0, 84
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real.
//
// The constructor's whole job is the vtable store at +0 and one call to the EH
// vector constructor iterator at 0x009F6EE4. Its five arguments spell the
// member out: the array starts at +4, the elements are 0x18 bytes, there are
// three of them, and each has both a constructor and a destructor -- which is
// why this is the EH iterator rather than a plain loop.

class BfmeDelayedLuaEvent
{
public:
	BfmeDelayedLuaEvent(void);				// ILT 0x0003A1C5
	~BfmeDelayedLuaEvent(void);				// ILT 0x00041362

private:
	char m_bfmeBody[0x18];
};

// The frame is an unwind frame with one state, which means something already
// constructed has to be torn down if the array constructor throws. The vtable
// store is the only other thing the body does, so the something is an empty
// base with a destructor: it contributes no layout, which is why the array
// still starts at +4.
class BfmeDelayedLuaEventListBase
{
public:
	~BfmeDelayedLuaEventListBase(void);
};

class DelayedLuaEventList : public BfmeDelayedLuaEventListBase
{
public:
	DelayedLuaEventList(void);

	virtual ~DelayedLuaEventList(void);

private:
	BfmeDelayedLuaEvent m_bfmeEvents[3];			// +0x04
};

// ??0DelayedLuaEventList@@QAE@XZ
DelayedLuaEventList::DelayedLuaEventList(void)
{
}
