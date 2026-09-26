// Five __cdecl functions that lay a fixed 'T','R','P','C','D' skeleton into a
// caller-supplied byte buffer, interleaving four fields read straight out of a
// two-level object graph and two fields fetched by call:
//
//     eax = ref ; esi = buffer ; edi = [ref]        <- the ref's ONLY field
//     [esi+0] = 'T'  [esi+1] = byte [edi+0x14]
//     [esi+2] = 'R'  [esi+3] = byte [eax+0x0C]      <- from the REF, not the msg
//     [esi+4] = 'P'  [esi+5] = byte [edi+0x0C]
//     [esi+6] = 'C'  word [esi+7] = word [edi+0x10]
//     [esi+9] = 'D'  [esi+0x0A] = <call A on edi>
//                    dword [esi+0x0B..] = <call B on edi>
//
// WHAT THE BYTES SHOW.  The buffer is written a byte at a time at ASCENDING
// offsets with no gaps except the two-byte field at +7, so the layout is a
// packed wire record, not a struct assignment.  Field widths are read directly
// off the store: byte, byte, byte, WORD, then whatever the two calls return.
// The fourth field comes from the REFERENCE object (eax) while the rest come
// from what the reference points at (edi), so there really are two objects and
// the dereference happens once, before any store.
//
// Nothing reads ecx on entry and both arguments come off the stack before any
// push, so these are __cdecl -- a free function or a STATIC member, not an
// instance method, even though the callees they make are __thiscall.
//
// TWO AXES.  The callee pair, distinct in all five rows; and the WIDTH of the
// first fetched field, which is what moves the second store's offset:
//
//     byte  at +0x0A -> dword at +0x0B   (two rows, 80 bytes)
//     word  at +0x0A -> dword at +0x0C   (one row, 81 bytes: the 66 prefix)
//     dword at +0x0A -> dword at +0x0E   (two rows, 80 bytes)
//
// The 81-byte row is longer by exactly the operand-size prefix on its store,
// which is the only thing separating it from the byte rows.
//
// The two dword-payload records now use caller-proven type-8/type-9 message
// identities. Their getter ILTs resolve to the same bodies used by the matched
// leave-frame and replay-range handlers. The other address-derived identities
// remain unrecovered.

class Rva00677280Msg
{
public:
	unsigned char fetchA();
	unsigned int fetchB();
	char           m_pad0[ 0x0c ];
	unsigned char  m_type;
	char           m_pad1[ 3 ];
	unsigned short m_id;
	char           m_pad2[ 2 ];
	unsigned char  m_player;
};

class Rva00677280Ref
{
public:
	Rva00677280Msg *m_msg;
	char m_pad[ 8 ];
	unsigned char m_relay;
};

void Rva00677280( unsigned char *buffer, Rva00677280Ref *ref )
{
	Rva00677280Msg *msg = ref->m_msg;
	buffer[ 0 ] = 'T';
	buffer[ 1 ] = msg->m_player;
	buffer[ 2 ] = 'R';
	buffer[ 3 ] = ref->m_relay;
	buffer[ 4 ] = 'P';
	buffer[ 5 ] = msg->m_type;
	buffer[ 6 ] = 'C';
	*(unsigned short *)( buffer + 7 ) = msg->m_id;
	buffer[ 9 ] = 'D';
	buffer[ 10 ] = msg->fetchA();
	*(unsigned int *)( buffer + 11 ) = msg->fetchB();
}

class Rva006772F0Msg
{
public:
	unsigned char fetchA();
	unsigned int fetchB();
	char           m_pad0[ 0x0c ];
	unsigned char  m_type;
	char           m_pad1[ 3 ];
	unsigned short m_id;
	char           m_pad2[ 2 ];
	unsigned char  m_player;
};

class Rva006772F0Ref
{
public:
	Rva006772F0Msg *m_msg;
	char m_pad[ 8 ];
	unsigned char m_relay;
};

void Rva006772F0( unsigned char *buffer, Rva006772F0Ref *ref )
{
	Rva006772F0Msg *msg = ref->m_msg;
	buffer[ 0 ] = 'T';
	buffer[ 1 ] = msg->m_player;
	buffer[ 2 ] = 'R';
	buffer[ 3 ] = ref->m_relay;
	buffer[ 4 ] = 'P';
	buffer[ 5 ] = msg->m_type;
	buffer[ 6 ] = 'C';
	*(unsigned short *)( buffer + 7 ) = msg->m_id;
	buffer[ 9 ] = 'D';
	buffer[ 10 ] = msg->fetchA();
	*(unsigned int *)( buffer + 11 ) = msg->fetchB();
}

