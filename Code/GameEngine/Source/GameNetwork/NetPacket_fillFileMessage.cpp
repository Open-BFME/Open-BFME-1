// cl: /DNDEBUG /MD /EHsc
// readable body of ?FillBufferWithFileMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// Retail 0x0067D740. Zero Hour's FillBufferWithFileMessage field for
// field, and it pairs with GetFileCommandSize at 0x0067D410: the same
// 'T'/'R'/'P'/'C'/'D' header, the filename with its terminator, then the file id
// and the player mask, adding up to the namelen + 0xE that helper returns.
//
// Named by its getters, all three already ledgered:
// ?getPortableFilename@NetFileCommandMsg, ?getFileLength@... and ?getFileData@...,
// reached in exactly Zero Hour's order -- including the second getFileLength call
// Zero Hour makes for the dead final offset bump.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;			// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }
	T getCharAt(Int index) const { return m_data ? ((const T *)(m_data + 1))[index] : 0; }

private:
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }	// Int, not Zero Hour's UnsignedByte: retail reads the whole dword and narrows at the store
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }

	StringBase<char> getPortableFilename(void);	// ILT thunk 0x00044323
	UnsignedInt getFileLength(void);		// ILT thunk 0x0001E7BD
	UnsignedByte *getFileData(void);		// ILT thunk 0x0003B598

	unsigned char m_bfmeHead[0x0C];
	Int m_playerID;					// +0x0C
	UnsignedShort m_id;				// +0x10
	UnsignedShort m_pad;
	Int m_commandType;				// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_command; }
	UnsignedByte getRelay(void) { return m_relay; }

	NetCommandMsg *m_command;			// +0x00
	unsigned char m_bfmeMiddle[0x0C - 4];
	UnsignedByte m_relay;				// +0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithFileMessage(UnsignedByte *buffer, NetCommandRef *msg);
};

// ?FillBufferWithFileMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithFileMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetFileCommandMsg *cmdMsg = (NetFileCommandMsg *)(msg->getCommand());
	UnsignedInt offset = 0;

	// command type
	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	// relay
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);

	// player ID
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	// command ID
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(newID));
	offset += sizeof(newID);

	// data
	buffer[offset] = 'D';
	++offset;

	StringBase<char> filename = cmdMsg->getPortableFilename();	// PORTABLE
	for (Int i = 0; i < filename.getLength(); ++i) {
		buffer[offset] = filename.getCharAt(i);
		++offset;
	}
	buffer[offset] = 0;
	++offset;

	UnsignedInt newInt = cmdMsg->getFileLength();
	memcpy(buffer + offset, &newInt, sizeof(newInt));
	offset += sizeof(newInt);

	memcpy(buffer + offset, cmdMsg->getFileData(), cmdMsg->getFileLength());
	offset += cmdMsg->getFileLength();
}
