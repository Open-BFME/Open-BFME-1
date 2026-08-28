// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x0005F5E0, 59 bytes. reverse/reloc_names.csv holds the name with
// identity=real.
//
// The store of a fixed address into +0x04 reads like a destructor restoring a
// vptr, but it is not one: MSVC always puts a new vptr at offset 0 and pushes
// non-polymorphic bases behind it, so a vptr at +0x04 with a four-byte base in
// front of it is a layout the compiler will not produce. Modelling it as a
// polymorphic base compiles the store to [esi] and nothing else moves. It is
// an ordinary pointer member being pointed back at a shared table, and the
// address rides a DIR32 relocation copied from retail either way.
//
// What is a base is the sub-object at +0x00: the tail jump hands ecx over
// with no adjustment, which is where a first base's destructor expects it.
// That destructor is the 13-byte body at 0x008FC5B0 that releases a surface
// through vtable slot 2; identical-code folding put several classes on it and
// its ledger row carries the name ??1W3DRadarResetSurface@@QAE@XZ, so the base
// is spelled that way to reach the address.
//
// The rest is this class's own: the buffer at +0x08 released with operator
// delete[] and no element loop, so its elements have no destructor; the word
// at +0x0C; and the flag at +0x11 that has to be set before the buffer is
// worth releasing.

typedef int Int;
typedef bool Bool;

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();				// retail 0x008FC5B0

private:
	void *m_bfmeSurface;					// +0x00
};

extern void *BfmeSentenceSurfaceTable[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	class PendingSurfaceStruct : public W3DRadarResetSurface
	{
	public:
		~PendingSurfaceStruct();

	private:
		void *m_bfme0004;				// +0x04
		char *m_bfmeBuffer;				// +0x08
		Int m_bfme000C;					// +0x0C
		char m_bfme0010;				// +0x10
		Bool m_bfmeBufferOwned;				// +0x11
	};
};

// ??1PendingSurfaceStruct@Render2DSentenceClass@@QAE@XZ
Render2DSentenceClass::PendingSurfaceStruct::~PendingSurfaceStruct()
{
	m_bfme0004 = BfmeSentenceSurfaceTable;

	if (m_bfmeBuffer && m_bfmeBufferOwned)
	{
		delete [] m_bfmeBuffer;

		m_bfmeBuffer = 0;
	}

	m_bfmeBufferOwned = false;
	m_bfme000C = 0;
}
