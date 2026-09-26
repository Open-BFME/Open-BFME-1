// Twelve ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<HOLDER>] / mov eax,[eax+<INNER>] / ret
//
// Same shape as Q1HolderByteGetters.cpp with a DWORD load instead of a byte
// load.  All ten bytes are concrete -- no relocation site -- so both
// displacements and the operand size are read directly off the instruction
// stream.
//
// TWO AXES: the holder displacement (signed, disp8) and the inner displacement
// (disp32).  Two members reach the holder at a negative displacement (-0x1C)
// or at +0x34; the negative one is spelled as an explicit backward cast and no
// inheritance relationship is claimed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  A dword
// return is spelled `int`; the bytes cannot distinguish int from unsigned,
// from a pointer, or from any other four-byte type.

#define Q1_LOADEE( ADDR, INNER )                                          	class Inner##ADDR                                                     	{                                                                     	public:                                                               		char m_lead[ INNER ];                                             		int m_value;                                                       	};

#define Q1_HOLDER_AT( NAME, INNER, OFFSET )                               	class NAME                                                            	{                                                                     	public:                                                               		char m_lead[ OFFSET ];                                            		INNER *m_holder;                                                  		int get();                                                         	};                                                                    	int NAME::get()                                                        	{                                                                     		return m_holder->m_value;                                         	}

#define Q1_HOLDER_BEFORE( NAME, INNER, BACK )                             	class Sub##NAME                                                       	{                                                                     	public:                                                               		INNER *m_holder;                                                  	};                                                                    	class NAME                                                            	{                                                                     	public:                                                               		int get();                                                         	};                                                                    	int NAME::get()                                                        	{                                                                     		return ( (Sub##NAME *)( (char *)this - ( BACK ) ) )->m_holder->m_value; 	}

Q1_LOADEE( 001B2BC0, 0x4C0 )
Q1_LOADEE( 001B2BD0, 0x4C4 )
Q1_LOADEE( 001B2BE0, 0x4C8 )
Q1_LOADEE( 001B2BF0, 0x4CC )
Q1_LOADEE( 001B2C10, 0x124 )
Q1_LOADEE( 001BDD80, 0x4AC )
Q1_LOADEE( 001EABF0, 0x4D4 )
Q1_LOADEE( 002214E0, 0x140 )
Q1_LOADEE( 002A61A0, 0x218 )
Q1_LOADEE( 002A61B0, 0x1D8 )
Q1_LOADEE( 002DB1D0, 0x4D8 )
Q1_LOADEE( 0052CCA0, 0x250 )

Q1_HOLDER_AT( Rva001B2BC0, Inner001B2BC0, 4 )
Q1_HOLDER_AT( Rva001B2BD0, Inner001B2BD0, 4 )
Q1_HOLDER_AT( Rva001B2BE0, Inner001B2BE0, 4 )
Q1_HOLDER_AT( Rva001B2BF0, Inner001B2BF0, 4 )
Q1_HOLDER_AT( Rva001B2C10, Inner001B2C10, 4 )
Q1_HOLDER_AT( Rva001BDD80, Inner001BDD80, 4 )
Q1_HOLDER_AT( Rva001EABF0, Inner001EABF0, 4 )
Q1_HOLDER_BEFORE( Rva002214E0, Inner002214E0, 28 )
Q1_HOLDER_AT( Rva002A61A0, Inner002A61A0, 4 )
Q1_HOLDER_AT( Rva002A61B0, Inner002A61B0, 4 )
Q1_HOLDER_AT( Rva002DB1D0, Inner002DB1D0, 4 )
Q1_HOLDER_AT( Rva0052CCA0, Inner0052CCA0, 52 )
