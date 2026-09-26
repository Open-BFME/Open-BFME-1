// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x000E9A40, 150 bytes. BfmeBaseVUQ (Snapshot) destructor
// family: own vtable 0x01084DF0 stored at entry, five destructible
// sub-objects torn down under an SEH frame (states 4..0), base vtable
// 0x01073744 restored implicitly via the base-class chain (no explicit call
// -- BfmeBaseVUQ's own destructor is trivial and MSVC inlines it).
//
// Unwind map (build/ehmap.py 0x011E89A8) confirms 5 states and that state
// 0's cleanup action calls ??1Snapshot@@UAE@XZ directly on `this`, i.e. the
// implicit base-class destructor -- matching BfmeBaseVUQ's real identity as
// Snapshot elsewhere in this codebase.
//
// Member shape read off the bytes:
//   +0x144  a ThingTemplate*-keyed _Rb_tree (retail dtor 0x0003D61D, already
//           matched/landed as the real STL symbol in
//           ThingTemplateRbTreeDestructorThunk.cpp) -- state 0, torn down LAST
//   +0x150  an array of 32 of the SAME tree shape (0xc bytes each = 0x180),
//           destroyed via the eh vector destructor iterator
//           (??_M@YGXPAXIHP6EX0@Z@Z); the per-element destructor pointer
//           pushed is the incremental-link thunk chain at 0x0001CDCD (->
//           0x000E9A30 -> 0x0003D61D), NOT the direct address the single
//           trees below call, so it needs its own address-derived pin --
//           state 1
//   +0x2D0  a second lone tree -- state 2
//   +0x2DC  a third lone tree -- state 3
//   +0x2E8  a StringBase<unsigned short> (UnicodeString) releaseBuffer
//           (retail 0x008881D0) -- state 4, torn down FIRST
//
// IDENTITY IS NOT FULLY RECOVERED: the field shape (three lone ThingTemplate
// count-maps, one MAX_PLAYER_COUNT-sized array of the same map, a
// UnicodeString) strongly resembles a ScoreKeeper-shaped tally object, but no
// exact matching ZH header carries a UnicodeString alongside the three ZH
// ScoreKeeper maps, so this stays address-derived.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) { }
};

class BfmeMapTree000E9A40
{
public:
	~BfmeMapTree000E9A40(void);				// retail 0x0003D61D

private:
	unsigned char m_pad[0xc];
};

class BfmeArrTree000E9A40
{
public:
	~BfmeArrTree000E9A40(void);				// retail 0x0001CDCD (thunk chain -> 0x0003D61D)

private:
	unsigned char m_pad[0xc];
};

class BfmeDtorMemberG000E9A40
{
public:
	~BfmeDtorMemberG000E9A40(void);			// retail 0x008881D0

private:
	void *m_data;
};

class Rva000E9A40 : public BfmeBaseVUQ
{
public:
	virtual ~Rva000E9A40(void);
	virtual void bfmePure000E9A40(void) = 0;	// keeps MSVC from emitting its own vftable

private:
	unsigned char m_pad004[0x140];				// +0x04, untouched by this body
	BfmeMapTree000E9A40 m_map0;				// +0x144
	BfmeArrTree000E9A40 m_arr[0x20];			// +0x150
	BfmeMapTree000E9A40 m_map2;				// +0x2D0
	BfmeMapTree000E9A40 m_map3;				// +0x2DC
	BfmeDtorMemberG000E9A40 m_str;				// +0x2E8
};

// @??1Rva000E9A40@@UAE@XZ 0x000E9A40
Rva000E9A40::~Rva000E9A40(void)
{
}
