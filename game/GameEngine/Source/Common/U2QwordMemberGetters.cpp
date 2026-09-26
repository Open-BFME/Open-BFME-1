// Three seven-byte accessors that return an eight-byte member in edx:eax:
//
//     mov eax,[ecx+DISP] / mov edx,[ecx+DISP+4] / ret
//
// `this` arrives in ecx, nothing is pushed and the function returns with `ret`
// rather than `ret 4`, so there is no hidden return-value pointer: the return
// type is one the MSVC 7.1 ABI hands back in the register pair, i.e. eight
// bytes wide and not a class with a non-trivial copy.  The two loads are
// adjacent and in ascending order, which is the whole body -- no shift, no
// arithmetic, no second member -- so the source is a plain `return m_x;` of a
// 64-bit integer member.
//
// The three differ only in the displacement (+0x70, +0x10, +0x18), and nothing
// in the image witnesses a name for either the holders or the member, so each
// class is named after its own address.  They are kept as three separate
// classes rather than one with three members because nothing here ties any two
// of the three addresses together.

#define U2_QWORD_GETTER( NAME, PAD )                                          	class NAME                                                                	{                                                                         	public:                                                                   		__int64 get() const;                                                                                                                                		char m_head[ PAD ];                                                   		__int64 m_value;                                                      	};                                                                        	__int64 NAME::get() const                                                 	{                                                                         		return m_value;                                                       	}

U2_QWORD_GETTER( Rva008012F0Owner, 0x70 )
U2_QWORD_GETTER( Rva00802230Owner, 0x10 )
U2_QWORD_GETTER( Rva008022F0Owner, 0x18 )
