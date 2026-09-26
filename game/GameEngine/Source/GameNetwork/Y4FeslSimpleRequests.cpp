// EA FESL client SDK ("jabba") -- the payload-free transaction request
// builders.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  Each
// row is nothing but `reset(); category = <FourCC>; depth = 3;`, so the ONLY
// thing that distinguishes one from another is the un-relocated imm32 written
// to +0x1C.  Those five FourCCs -- 'DISC', 'EPGT', 'RLST', 'RGAM', 'PING' --
// are hard evidence and are the whole content of these bodies.
//
// 0x007FBA70 is the one exception: it also stores its two remaining arguments
// into the message at +0x10 and +0x14, the buffer/size pair the V2 lane
// recovered for this object, so it is modelled with those two members named.

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0

	char m_head[ 0x10 ];
	void *m_buffer;                 // +0x10
	int m_bufferSize;               // +0x14
	char m_gap[ 0x04 ];
	unsigned int m_category;        // +0x1C
	char m_tail[ 0x0C ];
	int m_depth;                    // +0x2C
};

void __stdcall Rva007FAF90( Rva007E8810Message *msg )
{
	msg->reset();
	msg->m_category = 'DISC';
	msg->m_depth = 3;
}

void __stdcall Rva007FBA50( Rva007E8810Message *msg )
{
	msg->reset();
	msg->m_category = 'EPGT';
	msg->m_depth = 3;
}

void __stdcall Rva007FBA70( Rva007E8810Message *msg, void *buffer, int bufferSize )
{
	msg->reset();
	msg->m_category = 'PING';
	msg->m_depth = 3;
	msg->m_buffer = buffer;
	msg->m_bufferSize = bufferSize;
}

void __stdcall Rva007FC270( Rva007E8810Message *msg )
{
	msg->reset();
	msg->m_category = 'RLST';
	msg->m_depth = 3;
}

void __stdcall Rva007FCC80( Rva007E8810Message *msg )
{
	msg->reset();
	msg->m_category = 'RGAM';
	msg->m_depth = 3;
}

void __stdcall Rva007FCCA0( Rva007E8810Message *msg )
{
	msg->reset();
	msg->m_category = 'PING';
	msg->m_depth = 3;
}
