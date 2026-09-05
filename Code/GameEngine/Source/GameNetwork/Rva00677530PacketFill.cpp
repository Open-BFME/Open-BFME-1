// cl: /O2
// cdecl @ 0x00677530, 66 bytes. Twin of 0x00677600
// (NetPacket::FillBufferWithDisconnectFrameMessage): same 'T'/'R'/'P'/'C'/'D'
// tag-and-copy shape over a different command-message layout, with the
// final 4-byte field read through a same-shaped (ICF-folded) getter call.
// Address-derived — owning types are not recovered.
#include <string.h>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

struct Rva00677530CmdMsg
{
	unsigned char pad0[0xc];
	UnsignedByte playerID;			// +0xC
	unsigned char pad1[3];
	UnsignedShort id;			// +0x10
	unsigned char pad2[2];
	UnsignedByte commandType;		// +0x14

	UnsignedInt getPayload() const;
};

struct Rva00677530Ref
{
	unsigned char pad0[0xc];
	UnsignedByte relay;			// +0xC
	Rva00677530CmdMsg *m_command;		// +0x0 (read via [eax])
};

void FillBufferWithRva00677530Message(UnsignedByte *buffer, Rva00677530Ref *msg)
{
	Rva00677530CmdMsg *cmdMsg = *(Rva00677530CmdMsg **)msg;
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->commandType;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->relay;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->playerID;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->id;
	memcpy(buffer + offset, &newID, sizeof(newID));
	offset += sizeof(newID);

	buffer[offset] = 'D';
	++offset;

	UnsignedInt payload = cmdMsg->getPayload();
	memcpy(buffer + offset, &payload, sizeof(payload));
	offset += sizeof(payload);
}
