// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "GameNetwork/NetCommandMsg.h"

class BfmeNetGameMessageArgument
{
public:
	BfmeNetGameMessageArgument() {}
	virtual ~BfmeNetGameMessageArgument() {}

	BfmeNetGameMessageArgument *m_next;
	GameMessageArgumentType m_data;
	GameMessageArgumentDataType m_type;
};

NetCommandMsg::~NetCommandMsg()
{
}

void NetGameCommandMsg::addArgument(
	const GameMessageArgumentDataType type, GameMessageArgumentType arg)
{
	if (m_argTail == NULL) {
		BfmeNetGameMessageArgument *newArg = new BfmeNetGameMessageArgument;
		m_argList = reinterpret_cast<GameMessageArgument *>(newArg);
		m_argTail = m_argList;
		m_argList->m_data = arg;
		m_argList->m_type = type;
		m_argList->m_next = NULL;
		return;
	}

	GameMessageArgument *newArg = reinterpret_cast<GameMessageArgument *>(
		new BfmeNetGameMessageArgument);
	newArg->m_data = arg;
	newArg->m_type = type;
	newArg->m_next = NULL;
	m_argTail->m_next = newArg;
	m_argTail = newArg;
}

__declspec(naked) void NetCommandMsg::detach()
{
	__asm {
		mov eax, [ecx + 18h]
		dec eax
		mov [ecx + 18h], eax
		_emit 075h
		_emit 007h
		mov eax, [ecx]
		push 1
		call dword ptr [eax]
		ret
	}
}

NetWrapperCommandMsg::~NetWrapperCommandMsg()
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}
}

void NetWrapperCommandMsg::setData(UnsignedByte *data, UnsignedInt dataLength)
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}

	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
	m_dataLength = dataLength;
}

UnsignedByte * NetWrapperCommandMsg::getData()
{
	return m_data;
}

UnsignedInt NetWrapperCommandMsg::getDataLength()
{
	return m_dataLength;
}

UnsignedInt NetWrapperCommandMsg::getDataOffset()
{
	return m_dataOffset;
}

void NetWrapperCommandMsg::setDataOffset(UnsignedInt offset)
{
	m_dataOffset = offset;
}

UnsignedInt NetWrapperCommandMsg::getTotalDataLength()
{
	return m_totalDataLength;
}

void NetWrapperCommandMsg::setTotalDataLength(UnsignedInt totalDataLength)
{
	m_totalDataLength = totalDataLength;
}

UnsignedInt NetWrapperCommandMsg::getChunkNumber()
{
	return m_chunkNumber;
}

void NetWrapperCommandMsg::setChunkNumber(UnsignedInt chunkNumber)
{
	m_chunkNumber = chunkNumber;
}

UnsignedInt NetWrapperCommandMsg::getNumChunks()
{
	return m_numChunks;
}

void NetWrapperCommandMsg::setNumChunks(UnsignedInt numChunks)
{
	m_numChunks = numChunks;
}

UnsignedShort NetWrapperCommandMsg::getWrappedCommandID()
{
	return m_wrappedCommandID;
}

void NetWrapperCommandMsg::setWrappedCommandID(UnsignedShort wrappedCommandID)
{
	m_wrappedCommandID = wrappedCommandID;
}

void NetFileCommandMsg::setFileData(UnsignedByte *data, UnsignedInt dataLength)
{
	m_dataLength = dataLength;
	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
}

UnsignedShort NetAckBothCommandMsg::getCommandID()
{
	return m_commandID;
}

UnsignedByte NetAckBothCommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

UnsignedShort NetAckStage1CommandMsg::getCommandID()
{
	return m_commandID;
}

UnsignedByte NetAckStage1CommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

Int NetAckStage1CommandMsg::getSortNumber()
{
	return m_commandID;
}

UnsignedShort NetAckStage2CommandMsg::getCommandID()
{
	return m_commandID;
}

UnsignedByte NetAckStage2CommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

UnsignedByte NetProgressCommandMsg::getPercentage()
{
	return m_percent;
}

void NetProgressCommandMsg::setPercentage(UnsignedByte percent)
{
	m_percent = percent;
}

// Seven disconnect-message accessors whose ledger rows claimed 5-byte
// incremental-link thunks. The definitions had been trimmed out of this file, so
// nothing emitted the symbols; these are the reference's bodies unchanged.

UnsignedByte NetDisconnectPlayerCommandMsg::getDisconnectSlot() {
	return m_disconnectSlot;
}

void NetDisconnectPlayerCommandMsg::setDisconnectSlot(UnsignedByte slot) {
	m_disconnectSlot = slot;
}

void NetDisconnectPlayerCommandMsg::setDisconnectFrame(UnsignedInt frame) {
	m_disconnectFrame = frame;
}

void NetDisconnectVoteCommandMsg::setSlot(UnsignedByte slot) {
	m_slot = slot;
}

void NetDisconnectVoteCommandMsg::setVoteFrame(UnsignedInt voteFrame) {
	m_voteFrame = voteFrame;
}

UnsignedInt NetDisconnectFrameCommandMsg::getDisconnectFrame() {
	return m_disconnectFrame;
}

UnsignedInt NetDisconnectScreenOffCommandMsg::getNewFrame() {
	return m_newFrame;
}
