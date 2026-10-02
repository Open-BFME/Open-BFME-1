// Two-instruction __thiscall members with one shape:
//
//     mov eax,ecx / ret
//
// Each returns `this` and pops nothing.  Every body here sits in a .text gap
// no ledger row covered: it starts on a 16-byte boundary right after an int3
// pad run and its `ret` is followed by int3 padding, so both ends are proven
// by the retail layout.  Retail was linked without identical-COMDAT folding,
// so each address is its own function even though the bytes repeat.  Most are
// unreferenced (no call, ILT stub or table slot reaches them); the notes
// column of each row lists the references that do exist.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.
#define BFME_THIS_RETURNER( NAME )                                            \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME *self();                                                         \
	};                                                                        \
	NAME *NAME::self()                                                        \
	{                                                                         \
		return this;                                                          \
	}

BFME_THIS_RETURNER( Rva007F21A0Self )
BFME_THIS_RETURNER( Rva007F90A0Self )
BFME_THIS_RETURNER( Rva00808840Self )
BFME_THIS_RETURNER( Rva0081D440Self )
BFME_THIS_RETURNER( Rva00846060Self )
BFME_THIS_RETURNER( Rva00846070Self )
BFME_THIS_RETURNER( Rva008483F0Self )
BFME_THIS_RETURNER( Rva00850CB0Self )
BFME_THIS_RETURNER( Rva00891730Self )
BFME_THIS_RETURNER( Rva00898110Self )
BFME_THIS_RETURNER( Rva00898150Self )
BFME_THIS_RETURNER( Rva00898160Self )
BFME_THIS_RETURNER( Rva00898170Self )
BFME_THIS_RETURNER( Rva00898190Self )
BFME_THIS_RETURNER( Rva008A0660Self )
BFME_THIS_RETURNER( Rva008A4530Self )
BFME_THIS_RETURNER( Rva008ABFD0Self )
BFME_THIS_RETURNER( Rva008B2BA0Self )
BFME_THIS_RETURNER( Rva008B38B0Self )
BFME_THIS_RETURNER( Rva008B4250Self )
BFME_THIS_RETURNER( Rva008B56A0Self )
BFME_THIS_RETURNER( Rva008BA8A0Self )
BFME_THIS_RETURNER( Rva008C4910Self )
BFME_THIS_RETURNER( Rva008C4920Self )
BFME_THIS_RETURNER( Rva008C4930Self )
BFME_THIS_RETURNER( Rva008D66F0Self )
BFME_THIS_RETURNER( Rva008DD700Self )
BFME_THIS_RETURNER( Rva008F8E80Self )
BFME_THIS_RETURNER( Rva008FE940Self )
BFME_THIS_RETURNER( Rva0090C680Self )
BFME_THIS_RETURNER( Rva0091DB80Self )
BFME_THIS_RETURNER( Rva00921350Self )
BFME_THIS_RETURNER( Rva00921360Self )
BFME_THIS_RETURNER( Rva00923BA0Self )
BFME_THIS_RETURNER( Rva00923BE0Self )
BFME_THIS_RETURNER( Rva0092C710Self )
BFME_THIS_RETURNER( Rva0092C720Self )
BFME_THIS_RETURNER( Rva0092C880Self )
BFME_THIS_RETURNER( Rva0093C960Self )
BFME_THIS_RETURNER( Rva0094BC90Self )
BFME_THIS_RETURNER( Rva0094BCC0Self )
BFME_THIS_RETURNER( Rva0094DF80Self )
BFME_THIS_RETURNER( Rva009587D0Self )
BFME_THIS_RETURNER( Rva0095C6C0Self )
BFME_THIS_RETURNER( Rva0095C810Self )
BFME_THIS_RETURNER( Rva0095C820Self )
BFME_THIS_RETURNER( Rva0095C830Self )
BFME_THIS_RETURNER( Rva009600C0Self )
BFME_THIS_RETURNER( Rva009600D0Self )
BFME_THIS_RETURNER( Rva009600E0Self )
BFME_THIS_RETURNER( Rva0096B4C0Self )
BFME_THIS_RETURNER( Rva0096CB60Self )
BFME_THIS_RETURNER( Rva0096D130Self )
BFME_THIS_RETURNER( Rva00972330Self )
BFME_THIS_RETURNER( Rva00974EE0Self )
BFME_THIS_RETURNER( Rva00975070Self )
BFME_THIS_RETURNER( Rva00975080Self )
BFME_THIS_RETURNER( Rva00979390Self )
BFME_THIS_RETURNER( Rva0097EDE0Self )
BFME_THIS_RETURNER( Rva0098D220Self )
BFME_THIS_RETURNER( Rva009A1720Self )
BFME_THIS_RETURNER( Rva009A2D00Self )
BFME_THIS_RETURNER( Rva009A2FA0Self )
BFME_THIS_RETURNER( Rva009A3380Self )
BFME_THIS_RETURNER( Rva009C8E90Self )
BFME_THIS_RETURNER( Rva009C8EB0Self )
BFME_THIS_RETURNER( Rva009CB9E0Self )
BFME_THIS_RETURNER( Rva009CE610Self )
BFME_THIS_RETURNER( Rva009CE630Self )
BFME_THIS_RETURNER( Rva009D1BE0Self )
BFME_THIS_RETURNER( Rva009D6F20Self )
BFME_THIS_RETURNER( Rva009D6F60Self )
BFME_THIS_RETURNER( Rva009E1260Self )
BFME_THIS_RETURNER( Rva009EA7B0Self )
BFME_THIS_RETURNER( Rva009EA7C0Self )
BFME_THIS_RETURNER( Rva009ECA80Self )
BFME_THIS_RETURNER( Rva009ECB00Self )
BFME_THIS_RETURNER( Rva009ECB60Self )
BFME_THIS_RETURNER( Rva009ED260Self )
BFME_THIS_RETURNER( Rva009F2C40Self )
BFME_THIS_RETURNER( Rva009F4430Self )
BFME_THIS_RETURNER( Rva009F4480Self )
