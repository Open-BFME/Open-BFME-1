// Five 54-byte __thiscall members that report a fixed string through a global
// sink when a global flag is set, then consume one unit of a signed countdown:
//
//     mov al,[FLAG] / test al,al / push esi / mov esi,ecx / je .1 /
//     mov eax,[SINK] / test eax,eax / je .1 /
//     push <literal> / push eax / call <REL32> / add esp,8 /
//  .1 mov eax,[esi+0x50] / test eax,eax / jle .2 /
//     dec eax / mov [esi+0x50],eax / mov al,1 / pop esi / ret
//  .2 xor al,al / pop esi / ret
//
// WHAT THE BYTES SHOW.  Both guards branch to the SAME label, which is the
// short-circuit `&&`, not two nested statements with separate tails.  The flag
// is read a byte at a time and tested against zero: a bool/char global, not an
// int.  The report call pushes two dwords and the CALLER pops them, so it is
// __cdecl and takes (sink, text) in that order.  `test eax,eax / jle` is the
// SIGNED greater-than-zero test, so the countdown is a signed int, and the
// decrement reuses the already-loaded value rather than re-reading the member.
// al is set to 1 or cleared, so the return type is one byte wide.
//
// THE FIVE LITERALS ARE RECOVERED FROM RETAIL and are the only thing that
// varies: "CritterDesync: ComputePath5" through "...9".  Flag, sink, callee,
// member offset and the whole control flow are identical in all five rows.
//
// IDENTITY IS NOT RECOVERED.  The bytes CANNOT say whether these are five
// members of one class or one member of each of five classes -- the layout and
// every global are the same either way.  One address-derived class per row is
// written here because that asserts nothing about the other four.

extern bool TheS3Flag;
extern void *TheS3Sink;
extern void Gen0003A17A( void *sink, const char *text );

#define S3_CRITTER( NAME, TEXT )                                          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool step();                                                      \
		char m_lead[ 80 ];                                                \
		int m_countdown;                                                  \
	};                                                                    \
	bool NAME::step()                                                     \
	{                                                                     \
		if( TheS3Flag && TheS3Sink )                                      \
			Gen0003A17A( TheS3Sink, TEXT );                               \
		if( m_countdown > 0 )                                             \
		{                                                                 \
			--m_countdown;                                                \
			return true;                                                  \
		}                                                                 \
		return false;                                                     \
	}

S3_CRITTER( Rva0016B400, "CritterDesync: ComputePath5" )
S3_CRITTER( Rva0016B450, "CritterDesync: ComputePath6" )
S3_CRITTER( Rva0016B550, "CritterDesync: ComputePath7" )
S3_CRITTER( Rva0016B770, "CritterDesync: ComputePath8" )
S3_CRITTER( Rva0016B840, "CritterDesync: ComputePath9" )

struct AIUpdate0016B2C0
{
	char m_pad326[0x326];
	bool m_flag326;
	bool m_pad327;
	bool m_flag328;
};

struct Object0016B2C0
{
	char m_pad204[0x204];
	AIUpdate0016B2C0 *m_ai;
};

struct Intermediate0016B2C0
{
	char m_pad10[0x10];
	Object0016B2C0 *m_object;
};

class Rva0016B2C0
{
public:
	bool step();

	char m_pad1C[0x1c];
	Intermediate0016B2C0 *m_intermediate;
	char m_pad4D[0x4d - 0x20];
	bool m_flag4D;
};

bool Rva0016B2C0::step()
{
	if( TheS3Flag && TheS3Sink )
		Gen0003A17A( TheS3Sink, "CritterDesync: ComputePath3" );

	Intermediate0016B2C0 *it = m_intermediate;
	Object0016B2C0 *obj = it->m_object;
	AIUpdate0016B2C0 *ai = obj->m_ai;
	m_flag4D = true;
	if( ai->m_flag326 )
	{
		ai->m_flag328 = true;
		ai->m_flag326 = false;
	}
	return true;
}