class Rva00677450Msg
{
public:
	unsigned short fetchA();
	unsigned int fetchB();
	char           m_pad0[ 0x0c ];
	unsigned char  m_type;
	char           m_pad1[ 3 ];
	unsigned short m_id;
	char           m_pad2[ 2 ];
	unsigned char  m_player;
};

class Rva00677450Ref
{
public:
	Rva00677450Msg *m_msg;
	char m_pad[ 8 ];
	unsigned char m_relay;
};

void Rva00677450( unsigned char *buffer, Rva00677450Ref *ref )
{
	Rva00677450Msg *msg = ref->m_msg;
	buffer[ 0 ] = 'T';
	buffer[ 1 ] = msg->m_player;
	buffer[ 2 ] = 'R';
	buffer[ 3 ] = ref->m_relay;
	buffer[ 4 ] = 'P';
	buffer[ 5 ] = msg->m_type;
	buffer[ 6 ] = 'C';
	*(unsigned short *)( buffer + 7 ) = msg->m_id;
	buffer[ 9 ] = 'D';
	*(unsigned short *)( buffer + 10 ) = msg->fetchA();
	*(unsigned int *)( buffer + 12 ) = msg->fetchB();
}

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	int getLeavingPlayerID();
	unsigned int getLeaveFrame();
	char           m_pad0[ 0x0c ];
	unsigned char  m_sourcePlayerID;
	char           m_pad1[ 3 ];
	unsigned short m_id;
	char           m_pad2[ 2 ];
	unsigned char  m_commandType;
};

class Rva006774C0Ref
{
public:
	BFMENetInformPlayerLeaveFrameCommandMsg *m_msg;
	char m_pad[ 8 ];
	unsigned char m_relay;
};

void Rva006774C0( unsigned char *buffer, Rva006774C0Ref *ref )
{
	BFMENetInformPlayerLeaveFrameCommandMsg *msg = ref->m_msg;
	buffer[ 0 ] = 'T';
	buffer[ 1 ] = msg->m_commandType;
	buffer[ 2 ] = 'R';
	buffer[ 3 ] = ref->m_relay;
	buffer[ 4 ] = 'P';
	buffer[ 5 ] = msg->m_sourcePlayerID;
	buffer[ 6 ] = 'C';
	*(unsigned short *)( buffer + 7 ) = msg->m_id;
	buffer[ 9 ] = 'D';
	*(unsigned int *)( buffer + 10 ) = msg->getLeavingPlayerID();
	*(unsigned int *)( buffer + 14 ) = msg->getLeaveFrame();
}

class BFMENetRequestFrameDataCommandMsg
{
public:
	unsigned int getFirstFrame();
	unsigned int getLastFrame();
	char           m_pad0[ 0x0c ];
	unsigned char  m_sourcePlayerID;
	char           m_pad1[ 3 ];
	unsigned short m_id;
	char           m_pad2[ 2 ];
	unsigned char  m_commandType;
};

class Rva00677590Ref
{
public:
	BFMENetRequestFrameDataCommandMsg *m_msg;
	char m_pad[ 8 ];
	unsigned char m_relay;
};

void Rva00677590( unsigned char *buffer, Rva00677590Ref *ref )
{
	BFMENetRequestFrameDataCommandMsg *msg = ref->m_msg;
	buffer[ 0 ] = 'T';
	buffer[ 1 ] = msg->m_commandType;
	buffer[ 2 ] = 'R';
	buffer[ 3 ] = ref->m_relay;
	buffer[ 4 ] = 'P';
	buffer[ 5 ] = msg->m_sourcePlayerID;
	buffer[ 6 ] = 'C';
	*(unsigned short *)( buffer + 7 ) = msg->m_id;
	buffer[ 9 ] = 'D';
	*(unsigned int *)( buffer + 10 ) = msg->getFirstFrame();
	*(unsigned int *)( buffer + 14 ) = msg->getLastFrame();
}

