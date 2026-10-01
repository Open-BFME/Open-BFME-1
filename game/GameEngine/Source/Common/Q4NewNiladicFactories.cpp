// cl: /EHsc
//
// Eleven 89-byte free functions that allocate one object and default-construct
// it:
//
//     push <SIZE> / call operator new / add esp,4
//     test eax,eax / je null
//     mov ecx,eax / call <CTOR>
//     return eax          (null path returns 0 without calling the ctor)
//
// WHAT THE BYTES SHOW.  Same `new` expression as Q4NewOwnerFactories.cpp with
// one field removed: NOTHING IS PUSHED FOR THE CONSTRUCTOR.  The call is
// entered with ecx alone and the caller does not pop, so the constructor is
// __thiscall with no arguments -- a default constructor.  SIZE is therefore
// `sizeof` the constructed class exactly, as it is there.
//
// THESE ARE NOT MEMBERS.  The receiver is never copied out of ecx: the `push
// ecx` at offset 0x15 is the frame reserve for the one local (the raw block,
// stored at [esp]), and the four-byte offsets of every later stack reference
// count from that same slot.  A __thiscall member that ignored its `this`
// would still be indistinguishable, so what the bytes establish is only that
// no argument and no receiver field is read -- they are spelled here as
// niladic free functions because that asserts the least.
//
// The fs:[0] frame is `-EHsc`, exactly as in the owner-argument family; the
// pushed handler address is a DIR32 operand copied from retail and proves
// nothing.
//
// THE VARYING AXIS IS TWO FIELDS: the allocation size and the constructor's
// REL32.  Eleven members, eleven distinct constructors, eleven distinct sizes
// (0x80..0x3060) -- no repeat on either field, so the pairing is read straight
// off and nothing is over-fitted.  Note the sizes are all above 0x7f, so every
// one encodes as `push imm32`; the owner-argument family's smaller sizes use
// `push imm8`, which is why the two families group apart despite the same
// source shape.
//
// The factories retain their ledger return types and construct the row types.
// Each storage declaration carries the retail allocation size without claiming a field layout.

#define Q4_NEW_NILADIC_ROW_FACTORY(GEN, ROW, SIZE, MAKER) \
    class GEN; \
    class ROW { public: ROW(); char m_storage[SIZE]; }; \
    GEN *MAKER() { return reinterpret_cast<GEN *>(new ROW); }

#define Q4_NEW_NILADIC_FACTORY( GEN, SIZE, MAKER )                         \
	class GEN                                                              \
	{                                                                      \
	public:                                                                \
		GEN();                                                             \
		char m_storage[ SIZE ];                                            \
	};                                                                     \
	GEN *MAKER()                                                           \
	{                                                                      \
		return new GEN;                                                    \
	}

Q4_NEW_NILADIC_ROW_FACTORY( Gen0048D200, IMEManager, 0x3060, make0048D380 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen00642300, Rva00641C60Queue, 0x80,   make006426E0 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen00660FD0, Pinger, 0xb4,   make00661490 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen006B0E00, MilesAudioManager, 0xb78,  make006B5890 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen006FB500, Rva006FB500, 0x11c,  make006BA850 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen006C1D70, W3DRadar, 0x1508, make006BAA10 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen0078ABB0, Rva0078ABB0, 0x1c8,  make006BAA90 )
Q4_NEW_NILADIC_FACTORY( Gen006EF850, 0x2a8,  make006FB520 )
Q4_NEW_NILADIC_FACTORY( Gen006E2310, 0xf8,   make006FB8E0 )
Q4_NEW_NILADIC_ROW_FACTORY( Gen00745B10, Rva00745B10Owner, 0x24e4, make006FBE60 )
Q4_NEW_NILADIC_FACTORY( Gen0078D1C0, 0xe0,   make0078F5C0 )
