// Thirteen ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<HOLDER>] / mov al,[eax+<INNER>] / ret
//
// WHAT THE BYTES SHOW.  A dword is read out of the object and used as a base;
// one BYTE is then read at a fixed displacement from it and left in al.  All
// ten bytes are concrete -- there is no relocation site here -- so the two
// displacements and the operand size are read directly off the instruction
// stream and nothing else about these functions is asserted.
//
// TWO AXES: the holder displacement (signed, disp8) and the inner displacement
// (disp32).  Three members reach the holder at a NEGATIVE displacement (-0x28,
// -0x1C); the bytes cannot say whether that is a sub-object `this` pointing
// into the middle of a larger object, a container-of computation in the source,
// or something else, so those are spelled as an explicit backward cast and no
// inheritance relationship is claimed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// return type is spelled `char` because the load is `mov al` and the upper
// bytes of eax are left holding the base pointer; the bytes cannot distinguish
// `char` from `signed char` or from a one-byte enum.

#define Q1_LOADEE( ADDR, INNER )                                          	class Inner##ADDR                                                     	{                                                                     	public:                                                               		char m_lead[ INNER ];                                             		char m_value;                                                       	};

#define Q1_HOLDER_AT( NAME, INNER, OFFSET )                               	class NAME                                                            	{                                                                     	public:                                                               		char m_lead[ OFFSET ];                                            		INNER *m_holder;                                                  		char get();                                                         	};                                                                    	char NAME::get()                                                        	{                                                                     		return m_holder->m_value;                                         	}

#define Q1_HOLDER_BEFORE( NAME, INNER, BACK )                             	class Sub##NAME                                                       	{                                                                     	public:                                                               		INNER *m_holder;                                                  	};                                                                    	class NAME                                                            	{                                                                     	public:                                                               		char get();                                                         	};                                                                    	char NAME::get()                                                        	{                                                                     		return ( (Sub##NAME *)( (char *)this - ( BACK ) ) )->m_holder->m_value; 	}

Q1_LOADEE( 000C4510, 0x214 )
Q1_LOADEE( 001500A0, 0x532 )
Q1_LOADEE( 0016A9C0, 0x529 )
Q1_LOADEE( 001E0DC0, 0x534 )
Q1_LOADEE( 001EAC00, 0x4FA )
Q1_LOADEE( 001EAC20, 0x4FB )
Q1_LOADEE( 001EAC30, 0x4DC )
Q1_LOADEE( 001ECEA0, 0x51E )
Q1_LOADEE( 0020A9D0, 0xB0 )
Q1_LOADEE( 0021B8C0, 0x171 )
Q1_LOADEE( 00280010, 0x80 )
Q1_LOADEE( 00289AD0, 0x84 )
Q1_LOADEE( 002D4560, 0x80 )

Q1_HOLDER_AT( Rva000C4510, Inner000C4510, 4 )
Q1_HOLDER_AT( Rva001500A0, Inner001500A0, 4 )
Q1_HOLDER_AT( Rva0016A9C0, Inner0016A9C0, 4 )
Q1_HOLDER_AT( Rva001E0DC0, Inner001E0DC0, 4 )
Q1_HOLDER_AT( Rva001EAC00, Inner001EAC00, 4 )
Q1_HOLDER_AT( Rva001EAC20, Inner001EAC20, 4 )
Q1_HOLDER_AT( Rva001EAC30, Inner001EAC30, 4 )
Q1_HOLDER_AT( Rva001ECEA0, Inner001ECEA0, 4 )
Q1_HOLDER_BEFORE( Rva0020A9D0, Inner0020A9D0, 40 )
Q1_HOLDER_BEFORE( Rva0021B8C0, Inner0021B8C0, 28 )
Q1_HOLDER_BEFORE( Rva00280010, Inner00280010, 28 )
Q1_HOLDER_BEFORE( Rva00289AD0, Inner00289AD0, 28 )
Q1_HOLDER_AT( Rva002D4560, Inner002D4560, 4 )

class Rva001E0DD0
{
public:
	char get();

	char m_lead[ 0x4C ];
};

char Rva001E0DD0::get()
{
	return m_lead[ 0x4C ];
}
