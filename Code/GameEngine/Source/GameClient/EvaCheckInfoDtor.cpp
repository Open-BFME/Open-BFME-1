// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FILE: EvaCheckInfoDtor.cpp /////////////////////////////////////////////////
//
// EvaCheckInfo::~EvaCheckInfo, retail 0x0089A830.
//
// Not written into Eva.cpp, which already owns 45 byte-matched rows through the
// reference GameClient/Eva.h: retail destroys m_evaSideSounds at +0x8, and that
// header puts it at +0x14 behind m_framesBetweenChecks, m_framesToExpire and
// m_priority.  BFME's EvaCheckInfo carries m_message and then the vector, so
// the layout is a TU-local fact and gets spelled here rather than in a header
// eighteen sources include.
//
///////////////////////////////////////////////////////////////////////////////

// The member at +0x8 is NOT an STLport vector, which is what the work packet
// guessed.  Its destructor at 0x0089C900 (reached through the thunk at
// 0x0089CC70) walks a count at +0x0 over an array at +0x4 with an element
// stride of eight, releases two more owned pointers at +0x8 and +0xC through
// vtable slot 1 behind a tagged-pointer test, and frees the array with the
// CRT free import rather than an allocator.  STLport's vector has three
// pointers and no count.  So the type is spelled provisionally, by shape, and
// its name is marked Bfme* the way the other structurally-named pins in
// reverse/symbols.csv are: nothing here depends on the name being right, only
// on the call landing at 0x0089CC70.
//
// What the same destructor does prove about the element type: the first dword
// of each eight-byte element is an AsciiString buffer (it is compared against
// the empty-string singleton at 0x012D5298, then its UnsignedShort refcount is
// decremented and the buffer returned to the pool at 0x01337A30), and the
// second is an owned object released through vtable slot 1.  ZH's
// EvaSideSounds is sixteen bytes -- an AsciiString plus a vector<AsciiString>
// -- so BFME collapsed the sound list to a single owned pointer.
class BfmeEvaSideSoundsArray
{
public:
	~BfmeEvaSideSoundsArray();
private:
	int m_count;
	void *m_elements;
	void *m_owned1;
	void *m_owned2;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
protected:
	// Inline and empty, which is all retail keeps of it: the second store of a
	// vtable pointer into [esi] is this destructor.
	virtual ~MemoryPoolObject() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class EvaCheckInfo : public MemoryPoolObject
{
public:

	int m_message;																	// @0x4
	BfmeEvaSideSoundsArray m_evaSideSounds;					// @0x8

protected:

	virtual ~EvaCheckInfo();

};

EvaCheckInfo::~EvaCheckInfo()
{
}
