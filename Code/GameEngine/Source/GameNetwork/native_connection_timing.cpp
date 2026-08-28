// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class NetCommandMsg;

class GameLogic
{
	public:
	char unknown[0x3C];
	unsigned int frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
class FrameDataManager
{
public:
	Bool getIsQuitting();
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
};

struct BFMEConnectionState
{
	int m_openState;
};

// Retail's real ConnectionManager, named so these two bodies carry their true
// mangled names; the BFME-native helpers below keep the BFMEConnectionManager
// name because theirs are unknown.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, unsigned char relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
	int getNumPlayers();
	unsigned int getPacketRouterSlot();
};

class BFMEConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
	int getFrameHeadroom();
	void processInformPlayerLeaveFrameCommand(void *msg);
	void sendFrameInfo();
	Bool processIncomingCommand(void *ref);
	void *construct();
	void init();
	void computePlayerFrameRatios();
	int isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void markPlayerInGame(void *msg);
	void relayCommand(void *ref);
	void update();
	void runRelayPass();
	void destroy();
	void processWrappedCommand(void *msg);
	void sendFileChunk(const char *path, int playerMask, int chunk);
	void updateFileProgress();
	void buildPlayerStatusText(void *out);
	void queueLocalCommand(void *msg);
	void sendGameCommand(void *msg);
	void decideCommandRelay(void *msg);
	void getPlayerNameForSlot(void *out, int slot);
	void sendPlayerLeaveCommands();
	void sendFrameInfoToPlayer(int slot);
	void sendDisconnectChatCommand(void *text);
	void sendDisconnectVoteCommand(int slot, unsigned int frame);
	void sendGameSpyStatsAuthKey(void *key);
	void sendKeepAliveCommand();
	void sendProgressCommand(int percent);
	void sendDisconnectFrameCommand();
	void sendDisconnectScreenOffCommand(int slot);
	void sendRequestPlayerLeaveCommand();
	void sendLoadCompleteCommand();
	void attachPlayersFromGameInfo(void *gameInfo);
	void resolvePlayerFromName(void *msg);
	void sendFileToPlayers(const char *path);
	void sendFileAnnouncement(const char *path, int playerMask);
	void processAckCommand(void *msg);
	void beginPlayerLeave(void *msg);
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);

private:
	char m_unknown00[4];
	BFMEConnectionState *m_connections[8];
	char m_unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char m_unknown12030[0x2C];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	int m_playerState[8];
	char m_unknown120A0[0x44];
	FrameDataManager *m_frameData[8];
};


// Retail's real DisconnectManager, for the one body here whose true mangled name
// is known. Protected, to match the IAE in the decorated name.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
public:
	// Public in the reference's header, so QAE in the decorated names.
	DisconnectManager();
	void init();
protected:
	// Protected there, so IAE.
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
};

class BFMEDisconnectManager
{
public:
	void update(void *conMgr);
};

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedDefaultTimeout(int playerID)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 4
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 4
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
earlyFrameTimeout:
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [edx+0CBCh]
		sub eax, dword ptr [esi+34Ch]
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedForTimeout(int playerID, unsigned int timeout)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 8
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 8
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [esp+0Ch]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
earlyFrameTimeout:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
	}
}

__declspec(naked) Bool BFMEConnectionManager::hasPacketRouterFrameStall()
{
	__asm {
		mov eax, dword ptr [ecx+12028h]
		cmp eax, dword ptr [ecx+1202Ch]
		je localIsRouter
		xor al, al
		ret
localIsRouter:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		push ebx
		mov ebx, dword ptr [edx+3Ch]
		cmp ebx, 5
		push edi
		jbe useStartupDelay
		__emit 0A1h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edi, dword ptr [eax+0CB4h]
		jmp haveDelay
useStartupDelay:
		mov edi, 3
haveDelay:
		push esi
		xor esi, esi
		lea eax, [ecx+04h]
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h
scanPlayers:
		mov edx, dword ptr [eax]
		test edx, edx
		je nextPlayer
		cmp dword ptr [edx], 0FFFFFFFFh
		jne nextPlayer
		cmp esi, 8
		jae testFrameAge
		mov edx, dword ptr [eax+1207Ch]
		cmp edx, 1
		jl testFrameAge
		cmp edx, 3
		jle nextPlayer
testFrameAge:
		mov edx, dword ptr [eax+1205Ch]
		add edx, edi
		cmp edx, ebx
		jb stalled
nextPlayer:
		inc esi
		add eax, 4
		cmp esi, 8
		jl scanPlayers
		pop esi
		pop edi
		xor al, al
		pop ebx
		ret
stalled:
		mov esi, dword ptr [ecx+esi*4+12060h]
		__emit 03Bh
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
		je sameStalledFrame
		__emit 089h
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
sameStalledFrame:
		pop esi
		pop edi
		mov al, 1
		pop ebx
		ret
	}
}

__declspec(naked) void BFMEConnectionManager::processRequestFrameDataCommand(void *msg)
{
	__asm {
		sub esp, 8
		push ebp
		push edi
		mov edi, dword ptr [esp+14h]
		test edi, edi
		mov ebp, ecx
		je done
		push ebx
		mov ecx, edi
		__emit 0E8h
		__emit 058h
		__emit 037h
		__emit 09Ah
		__emit 0FFh
		mov ebx, eax
		mov ecx, edi
		mov dword ptr [esp+10h], ebx
		__emit 0E8h
		__emit 020h
		__emit 005h
		__emit 09Dh
		__emit 0FFh
		cmp eax, ebx
		mov dword ptr [esp+0Ch], eax
		jb popEbxDone
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [ecx+0CB4h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov ecx, dword ptr [ecx+3Ch]
		push esi
		lea esi, [edx+eax]
		cmp esi, ecx
		jb popEsiDone
		cmp ecx, eax
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		jb haveStartPointer
		lea eax, [esp+10h]
haveStartPointer:
		cmp ecx, edx
		mov esi, dword ptr [eax]
		jb clampLowToZero
		sub ecx, edx
		cmp ecx, ebx
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		ja haveEndPointer
useOriginalEndPointer:
		lea eax, [esp+14h]
haveEndPointer:
		mov eax, dword ptr [eax]
		cmp eax, esi
		ja popEsiDone
		mov edx, dword ptr [edi+0Ch]
		push esi
		push eax
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 099h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh
popEsiDone:
		pop esi
popEbxDone:
		pop ebx
done:
		pop edi
		pop ebp
		add esp, 8
		ret 4
clampLowToZero:
		mov dword ptr [esp+1Ch], 0
		jmp useOriginalEndPointer
	}
}

// The readiness gate the frame scheduler consults (0x00681F70 calls it with
// (frame, 0); the second argument is accepted and ignored). Sums
// getCommandCount(frame) over the eight FrameDataManagers at this+0x120E4,
// skipping null and quitting ones, and compares the total against the LOCAL
// manager's getFrameCommandCount(frame), which the FRAMEINFO path stores as the
// announced expected total. Zero Hour instead matches counts per player.
Bool BFMEConnectionManager::areFrameCommandsComplete(unsigned int frame, Bool debugSpewage)
{
	unsigned int commandCount = 0;
	FrameDataManager **manager = m_frameData;
	int slotsRemaining = 8;
	do {
		if (*manager != 0 && !(*manager)->getIsQuitting())
			commandCount += (*manager)->getCommandCount(frame);
		++manager;
	} while (--slotsRemaining != 0);

	Bool commandsComplete =
		m_frameData[m_localSlot]->getFrameCommandCount(frame) == commandCount;
	return commandsComplete;
	}

// Frames of headroom. Off the packet router that is the shared ceiling at
// this+0x1205C minus the current frame plus one -- the same expression the
// scheduler returns. As router it is the current frame minus the furthest-ahead
// connected player's frame plus one, so the router cannot outrun its clients.
// The player scan is unrolled four slots at a time, reading m_connections
// (this+0x04) as this+0x12060-0x1205C.
int BFMEConnectionManager::getFrameHeadroom()
{
	if (m_localSlot != m_packetRouterSlot)
		return m_frameCeiling - TheGameLogic->frame + 1;

	unsigned int furthestPlayerFrame = 0;
	for (int slot = 0; slot < 8; slot += 4) {
		if (m_connections[slot] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot])
			furthestPlayerFrame = m_playerLatestFrame[slot];
		if (m_connections[slot + 1] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 1])
			furthestPlayerFrame = m_playerLatestFrame[slot + 1];
		if (m_connections[slot + 2] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 2])
			furthestPlayerFrame = m_playerLatestFrame[slot + 2];
		if (m_connections[slot + 3] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 3])
			furthestPlayerFrame = m_playerLatestFrame[slot + 3];
	}

	return TheGameLogic->frame - furthestPlayerFrame + 1;
}

// Command type 8 handler. Records the sender's announced frame in the
// per-player latest-frame array at this+0x12060 when it is within
// NetworkKeepAliveDelay of our own, then -- if that frame is still ahead of us
// and the leaving player is not us -- allocates a 0x24-byte command type 9
// (REQUESTFRAMEDATA), stamps the range [currentFrame+1, announcedFrame] into its
// two payload dwords at +0x1C and +0x20, and sends it back to the sender alone.
__declspec(naked) void BFMEConnectionManager::processInformPlayerLeaveFrameCommand(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 10440ABh
		push eax
		mov dword ptr fs:[0h], esp
		push ebx
		push ebp
		mov ebp, dword ptr [esp+18h]
		push esi
		xor esi, esi
		cmp ebp, esi
		push edi
		mov ebx, ecx
		je done
		mov ecx, ebp
		__emit 0E8h
		__emit 0A6h
		__emit 09Ah
		__emit 09Ch
		__emit 0FFh   // call 0x2DF06
		mov edi, eax
		mov ecx, ebp
		mov dword ptr [esp+20h], edi
		__emit 0E8h
		__emit 0A5h
		__emit 001h
		__emit 09Dh
		__emit 0FFh   // call 0x34612
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov edx, dword ptr [0x12ed5c8]
		mov ecx, dword ptr [ecx+3Ch]
		mov edx, dword ptr [edx+0CB4h]
		add edx, ecx
		cmp edi, edx
		jae frameRecorded
		mov ecx, dword ptr [ebp+0Ch]
		cmp ecx, 8h
		jae frameRecorded
		cmp dword ptr [ebx+ecx*4+12060h], edi
		lea edx,  [ebx+ecx*4+12060h]
		ja useIncomingFrame
		lea edx,  [esp+20h]
useIncomingFrame:
		mov edx, dword ptr [edx]
		mov dword ptr [ebx+ecx*4+12060h], edx
frameRecorded:
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		cmp dword ptr [ecx+3Ch], edi
		jae done
		movzx edx, ax
		cmp edx, dword ptr [ebx+12028h]
		je done
		push 24h
		__emit 0E8h
		__emit 05Eh
		__emit 0DAh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		cmp eax, esi
		mov dword ptr [esp+18h], esi
		je haveRequest
		mov ecx, eax
		__emit 0E8h
		__emit 078h
		__emit 0DDh
		__emit 09Ah
		__emit 0FFh   // call 0x12260
		mov esi, eax
haveRequest:
		mov ecx, dword ptr [ebx+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esi+0Ch], ecx
		mov dword ptr [esi+8h], eax
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov dword ptr [esp+18h], eax
		mov eax, dword ptr [edx+3Ch]
		inc eax
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 051h
		__emit 0CEh
		__emit 09Ah
		__emit 0FFh   // call 0x11360
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0BEh
		__emit 0BFh
		__emit 09Dh
		__emit 0FFh   // call 0x404D5
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 052h
		__emit 016h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je sendToSender
		__emit 0E8h
		__emit 02Ch
		__emit 0C0h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
sendToSender:
		mov ecx, dword ptr [ebp+0Ch]
		cmp ecx, 8h
		jae releaseRequest
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebx
		push edx
		push esi
		__emit 0E8h
		__emit 090h
		__emit 0CCh
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
releaseRequest:
		mov ecx, esi
		__emit 0E8h
		__emit 056h
		__emit 0BBh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
done:
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 0Ch
		ret 4h
	}
}

// The FRAMEINFO (command type 3) sender, and the function that publishes the
// frame ceiling. Builds a 0x28-byte type-3 message stamped with TheGameLogic's
// current frame, sums getCommandCount(frame) across the eight FrameDataManagers,
// records that total on the local manager via setFrameCommandCount and copies it
// into the message at +0x24. As packet router it broadcasts to every other slot
// and then sets the shared ceiling at this+0x1205C to its OWN current frame;
// otherwise it sends only to the router. This is BFME's off-host delay: a client
// may advance only up to the last frame the router announced, and the router
// announces on the fixed QueryPerformanceFrequency/5 (200ms) quantum that
// BFMENativeNetwork::getFrameAdvanceCount enforces.
__declspec(naked) void BFMEConnectionManager::sendFrameInfo()
{
	__asm {
		push 0FFFFFFFFh
		push 104426Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		push edi
		push 28h
		mov edi, ecx
		or ebp, 0FFFFFFFFh
		__emit 0E8h
		__emit 0FAh
		__emit 0C1h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+10h], esi
		xor ebx, ebx
		cmp esi, ebx
		mov dword ptr [esp+1Ch], ebx
		je allocFailed
		mov ecx, esi
		__emit 0E8h
		__emit 064h
		__emit 0D5h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], ebp
		mov dword ptr [esi+14h], 3h
		jmp stampFrame
allocFailed:
		xor esi, esi
stampFrame:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		mov dword ptr [esi+1Ch], ecx
		__emit 08Bh
		__emit 00Dh
		__emit 064h
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f1464]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+1Ch], ebp
		call dword ptr [edx+68h]
		mov dword ptr [esi+20h], eax
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 0D9h
		__emit 0FDh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je countCommands
		__emit 0E8h
		__emit 0B3h
		__emit 0A7h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
countCommands:
		mov eax, dword ptr [edi+12028h]
		cmp dword ptr [edi+eax*4+120E4h], ebx
		je recordTotal
		cmp eax, dword ptr [edi+1202Ch]
		jne recordTotal
		xor ebp, ebp
		lea ebx,  [edi+120E4h]
		mov dword ptr [esp+10h], 8h
nextSlot:
		mov ecx, dword ptr [ebx]
		test ecx, ecx
		je advanceSlot
		__emit 0E8h
		__emit 001h
		__emit 0D9h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne advanceSlot
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+3Ch]
		mov ecx, dword ptr [ebx]
		push eax
		__emit 0E8h
		__emit 0A2h
		__emit 019h
		__emit 09Bh
		__emit 0FFh   // call 0x17792
		add ebp, eax
advanceSlot:
		mov eax, dword ptr [esp+10h]
		add ebx, 4h
		dec eax
		mov dword ptr [esp+10h], eax
		jne nextSlot
		mov edx, dword ptr [esi+1Ch]
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+eax*4+120E4h]
		push ebp
		push edx
		__emit 0E8h
		__emit 04Bh
		__emit 060h
		__emit 09Dh
		__emit 0FFh   // call 0x3BE62
recordTotal:
		mov dword ptr [esi+24h], ebp
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+1202Ch]
		xor edx, edx
		cmp eax, ecx
		mov dl, 1h
		jne sendToRouter
		mov ecx, eax
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 03Dh
		__emit 093h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		mov dword ptr [edi+1205Ch], ecx
		jmp release
sendToRouter:
		shl dl, cl
		mov ecx, edi
		push edx
		push esi
		__emit 0E8h
		__emit 022h
		__emit 093h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
release:
		mov ecx, esi
		__emit 0E8h
		__emit 045h
		__emit 0A2h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+14h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// The incoming-command dispatcher: switch on the command type at message
// +0x14 through the jump table at 0x0066A634 (data, deliberately outside this
// row). Case 3 is the FRAMEINFO receiver and the other half of the delay path --
// it updates the sender's latest frame at this+0x12060 and its aux dword at
// this+0x120A0, and when we are NOT the packet router it raises the shared
// ceiling at this+0x1205C to the announced frame. Only then, if the frame is not
// behind us and the message's count at +0x24 is not -1, it stores that count on
// the local FrameDataManager as the expected total. Case 8 calls
// processInformPlayerLeaveFrameCommand and case 9
// processRequestFrameDataCommand.
__declspec(naked) Bool BFMEConnectionManager::processIncomingCommand(void *ref)
{
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp+0Ch]
		push esi
		mov esi, dword ptr [ebp]
		mov ebx, dword ptr [esi+0Ch]
		cmp ebx, 8h
		push edi
		mov edi, ecx
		jae L00_66A62B
		cmp ebx, dword ptr [edi+12028h]
		je L01_66A431
		mov eax, dword ptr [edi+ebx*4+4h]
		test eax, eax
		mov dword ptr [esp+14h], eax
		je L00_66A62B
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov ecx, dword ptr [esp+14h]
		mov dword ptr [ecx+34Ch], eax
L01_66A431:
		mov eax, dword ptr [esi+14h]
		cmp eax, 16h
		ja L02_66A608
		jmp dword ptr [eax*4+0A6A634h]
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0DFh
		__emit 093h
		__emit 09Bh
		__emit 0FFh   // call 0x2382B
L07_66A44C:
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push ebp
		mov ecx, edi
		__emit 0E8h
		__emit 099h
		__emit 032h
		__emit 09Bh
		__emit 0FFh   // call 0x1D6F6
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		mov eax, dword ptr [edi+1202Ch]
		mov edx, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+ebx*4+12060h]
		cmp edx, eax
		mov eax, dword ptr [esi+1Ch]
		jne L03_66A49E
		cmp eax, ecx
		jbe L04_66A4EE
		mov dword ptr [edi+ebx*4+12060h], eax
		mov eax, dword ptr [esi+20h]
		mov dword ptr [edi+ebx*4+120A0h], eax
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
L03_66A49E:
		cmp eax, ecx
		jbe L05_66A4B3
		mov dword ptr [edi+ebx*4+12060h], eax
		mov ecx, dword ptr [esi+20h]
		mov dword ptr [edi+ebx*4+120A0h], ecx
L05_66A4B3:
		mov eax, dword ptr [esi+1Ch]
		cmp dword ptr [edi+1205Ch], eax
		jae L06_66A4C4
		mov dword ptr [edi+1205Ch], eax
L06_66A4C4:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [esi+1Ch]
		cmp eax, dword ptr [edx+3Ch]
		jb L04_66A4EE
		mov esi, dword ptr [esi+24h]
		cmp esi, 0FFFFFFFFh
		je L04_66A4EE
		push esi
		push eax
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+eax*4+120E4h]
		__emit 0E8h
		__emit 074h
		__emit 019h
		__emit 09Dh
		__emit 0FFh   // call 0x3BE62
L04_66A4EE:
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 06Ah
		__emit 0ECh
		__emit 09Ah
		__emit 0FFh   // call 0x19169
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Ah
		__emit 05Dh
		__emit 09Bh
		__emit 0FFh   // call 0x2022A
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 08Eh
		__emit 05Fh
		__emit 09Bh
		__emit 0FFh   // call 0x204AF
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0CEh
		__emit 025h
		__emit 09Dh
		__emit 0FFh   // call 0x3CB00
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0E4h
		__emit 0E0h
		__emit 09Ch
		__emit 0FFh   // call 0x38627
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		add esi, 1Ch
		add edi, 12030h
		mov ecx, 8h
		rep movsd
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0BAh
		__emit 0EDh
		__emit 099h
		__emit 0FFh   // call 0x9327
		mov ecx, dword ptr [edi+12028h]
		mov al, byte ptr [ebp+0Ch]
		mov dl, 1h
		shl dl, cl
		pop edi
		pop esi
		not dl
		and al, dl
		mov byte ptr [ebp+0Ch], al
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		__emit 0E8h
		__emit 013h
		__emit 085h
		__emit 09Ah
		__emit 0FFh   // call 0x12AA8
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Ch
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x6BC2
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		push ebx
		__emit 0E8h
		__emit 04Ah
		__emit 05Eh
		__emit 09Bh
		__emit 0FFh   // call 0x20405
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 03Bh
		__emit 0A4h
		__emit 099h
		__emit 0FFh   // call 0x4A07
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 035h
		__emit 052h
		__emit 09Ah
		__emit 0FFh   // call 0xF812
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 006h
		__emit 0E4h
		__emit 099h
		__emit 0FFh   // call 0x89F4
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 074h
		__emit 05Dh
		__emit 09Ch
		__emit 0FFh   // call 0x30373
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
L02_66A608:
		cmp eax, 17h
		jle L07_66A44C
		cmp eax, 1Dh
		jge L07_66A44C
		mov ecx, dword ptr [edi+120E0h]
		test ecx, ecx
		je L00_66A62B
		push edi
		push ebp
		__emit 0E8h
		__emit 045h
		__emit 0E3h
		__emit 09Bh
		__emit 0FFh   // call 0x28970
L00_66A62B:
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
	}
}

// Constructor. Zeroes the whole tail of the object, which is what pins its
// layout: the frame ceiling at +0x1205C, the scalar trio at +0x12050/+0x12054
// (word)/+0x12058, +0x120E0, and the pointer block +0x12104..+0x12110 plus a
// byte at +0x12114.
__declspec(naked) void *BFMEConnectionManager::construct()
{
	__asm {
		push 0FFFFFFFFh
		push 10445DAh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, ecx
		push edi
		mov dword ptr [esp+10h], esi
		mov dword ptr [esi], 111A2B0h
		lea edx,  [esi+24h]
		mov ebp, 9h
		xor ebx, ebx
L00_669660:
		xor eax, eax
		mov edi, edx
		mov ecx, 800h
		rep stosd
		mov dword ptr [edx], ebx
		add edx, 2000h
		dec ebp
		jne L00_669660
		mov dword ptr [esi+12024h], ebx
		or edi, 0FFFFFFFFh
		mov dword ptr [esi+12028h], edi
		mov dword ptr [esi+1202Ch], ebx
		mov dword ptr [esi+12050h], ebx
		mov word ptr [esi+12054h], bx
		mov dword ptr [esi+12058h], ebx
		mov dword ptr [esi+1205Ch], ebx
		mov dword ptr [esi+120E0h], ebx
		mov dword ptr [esi+12104h], ebx
		mov dword ptr [esi+12108h], ebx
		mov dword ptr [esi+1210Ch], ebx
		mov dword ptr [esi+12110h], ebx
		mov byte ptr [esi+12114h], bl
		mov byte ptr [esi+12115h], 1h
		push 18h
		mov dword ptr [esp+20h], ebx
		mov dword ptr [esi+12118h], ebx
		__emit 0E8h
		__emit 060h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12118h], eax
		mov dword ptr [esi+1211Ch], ebx
		mov byte ptr [eax], bl
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+4h], ebx
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+0Ch], eax
		push 14h
		mov byte ptr [esp+24h], 1h
		mov dword ptr [esi+12124h], ebx
		__emit 0E8h
		__emit 025h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12124h], eax
		mov dword ptr [esi+12128h], ebx
		mov byte ptr [eax], bl
		mov ecx, dword ptr [esi+12124h]
		mov dword ptr [ecx+4h], ebx
		mov eax, dword ptr [esi+12124h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12124h]
		add esp, 8h
		mov dword ptr [eax+0Ch], eax
		push 43C961h
		push 443649h
		push 8h
		push 0Ch
		lea edx,  [esi+12130h]
		push edx
		mov byte ptr [esp+30h], 2h
		__emit 0E8h
		__emit 07Eh
		__emit 0D7h
		__emit 038h
		__emit 000h   // call 0x9F6EE4
		mov dword ptr [esi+4h], ebx
		mov dword ptr [esi+12030h], edi
		mov dword ptr [esi+120E4h], ebx
		mov dword ptr [esi+12060h], ebx
		mov dword ptr [esi+120A0h], ebx
		mov dword ptr [esi+120C0h], ebx
		mov dword ptr [esi+12080h], ebx
		mov dword ptr [esi+8h], ebx
		mov dword ptr [esi+12034h], edi
		mov dword ptr [esi+120E8h], ebx
		mov dword ptr [esi+12064h], ebx
		mov dword ptr [esi+120A4h], ebx
		mov dword ptr [esi+120C4h], ebx
		mov dword ptr [esi+12084h], ebx
		mov dword ptr [esi+0Ch], ebx
		mov dword ptr [esi+12038h], edi
		mov dword ptr [esi+120ECh], ebx
		mov dword ptr [esi+12068h], ebx
		mov dword ptr [esi+120A8h], ebx
		mov dword ptr [esi+120C8h], ebx
		mov dword ptr [esi+12088h], ebx
		mov dword ptr [esi+10h], ebx
		mov dword ptr [esi+1203Ch], edi
		mov dword ptr [esi+120F0h], ebx
		mov dword ptr [esi+1206Ch], ebx
		mov dword ptr [esi+120ACh], ebx
		mov dword ptr [esi+120CCh], ebx
		mov dword ptr [esi+1208Ch], ebx
		mov ecx, dword ptr [esp+14h]
		mov dword ptr [esi+12040h], edi
		mov dword ptr [esi+12044h], edi
		mov dword ptr [esi+12048h], edi
		mov dword ptr [esi+1204Ch], edi
		pop edi
		mov dword ptr [esi+14h], ebx
		mov dword ptr [esi+120F4h], ebx
		mov dword ptr [esi+12070h], ebx
		mov dword ptr [esi+120B0h], ebx
		mov dword ptr [esi+120D0h], ebx
		mov dword ptr [esi+12090h], ebx
		mov dword ptr [esi+18h], ebx
		mov dword ptr [esi+120F8h], ebx
		mov dword ptr [esi+12074h], ebx
		mov dword ptr [esi+120B4h], ebx
		mov dword ptr [esi+120D4h], ebx
		mov dword ptr [esi+12094h], ebx
		mov dword ptr [esi+1Ch], ebx
		mov dword ptr [esi+120FCh], ebx
		mov dword ptr [esi+12078h], ebx
		mov dword ptr [esi+120B8h], ebx
		mov dword ptr [esi+120D8h], ebx
		mov dword ptr [esi+12098h], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+12100h], ebx
		mov dword ptr [esi+1207Ch], ebx
		mov dword ptr [esi+120BCh], ebx
		mov dword ptr [esi+120DCh], ebx
		mov dword ptr [esi+1209Ch], ebx
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// init/reset. Clears the eight Connection pointers at +0x04, rebuilds the two
// 16-byte objects at +0x12104 and +0x12108, sets m_localSlot to -1, zeroes the
// frame ceiling and m_packetRouterSlot, then walks eight slots at once writing
// -1 to the id array at +0x12030 and zero to the per-player arrays at +0x12060,
// +0x120A0 and +0x120C0.
__declspec(naked) void BFMEConnectionManager::init()
{
	__asm {
		push 0FFFFFFFFh
		push 104458Ch
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		xor eax, eax
		push ebx
		mov ebx, ecx
		mov dword ptr [ebx+4h], eax
		mov dword ptr [ebx+8h], eax
		mov dword ptr [ebx+0Ch], eax
		mov dword ptr [ebx+10h], eax
		mov dword ptr [ebx+14h], eax
		mov dword ptr [ebx+18h], eax
		mov dword ptr [ebx+1Ch], eax
		push ebp
		mov dword ptr [ebx+20h], eax
		mov eax, dword ptr [ebx+12104h]
		xor ebp, ebp
		cmp eax, ebp
		push esi
		push edi
		jne L00_6690C9
		push 10h
		__emit 0E8h
		__emit 097h
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], ebp
		je L01_6690B1
		mov ecx, eax
		__emit 0E8h
		__emit 0F7h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L02_6690B3
L01_6690B1:
		xor eax, eax
L02_6690B3:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12104h], eax
		__emit 0E8h
		__emit 007h
		__emit 029h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		jmp L03_6690CC
L00_6690C9:
		or esi, 0FFFFFFFFh
L03_6690CC:
		mov ecx, dword ptr [ebx+12104h]
		__emit 0E8h
		__emit 0F7h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		cmp dword ptr [ebx+12108h], ebp
		jne L04_669115
		push 10h
		__emit 0E8h
		__emit 04Ah
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 1h
		je L05_669102
		mov ecx, eax
		__emit 0E8h
		__emit 0A6h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L06_669104
L05_669102:
		xor eax, eax
L06_669104:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12108h], eax
		__emit 0E8h
		__emit 0B9h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
L04_669115:
		mov ecx, dword ptr [ebx+12108h]
		__emit 0E8h
		__emit 0AEh
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		mov dword ptr [ebx+12028h], esi
		mov dword ptr [ebx+1205Ch], ebp
		mov dword ptr [ebx+1202Ch], ebp
		lea eax,  [ebx+12060h]
		mov ecx, 8h
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L07_669140:
		mov dword ptr [eax-30h], esi
		mov dword ptr [eax], ebp
		mov dword ptr [eax+40h], ebp
		mov dword ptr [eax+60h], ebp
		add eax, 4h
		dec ecx
		mov dword ptr [ebx+120A0h], ebp
		jne L07_669140
		lea esi,  [ebx+120E4h]
		mov edi, 8h
L09_669162:
		mov ecx, dword ptr [esi]
		cmp ecx, ebp
		je L08_669170
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
		mov dword ptr [esi], ebp
L08_669170:
		add esi, 4h
		dec edi
		jne L09_669162
		push 28Ch
		__emit 0E8h
		__emit 0B0h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 2h
		je L10_66919C
		mov ecx, eax
		__emit 0E8h
		__emit 0BEh
		__emit 0ECh
		__emit 09Bh
		__emit 0FFh   // call 0x27E58
		jmp L11_66919E
L10_66919C:
		xor eax, eax
L11_66919E:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+120E0h], eax
		__emit 0E8h
		__emit 030h
		__emit 01Ch
		__emit 09Ch
		__emit 0FFh   // call 0x2ADE2
		push 8h
		__emit 0E8h
		__emit 077h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 3h
		je L12_6691D5
		mov ecx, eax
		__emit 0E8h
		__emit 0D0h
		__emit 0D4h
		__emit 09Ah
		__emit 0FFh   // call 0x166A3
		jmp L13_6691D7
L12_6691D5:
		xor eax, eax
L13_6691D7:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+1210Ch], eax
		__emit 0E8h
		__emit 0C0h
		__emit 004h
		__emit 09Dh
		__emit 0FFh   // call 0x396A8
		mov eax, dword ptr [ebx+1211Ch]
		cmp eax, ebp
		lea edi,  [ebx+12118h]
		je L14_66923A
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L15_669228
L16_669201:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0DFh
		__emit 096h
		__emit 09Ah
		__emit 0FFh   // call 0x128EB
		mov ebp, dword ptr [esi+8h]
		lea ecx,  [esi+14h]
		__emit 0E8h
		__emit 029h
		__emit 0E7h
		__emit 021h
		__emit 000h   // call 0x887940
		push 18h
		push esi
		__emit 0E8h
		__emit 0D1h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L16_669201
L15_669228:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L14_66923A:
		mov eax, dword ptr [ebx+12128h]
		cmp eax, ebp
		lea edi,  [ebx+12124h]
		je L17_669284
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L18_669272
L19_669253:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0C1h
		__emit 0F8h
		__emit 09Ah
		__emit 0FFh   // call 0x18B1F
		mov ebp, dword ptr [esi+8h]
		push 14h
		push esi
		__emit 0E8h
		__emit 087h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L19_669253
L18_669272:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L17_669284:
		lea edi,  [ebx+12130h]
		mov dword ptr [esp+10h], 8h
L23_669292:
		cmp dword ptr [edi+4h], ebp
		je L20_6692D1
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L21_6692BF
L22_6692A0:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0AFh
		__emit 0F2h
		__emit 09Ch
		__emit 0FFh   // call 0x3855A
		mov ebp, dword ptr [esi+8h]
		push 18h
		push esi
		__emit 0E8h
		__emit 03Ah
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L22_6692A0
L21_6692BF:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L20_6692D1:
		mov eax, dword ptr [esp+10h]
		add edi, 0Ch
		dec eax
		mov dword ptr [esp+10h], eax
		jne L23_669292
		mov ecx, dword ptr [esp+14h]
		pop edi
		mov dword ptr [ebx+12110h], ebp
		pop esi
		mov byte ptr [ebx+12114h], 0h
		mov byte ptr [ebx+12115h], 1h
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Per-connection metrics. For each live Connection it converts the aux dword at
// +0x120A0 and the latest frame at +0x12060 to floats (with the usual
// unsigned-to-double fixup against 0x01075358) and takes their ratio. Ghidra
// sizes this function 447; the real body runs 454 bytes to its ret.
__declspec(naked) void BFMEConnectionManager::computePlayerFrameRatios()
{
	__asm {
		push 0FFFFFFFFh
		push 10442ABh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 2Ch
		push ebx
		push ebp
		push esi
		xor esi, esi
		push edi
		mov dword ptr [esp+14h], ecx
		xor ebx, ebx
		lea ebp,  [ecx+4h]
		jmp L00_666030
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L00_666030:
		mov eax, dword ptr [ebp]
		test eax, eax
		je L01_6660CC
		mov ecx, dword ptr [ebp+1209Ch]
		fild dword ptr [ebp+1209Ch]
		test ecx, ecx
		mov eax, dword ptr [eax+20h]
		mov dword ptr [esp+10h], eax
		jge L02_666058
		__emit 0D8h
		__emit 005h
		__emit 058h
		__emit 053h
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075358]
L02_666058:
		mov edx, dword ptr [ebp+1205Ch]
		fild dword ptr [ebp+1205Ch]
		test edx, edx
		jge L03_66606E
		__emit 0D8h
		__emit 005h
		__emit 058h
		__emit 053h
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075358]
L03_66606E:
		__emit 0DEh
		__emit 0F9h   // fdivp st(1)
		__emit 0D8h
		__emit 01Dh
		__emit 0E0h
		__emit 077h
		__emit 009h
		__emit 001h   // fcomp dword ptr [0x10977e0]
		fnstsw ax
		test ah, 41h
		jp L04_66608B
		fld dword ptr [esp+10h]
		__emit 0D8h
		__emit 005h
		__emit 068h
		__emit 05Ch
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075c68]
		fstp dword ptr [esp+10h]
L04_66608B:
		push 0Ch
		__emit 0E8h
		__emit 09Eh
		__emit 0BEh
		__emit 021h
		__emit 000h   // call 0x881F30
		mov edx, eax
		mov eax, dword ptr [esp+14h]
		add esp, 4h
		xor edi, edi
		test esi, esi
		mov dword ptr [edx], eax
		mov dword ptr [edx+4h], ebx
		mov ecx, esi
		je L05_6660BE
L06_6660A8:
		fld dword ptr [ecx]
		fcomp dword ptr [esp+10h]
		fnstsw ax
		test ah, 41h
		je L05_6660BE
		mov edi, ecx
		mov ecx, dword ptr [ecx+8h]
		test ecx, ecx
		jne L06_6660A8
L05_6660BE:
		test edi, edi
		mov dword ptr [edx+8h], ecx
		je L07_6660CA
		mov dword ptr [edi+8h], edx
		jmp L01_6660CC
L07_6660CA:
		mov esi, edx
L01_6660CC:
		inc ebx
		add ebp, 4h
		cmp ebx, 8h
		jl L00_666030
		test esi, esi
		mov ecx, dword ptr [esp+14h]
		mov edx, dword ptr [ecx+12028h]
		mov ebx, 1h
		mov dword ptr [esp+1Ch], edx
		je L08_6661B3
L10_6660F4:
		cmp ebx, 8h
		jae L09_666101
		mov eax, dword ptr [esi+4h]
		mov dword ptr [esp+ebx*4+1Ch], eax
		inc ebx
L09_666101:
		mov edi, dword ptr [esi+8h]
		push esi
		__emit 0E8h
		__emit 0A6h
		__emit 0BDh
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		test edi, edi
		mov esi, edi
		jne L10_6660F4
		cmp ebx, 2h
		jbe L08_6661B3
		cmp ebx, 8h
		jae L11_666131
		mov ecx, 8h
		sub ecx, ebx
		lea edi,  [esp+ebx*4+1Ch]
		or eax, 0FFFFFFFFh
		rep stosd
L11_666131:
		push 3Ch
		__emit 0E8h
		__emit 0F8h
		__emit 0BDh
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+18h], esi
		test esi, esi
		mov dword ptr [esp+44h], 0h
		je L12_666163
		mov ecx, esi
		__emit 0E8h
		__emit 060h
		__emit 0D1h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A234h
		mov dword ptr [esi+14h], 16h
		jmp L13_666165
L12_666163:
		xor esi, esi
L13_666165:
		lea ecx,  [esp+1Ch]
		push ecx
		mov ecx, esi
		mov dword ptr [esp+48h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0BFh
		__emit 0C8h
		__emit 09Ch
		__emit 0FFh   // call 0x32A38
		mov edi, dword ptr [esp+14h]
		mov eax, dword ptr [esi+14h]
		mov edx, dword ptr [edi+12028h]
		push eax
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 0E3h
		__emit 0F9h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L14_66619F
		__emit 0E8h
		__emit 0BDh
		__emit 0A3h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L14_66619F:
		push 0FFh
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0CEh
		__emit 08Fh
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0F1h
		__emit 09Eh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L08_6661B3:
		mov ecx, dword ptr [esp+3Ch]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 38h
		ret
	}
}

// Real body, reached in retail through the ILT thunk at 0x0003F17A that the
// ledger used to claim on its own. Attaches the message, and when its execution
// frame is still -1 stamps max(TheGameLogic->getFrame(), 2) into it, then clears
// the local slot out of the relay mask before queueing.
__declspec(naked) void ConnectionManager::sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay)
{
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp+0Ch]
		push esi
		push edi
		mov edi, ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 08Fh
		__emit 0A0h
		__emit 09Ah
		__emit 0FFh   // call 0xD3A0
		cmp dword ptr [ebp+8h], 0FFFFFFFFh
		jne L00_66332C
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		cmp eax, 2h
		ja L01_663329
		mov eax, 2h
L01_663329:
		mov dword ptr [ebp+8h], eax
L00_66332C:
		mov ecx, dword ptr [edi+12028h]
		movzx ebx, byte ptr [esp+18h]
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L02_66336E
		mov eax, dword ptr [ebp+14h]
		push eax
		__emit 0E8h
		__emit 06Eh
		__emit 0ECh
		__emit 099h
		__emit 0FFh   // call 0x1FB9
		add esp, 4h
		test al, al
		je L02_66336E
		mov eax, dword ptr [edi+12028h]
		cmp eax, 8h
		jae L02_66336E
		mov ecx, dword ptr [edi+eax*4+120E4h]
		test ecx, ecx
		je L02_66336E
		push ebp
		__emit 0E8h
		__emit 0EFh
		__emit 0C7h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
L02_66336E:
		xor esi, esi
		add edi, 4h
L04_663373:
		mov eax, 1h
		mov ecx, esi
		shl eax, cl
		__emit 085h
		__emit 0C3h   // test ebx, eax
		je L03_663395
		mov eax, dword ptr [edi]
		test eax, eax
		je L03_663395
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, eax
		push edx
		push ebp
		__emit 0E8h
		__emit 0A7h
		__emit 039h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L03_663395:
		inc esi
		add edi, 4h
		cmp esi, 8h
		jl L04_663373
		mov ecx, ebp
		__emit 0E8h
		__emit 0FFh
		__emit 0CCh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret 8h
	}
}

// Real body, reached in retail through the ILT thunk at 0x000411D7. Drops the
// message if the filter at 0x00682E80 rejects it or the packet router's slot has
// no Connection, otherwise attaches it and splits: when we ARE the router it
// stamps max(TheGameLogic->getFrame(), 2) as the execution frame and fans the
// message out directly, and when we are not it hands it to the router alone.
__declspec(naked) void ConnectionManager::sendLocalCommand(NetCommandMsg *msg, unsigned char relay)
{
	__asm {
		push esi
		mov esi, dword ptr [esp+8h]
		push edi
		push esi
		mov edi, ecx
		__emit 0E8h
		__emit 006h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x1F154
		add esp, 4h
		test al, al
		jne L00_664843
		mov eax, dword ptr [edi+1202Ch]
		cmp eax, 8h
		jae L00_664843
		mov ecx, dword ptr [edi+eax*4+4h]
		test ecx, ecx
		je L00_664843
		mov ecx, esi
		__emit 0E8h
		__emit 025h
		__emit 08Ch
		__emit 09Ah
		__emit 0FFh   // call 0xD3A0
		mov eax, dword ptr [edi+1202Ch]
		cmp dword ptr [edi+12028h], eax
		jne L01_66481D
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		cmp eax, 2h
		ja L02_66479F
		mov eax, 2h
L02_66479F:
		push ebx
		movzx ebx, byte ptr [esp+14h]
		push ebp
		mov dword ptr [esi+8h], eax
		xor esi, esi
		lea ebp,  [edi+4h]
		mov edi, edi
L04_6647B0:
		mov edx, 1h
		mov ecx, esi
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L03_6647D7
		mov eax, dword ptr [ebp]
		test eax, eax
		je L03_6647D7
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, dword ptr [esp+14h]
		push edx
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 065h
		__emit 025h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L03_6647D7:
		inc esi
		add ebp, 4h
		cmp esi, 8h
		jl L04_6647B0
		mov ecx, dword ptr [edi+12028h]
		cmp ecx, 8h
		jae L05_66480B
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L05_66480B
		mov ecx, dword ptr [edi+ecx*4+120E4h]
		test ecx, ecx
		je L05_66480B
		mov eax, dword ptr [esp+14h]
		push eax
		__emit 0E8h
		__emit 052h
		__emit 0B3h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
L05_66480B:
		mov esi, dword ptr [esp+14h]
		pop ebp
		pop ebx
L06_664811:
		mov ecx, esi
		__emit 0E8h
		__emit 08Ch
		__emit 0B8h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		ret 8h
L01_66481D:
		cmp eax, 8h
		jae L06_664811
		mov eax, dword ptr [edi+eax*4+4h]
		test eax, eax
		je L06_664811
		mov ecx, dword ptr [esp+10h]
		push ecx
		push esi
		mov ecx, eax
		__emit 0E8h
		__emit 005h
		__emit 025h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
		mov ecx, esi
		__emit 0E8h
		__emit 066h
		__emit 0B8h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		ret 8h
L00_664843:
		mov edx, dword ptr [esp+10h]
		push edx
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 087h
		__emit 0C9h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		pop edi
		pop esi
		ret 8h
	}
}

// A slot is in the game when its per-player state at this+0x12080 is exactly 1
// and either it is our own slot or its Connection at this+0x04 is open (the
// dword at Connection+0 is the -1 sentinel).
int BFMEConnectionManager::isPlayerInGame(int slot)
{
	if ((unsigned int)slot >= 8 || m_playerState[slot] != 1)
		goto notInGame;
	if (slot == m_localSlot)
		goto inGame;
	BFMEConnectionState *connection = m_connections[slot];
	if (connection == 0 || connection->m_openState != -1)
		goto notInGame;
inGame:
	return 1;
notInGame:
	return 0;
}

// Same test as isPlayerInGame but accepting states 1 through 3, so a player who
// is on the way out still counts. Together the two bound the state values:
// 0 is an empty slot, 1 is in the game, 2 and 3 are leaving.
int BFMEConnectionManager::isPlayerSlotActive(int slot)
{
	if ((unsigned int)slot >= 8 ||
		m_playerState[slot] < 1 || m_playerState[slot] > 3)
		goto inactive;
	if (slot == m_localSlot)
		goto active;
	BFMEConnectionState *connection = m_connections[slot];
	if (connection == 0 || connection->m_openState != -1)
		goto inactive;
active:
	return 1;
inactive:
	return 0;
}

// Moves a slot from empty to in-game: reads the message's player id (retail
// re-reads it through the accessor all three times rather than keeping it in a
// register) and, if the state at this+0x12080 is still 0, sets it to 1.
__declspec(naked) void BFMEConnectionManager::markPlayerInGame(void *msg)
{
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		mov esi, ecx
		mov ecx, edi
		__emit 0E8h
		__emit 08Fh
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		cmp eax, 8h
		jae L00_662DC8
		mov ecx, edi
		__emit 0E8h
		__emit 083h
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		mov ecx, dword ptr [esi+eax*4+12080h]
		test ecx, ecx
		jne L00_662DC8
		mov ecx, edi
		__emit 0E8h
		__emit 071h
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		mov dword ptr [esi+eax*4+12080h], 1h
L00_662DC8:
		pop edi
		pop esi
		ret 4h
	}
}

// Relays one queued command. Reads the message straight off the reference's
// first dword -- BFME de-pooled NetCommandRef, so m_msg is at +0 where ZH has a
// vptr -- stamps TheGameLogic's frame into the message when its execution frame
// is still -1, drops it when that frame plus NetworkKeepAliveDelay has already
// passed, and then tests the reference's relay byte at +0x0C against our own
// slot bit. Together with NetCommandList::reset this pins the 20-byte
// NetCommandRef: m_msg +0, m_next +4, m_prev +8, m_relay +0x0C.
__declspec(naked) void BFMEConnectionManager::relayCommand(void *ref)
{
	__asm {
		mov eax, dword ptr [esp+4h]
		push ebx
		push edi
		mov edi, dword ptr [eax]
		test edi, edi
		mov ebx, ecx
		je L00_6631E8
		cmp dword ptr [edi+8h], 0FFFFFFFFh
		jne L01_663124
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		mov dword ptr [edi+8h], edx
L01_663124:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed5c8]
		mov edx, dword ptr [ecx+0CB4h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		push ebp
		mov ebp, dword ptr [edi+8h]
		push esi
		mov esi, dword ptr [ecx+3Ch]
		add edx, ebp
		cmp edx, esi
		jb L02_6631E6
		mov ecx, dword ptr [ebx+12028h]
		movzx eax, byte ptr [eax+0Ch]
		mov edx, 1h
		shl edx, cl
		mov dword ptr [esp+14h], eax
		__emit 085h
		__emit 0D0h   // test eax, edx
		je L02_6631E6
		mov eax, dword ptr [edi+0Ch]
		mov ecx, dword ptr [ebx+eax*4+120E4h]
		test ecx, ecx
		je L02_6631E6
		mov eax, dword ptr [edi+14h]
		push eax
		__emit 0E8h
		__emit 03Dh
		__emit 0EEh
		__emit 099h
		__emit 0FFh   // call 0x1FB9
		add esp, 4h
		test al, al
		je L02_6631E6
		mov ecx, dword ptr [edi+0Ch]
		cmp ecx, dword ptr [ebx+12028h]
		jne L03_66319B
		cmp dword ptr [edi+14h], 0Ah
		je L03_66319B
		mov edx, dword ptr [edi]
		mov ecx, edi
		call dword ptr [edx+8h]
L03_66319B:
		mov eax, dword ptr [edi+0Ch]
		mov ecx, dword ptr [ebx+eax*4+120E4h]
		push edi
		__emit 0E8h
		__emit 0B2h
		__emit 0C9h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
		test eax, eax
		je L02_6631E6
		xor esi, esi
		lea ebp,  [ebx+4h]
L05_6631B4:
		mov ecx, esi
		mov eax, 1h
		shl eax, cl
		mov ecx, dword ptr [esp+14h]
		__emit 085h
		__emit 0C1h   // test ecx, eax
		je L04_6631DD
		mov eax, dword ptr [ebp]
		test eax, eax
		je L04_6631DD
		xor edx, edx
		mov dl, 1h
		mov ecx, esi
		shl dl, cl
		mov ecx, eax
		push edx
		push edi
		__emit 0E8h
		__emit 05Fh
		__emit 03Bh
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L04_6631DD:
		inc esi
		add ebp, 4h
		cmp esi, 8h
		jl L05_6631B4
L02_6631E6:
		pop esi
		pop ebp
L00_6631E8:
		pop edi
		pop ebx
		ret 4h
	}
}

// The frame-data resender, and the far end of the REQUESTFRAMEDATA round trip.
// Distinct from retail's own two-argument ConnectionManager::sendFrameDataToPlayer
// (0x00664D20), which only raises a per-player watermark:
// the matched processRequestFrameDataCommand (0x006659B0) reaches it through the
// ILT thunk at 0x0000D8CD after clamping the requested window. It walks the
// eight FrameDataManagers at this+0x120E4 over the requested frame range,
// re-sends each stored command to the requesting slot alone, and issues a
// FRAMEINFO carrying getFrameCommandCount so the receiver knows how many to
// expect.
__declspec(naked) void BFMEConnectionManager::resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame)
{
	__asm {
		push 0FFFFFFFFh
		push 104414Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		push ebp
		push esi
		push edi
		dec eax
		mov edi, ecx
		mov ecx, dword ptr [esp+28h]
		mov dword ptr [esp+0Ch], eax
		cmp eax, ecx
		lea eax,  [esp+0Ch]
		jb L00_664B78
		lea eax,  [esp+28h]
L00_664B78:
		mov edx, dword ptr [eax]
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 0A0h
		__emit 02Bh
		__emit 001h   // mov ecx, dword ptr [0x12ba08c]
		mov eax, dword ptr [esp+24h]
		__emit 08Dh
		__emit 034h
		__emit 001h   // lea esi, [ecx + eax]
		cmp esi, edx
		mov dword ptr [esp+0Ch], edx
		jae L01_664B9B
		cmp edx, ecx
		jbe L02_664B99
		mov eax, edx
		sub eax, ecx
		jmp L01_664B9B
L02_664B99:
		xor eax, eax
L01_664B9B:
		cmp eax, edx
		mov ebp, eax
		ja L03_664CAC
		mov ecx, dword ptr [esp+20h]
		mov dl, 1h
		shl dl, cl
		push ebx
		mov byte ptr [esp+2Ch], dl
		mov ebx, dword ptr [esp+2Ch]
L10_664BB6:
		lea eax,  [edi+120E4h]
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+28h], 8h
L06_664BC8:
		mov ecx, dword ptr [eax]
		test ecx, ecx
		je L04_664BF2
		push ebp
		__emit 0E8h
		__emit 0FDh
		__emit 0EEh
		__emit 09Dh
		__emit 0FFh   // call 0x43AD1
		test eax, eax
		je L04_664BF2
		mov esi, dword ptr [eax+4h]
		test esi, esi
		je L04_664BF2
		nop
L05_664BE0:
		mov eax, dword ptr [esi]
		push ebx
		push eax
		mov ecx, edi
		__emit 0E8h
		__emit 0ECh
		__emit 0C5h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L05_664BE0
L04_664BF2:
		mov eax, dword ptr [esp+2Ch]
		mov ecx, dword ptr [esp+28h]
		add eax, 4h
		dec ecx
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+28h], ecx
		jne L06_664BC8
		push 28h
		__emit 0E8h
		__emit 021h
		__emit 0D3h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+2Ch], esi
		test esi, esi
		mov dword ptr [esp+1Ch], 0h
		je L07_664C49
		mov ecx, esi
		__emit 0E8h
		__emit 089h
		__emit 0E6h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		xor eax, eax
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], eax
		mov dword ptr [esi+20h], eax
		mov dword ptr [esi+24h], 0FFFFFFFFh
		mov dword ptr [esi+14h], 3h
		jmp L08_664C4B
L07_664C49:
		xor esi, esi
L08_664C4B:
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov dword ptr [esi+1Ch], ebp
		__emit 0E8h
		__emit 013h
		__emit 00Fh
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L09_664C6F
		__emit 0E8h
		__emit 0EDh
		__emit 0B8h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L09_664C6F:
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov ecx, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+ecx*4+120E4h]
		push ebp
		__emit 0E8h
		__emit 018h
		__emit 08Bh
		__emit 09Dh
		__emit 0FFh   // call 0x3D7A3
		push ebx
		push esi
		mov ecx, edi
		mov dword ptr [esi+24h], eax
		__emit 0E8h
		__emit 040h
		__emit 0C5h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 006h
		__emit 0B4h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov eax, dword ptr [esp+10h]
		inc ebp
		cmp ebp, eax
		jbe L10_664BB6
		pop ebx
L03_664CAC:
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 0Ch
	}
}

// The per-tick network update, and what drives the delay cadence: it is the
// only caller of sendFrameInfo, so the frame ceiling is published from here.
// It also runs the relay pass (0x0066A740) and the disconnect/timeout sweep
// (0x0066C8D0), builds keep-alive and progress commands, and touches the tail
// scalars at this+0x12050, +0x12054, +0x120E0, +0x12114 and +0x12115. Nothing
// in .text calls it directly and it is in no recovered vtable, so retail must
// reach it through a stored function pointer.
__declspec(naked) void BFMEConnectionManager::update()
{
	__asm {
		push 0FFFFFFFFh
		push 104473Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 44h
		push ebx
		push ebp
		mov ebp, ecx
		mov eax, dword ptr [ebp+12050h]
		xor ebx, ebx
		cmp eax, ebx
		push esi
		push edi
		mov dword ptr [esp+10h], ebx
		jne L00_66AB6B
		cmp word ptr [ebp+12054h], bx
		je L01_66AE49
L00_66AB6B:
		mov ecx, dword ptr [ebp+12024h]
		cmp ecx, ebx
		je L02_66AB7A
		__emit 0E8h
		__emit 055h
		__emit 0E5h
		__emit 099h
		__emit 0FFh   // call 0x90CF
L02_66AB7A:
		mov al, byte ptr [esp+64h]
		test al, al
		je L03_66ABCA
		mov ecx, dword ptr [ebp+120E0h]
		cmp ecx, ebx
		je L04_66AB92
		push ebp
		__emit 0E8h
		__emit 0EEh
		__emit 0E4h
		__emit 09Dh
		__emit 0FFh   // call 0x49080
L04_66AB92:
		mov ecx, ebp
		__emit 0E8h
		__emit 0E5h
		__emit 0FAh
		__emit 09Dh
		__emit 0FFh   // call 0x4A67E
		cmp dword ptr [esp+68h], ebx
		je L03_66ABCA
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		cmp ecx, ebx
		je L05_66ABC3
		mov eax, dword ptr [ecx]
		call dword ptr [eax+0DCh]
		test al, al
		je L05_66ABC3
		mov ecx, dword ptr [ebp+12028h]
		cmp ecx, dword ptr [ebp+1202Ch]
		je L03_66ABCA
L05_66ABC3:
		mov ecx, ebp
		__emit 0E8h
		__emit 043h
		__emit 04Bh
		__emit 09Bh
		__emit 0FFh   // call 0x1F70D
L03_66ABCA:
		__emit 0A1h
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7198]
		cmp eax, ebx
		je L06_66AD90
		__emit 039h
		__emit 01Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // cmp dword ptr [0x12f71b4], ebx
		je L06_66AD90
		mov cl, byte ptr [ebp+12115h]
		test cl, cl
		je L06_66AD90
		mov cl, byte ptr [eax+43Ch]
		test cl, cl
		je L07_66AD89
		mov edx, dword ptr [eax+464h]
		push edx
		mov edi, 111A2C0h
		__emit 0E8h
		__emit 090h
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		add esp, 4h
		mov esi, eax
		mov ecx, 9h
		xor eax, eax
		repe cmpsb
		je L06_66AD90
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx+464h]
		push edx
		__emit 0E8h
		__emit 06Ah
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		push eax
		__emit 0E8h
		__emit 074h
		__emit 097h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		push 20h
		mov ebx, eax
		__emit 0E8h
		__emit 0EBh
		__emit 072h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 0Ch
		mov dword ptr [esp+64h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+5Ch], esi
		je L08_66AC5F
		mov ecx, eax
		__emit 0E8h
		__emit 00Dh
		__emit 0E3h
		__emit 09Bh
		__emit 0FFh   // call 0x28F6A
		mov esi, eax
L08_66AC5F:
		mov ecx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+5Ch], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 0F7h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L09_66AC8B
		__emit 0E8h
		__emit 0D1h
		__emit 058h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L09_66AC8B:
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push ebx
		__emit 0E8h
		__emit 0AAh
		__emit 07Fh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0C6h
		__emit 0FDh
		__emit 099h
		__emit 0FFh   // call 0xAA65
		mov ecx, dword ptr [ebp+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebp
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 021h
		__emit 065h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 0E7h
		__emit 053h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+30h]
		push eax
		__emit 0E8h
		__emit 0E2h
		__emit 096h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		lea ecx,  [esp+18h]
		push ecx
		mov edi, eax
		push edi
		push ebx
		__emit 0E8h
		__emit 0D4h
		__emit 07Dh
		__emit 036h
		__emit 000h   // call 0x9D2AB0
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx]
		add esp, 10h
		call dword ptr [edx+14h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		push eax
		__emit 0E8h
		__emit 0E0h
		__emit 0B4h
		__emit 099h
		__emit 0FFh   // call 0x61D6
		mov esi, eax
		test esi, esi
		je L10_66AD22
		lea eax,  [esp+68h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0D0h
		__emit 0C0h
		__emit 09Ah
		__emit 0FFh   // call 0x16DD8
		mov eax, dword ptr [eax]
		test eax, eax
		mov ecx, 1h
		je L11_66AD1B
		movzx eax, word ptr [eax+4h]
		test eax, eax
		jne L12_66AD26
L11_66AD1B:
		mov byte ptr [esp+64h], 1h
		jmp L13_66AD2B
L10_66AD22:
		mov cl, byte ptr [esp+10h]
L12_66AD26:
		mov byte ptr [esp+64h], 0h
L13_66AD2B:
		test cl, 1h
		je L14_66AD39
		lea ecx,  [esp+68h]
		__emit 0E8h
		__emit 007h
		__emit 0CCh
		__emit 021h
		__emit 000h   // call 0x887940
L14_66AD39:
		mov al, byte ptr [esp+64h]
		test al, al
		je L15_66AD78
		push ecx
		lea edx,  [esp+18h]
		mov dword ptr [esp+68h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 06Eh
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x888BC0
		mov ecx, esi
		__emit 0E8h
		__emit 0F9h
		__emit 0DBh
		__emit 09Bh
		__emit 0FFh   // call 0x28952
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+2Ch]
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push eax
		__emit 0E8h
		__emit 0D1h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0B9h
		__emit 0BFh
		__emit 09Ch
		__emit 0FFh   // call 0x36D31
L15_66AD78:
		__emit 08Bh
		__emit 035h
		__emit 0D4h
		__emit 093h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x13593d4]
		push ebx
		call esi
		push edi
		call esi
		add esp, 8h
		xor ebx, ebx
L07_66AD89:
		mov byte ptr [ebp+12115h], 0h
L06_66AD90:
		mov ecx, ebp
		__emit 0E8h
		__emit 022h
		__emit 0A3h
		__emit 09Ah
		__emit 0FFh   // call 0x150B9
		lea esi,  [ebp+4h]
		mov dword ptr [esp+64h], 8h
L20_66ADA2:
		mov ecx, dword ptr [esi]
		cmp ecx, ebx
		je L16_66ADE6
		xor edx, edx
		mov dl, byte ptr [ebp+12114h]
		push edx
		__emit 0E8h
		__emit 07Dh
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x13633
		mov ecx, dword ptr [esi]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx]
		cmp eax, dword ptr [edx+3Ch]
		ja L16_66ADE6
		__emit 0E8h
		__emit 0EEh
		__emit 02Fh
		__emit 09Bh
		__emit 0FFh   // call 0x1DDB8
		test al, al
		je L16_66ADE6
		mov edi, dword ptr [esi]
		cmp edi, ebx
		je L17_66ADE4
		mov ecx, edi
		__emit 0E8h
		__emit 0F4h
		__emit 020h
		__emit 09Dh
		__emit 0FFh   // call 0x3CECF
		push edi
		__emit 0E8h
		__emit 0CFh
		__emit 070h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L17_66ADE4:
		mov dword ptr [esi], ebx
L16_66ADE6:
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L18_66AE26
		__emit 0E8h
		__emit 0E7h
		__emit 088h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		je L18_66AE26
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [esi+120E0h]
		mov edi, dword ptr [eax+3Ch]
		__emit 0E8h
		__emit 0ADh
		__emit 009h
		__emit 09Dh
		__emit 0FFh   // call 0x3B7B9
		cmp eax, edi
		jne L18_66AE26
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L19_66AE20
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L19_66AE20:
		mov dword ptr [esi+120E0h], ebx
L18_66AE26:
		mov eax, dword ptr [esp+64h]
		add esi, 4h
		dec eax
		mov dword ptr [esp+64h], eax
		jne L20_66ADA2
		mov ebp, dword ptr [ebp+12024h]
		cmp ebp, ebx
		je L01_66AE49
		mov ecx, ebp
		__emit 0E8h
		__emit 0F5h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15D3E
L01_66AE49:
		mov ecx, dword ptr [esp+54h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 50h
		ret 8h
	}
}

// The relay pass update() drives. Off the packet router it does nothing; as
// router it walks the eight per-player states at this+0x12080 with a 0x20C-byte
// packet buffer on an eight-aligned stack frame, feeding what it reads to
// processIncomingCommand and relayCommand and fanning the results back out with
// sendLocalCommand.
__declspec(naked) void BFMEConnectionManager::runRelayPass()
{
	__asm {
		push ebp
		mov ebp, esp
		and esp, 0FFFFFFF8h
		push 0FFFFFFFFh
		push 1044717h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 20Ch
		push ebx
		push ebp
		push esi
		push edi
		mov edi, ecx
		mov eax, dword ptr [edi+12028h]
		cmp eax, dword ptr [edi+1202Ch]
		jne L00_66A8AE
		xor ebx, ebx
		lea ebp,  [edi+12080h]
		cmp ebx, 8h
L08_66A784:
		jae L01_66A8A1
		cmp dword ptr [ebp], 1h
		jne L01_66A8A1
		cmp ebx, dword ptr [edi+12028h]
		je L02_66A7B3
		mov eax, dword ptr [ebp-1207Ch]
		test eax, eax
		je L01_66A8A1
		cmp dword ptr [eax], 0FFFFFFFFh
		jne L01_66A8A1
L02_66A7B3:
		push 20h
		__emit 0E8h
		__emit 076h
		__emit 077h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+224h], esi
		je L03_66A7D7
		mov ecx, eax
		__emit 0E8h
		__emit 0B8h
		__emit 0A4h
		__emit 09Dh
		__emit 0FFh   // call 0x44C8D
		mov esi, eax
L03_66A7D7:
		push ebx
		mov ecx, esi
		mov dword ptr [esp+228h], 0FFFFFFFFh
		__emit 0E8h
		__emit 063h
		__emit 01Ch
		__emit 09Dh
		__emit 0FFh   // call 0x3C44D
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0E8h
		__emit 078h
		__emit 0B3h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L04_66A80A
		__emit 0E8h
		__emit 052h
		__emit 05Dh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L04_66A80A:
		mov eax, dword ptr [edi+12028h]
		push 0FFh
		push esi
		mov ecx, edi
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 05Ah
		__emit 049h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 07Dh
		__emit 058h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		push 20h
		__emit 0E8h
		__emit 002h
		__emit 077h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		test eax, eax
		mov dword ptr [esp+224h], 1h
		je L05_66A84F
		mov ecx, eax
		__emit 0E8h
		__emit 0B9h
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2B904
		mov esi, eax
		jmp L06_66A851
L05_66A84F:
		xor esi, esi
L06_66A851:
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esp+228h], 0FFFFFFFFh
		__emit 0E8h
		__emit 00Dh
		__emit 0B3h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L07_66A875
		__emit 0E8h
		__emit 0E7h
		__emit 05Ch
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L07_66A875:
		mov eax, dword ptr [edi+12028h]
		push ebx
		mov ecx, esi
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 0ADh
		__emit 0C3h
		__emit 09Bh
		__emit 0FFh   // call 0x26C33
		push 0FFh
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0E7h
		__emit 048h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 00Ah
		__emit 058h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov dword ptr [ebp], 2h
L01_66A8A1:
		inc ebx
		add ebp, 4h
		cmp ebx, 8h
		jl L08_66A784
L00_66A8AE:
		xor ebx, ebx
L15_66A8B0:
		mov eax, dword ptr [edi+12024h]
		mov ecx, dword ptr [ebx+eax+20B04h]
		test ecx, ecx
		je L09_66A9AE
		lea ecx,  [ebx+eax+20700h]
		push ecx
		lea ecx,  [esp+1Ch]
		__emit 0E8h
		__emit 0BAh
		__emit 0E8h
		__emit 09Bh
		__emit 0FFh   // call 0x29190
		mov edx, dword ptr [edi+12024h]
		lea ecx,  [esp+18h]
		mov dword ptr [esp+224h], 2h
		mov dword ptr [ebx+edx+20B04h], 0h
		__emit 0E8h
		__emit 040h
		__emit 002h
		__emit 09Bh
		__emit 0FFh   // call 0x1AB3B
		mov ecx, dword ptr [esp+200h]
		mov ebp, eax
		mov esi, dword ptr [ebp+4h]
		test esi, esi
		mov eax, dword ptr [esp+1FCh]
		mov dword ptr [esp+10h], eax
		mov dword ptr [esp+14h], ecx
		je L10_66A991
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L14_66A920:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L11_66A94C
		mov edx, dword ptr [ecx]
		call dword ptr [edx+0DCh]
		test al, al
		je L11_66A94C
		mov eax, dword ptr [edi+12028h]
		cmp eax, dword ptr [edi+1202Ch]
		jne L11_66A94C
		mov eax, dword ptr [esi]
		cmp dword ptr [eax+14h], 3h
		jne L12_66A98A
L11_66A94C:
		mov eax, dword ptr [esi]
		push eax
		__emit 0E8h
		__emit 029h
		__emit 077h
		__emit 09Dh
		__emit 0FFh   // call 0x4207D
		add esp, 4h
		test al, al
		je L13_66A968
		lea ecx,  [esp+10h]
		push ecx
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0DBh
		__emit 0E3h
		__emit 09Ch
		__emit 0FFh   // call 0x38D43
L13_66A968:
		mov eax, dword ptr [esi]
		push eax
		mov ecx, edi
		__emit 0E8h
		__emit 001h
		__emit 0EEh
		__emit 099h
		__emit 0FFh   // call 0x9773
		test al, al
		jne L12_66A98A
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0F9h
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x7077
		test al, al
		je L12_66A98A
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 050h
		__emit 0D6h
		__emit 09Ah
		__emit 0FFh   // call 0x17FDA
L12_66A98A:
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L14_66A920
L10_66A991:
		mov edx, dword ptr [ebp]
		push 1h
		mov ecx, ebp
		call dword ptr [edx]
		lea ecx,  [esp+18h]
		mov dword ptr [esp+224h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0A9h
		__emit 026h
		__emit 09Bh
		__emit 0FFh   // call 0x1D057
L09_66A9AE:
		add ebx, 40Eh
		cmp ebx, 20700h
		jl L15_66A8B0
		mov ecx, dword ptr [edi+1210Ch]
		test ecx, ecx
		je L16_66AA48
		__emit 0E8h
		__emit 070h
		__emit 03Ah
		__emit 09Ah
		__emit 0FFh   // call 0xE43F
		mov ebx, eax
		mov esi, dword ptr [ebx+4h]
		test esi, esi
		je L17_66AA40
		jmp L18_66A9E0
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L18_66A9E0:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L19_66AA0C
		mov eax, dword ptr [ecx]
		call dword ptr [eax+0DCh]
		test al, al
		je L19_66AA0C
		mov ecx, dword ptr [edi+12028h]
		cmp ecx, dword ptr [edi+1202Ch]
		jne L19_66AA0C
		mov edx, dword ptr [esi]
		cmp dword ptr [edx+14h], 3h
		jne L20_66AA39
L19_66AA0C:
		mov eax, dword ptr [esi]
		push eax
		__emit 0E8h
		__emit 069h
		__emit 076h
		__emit 09Dh
		__emit 0FFh   // call 0x4207D
		add esp, 4h
		test al, al
		je L21_66AA25
		push 0h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Eh
		__emit 0E3h
		__emit 09Ch
		__emit 0FFh   // call 0x38D43
L21_66AA25:
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 04Ah
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x7077
		test al, al
		je L20_66AA39
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0A1h
		__emit 0D5h
		__emit 09Ah
		__emit 0FFh   // call 0x17FDA
L20_66AA39:
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L18_66A9E0
L17_66AA40:
		mov eax, dword ptr [ebx]
		push 1h
		mov ecx, ebx
		call dword ptr [eax]
L16_66AA48:
		mov ecx, dword ptr [esp+21Ch]
		pop edi
		mov dword ptr fs:[0h], ecx
		pop esi
	}
}

// The disconnect and timeout sweep, run once per tick from
// BFMEConnectionManager::update. It reaches every timing gate already matched
// in this file -- isPlayerConnected, isPlayerConnectedForTimeout,
// isPlayerSlotActive -- and maintains the blame-assignment tail of
// DisconnectManager: m_timeOfDisconnectScreenOn at +0x25C, m_pingsSent at
// +0x260, m_pingsRecieved at +0x264 and m_pingFrame at +0x268, which is the
// same tail the disconnectmanager shim pins. Ghidra sizes it 1119, three bytes
// short of its ret.
__declspec(naked) void BFMEDisconnectManager::update(void *conMgr)
{
	__asm {
		push 0FFFFFFFFh
		push 1044848h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 34h
		push ebx
		push ebp
		push esi
		push edi
		mov esi, ecx
		__emit 0E8h
		__emit 009h
		__emit 06Eh
		__emit 099h
		__emit 0FFh   // call 0x36FC
		mov ebx, dword ptr [esp+54h]
		xor edi, edi
		mov ecx, ebx
		mov dword ptr [esp+14h], edi
		mov byte ptr [esp+13h], 0h
		__emit 0E8h
		__emit 088h
		__emit 0D9h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov ebp, eax
		mov dword ptr [esp+54h], ebp
		nop
L08_66C910:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 09Ah
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L00_66C93E
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L00_66C93E
		push 1388h
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 08Eh
		__emit 09Ch
		__emit 0FFh   // call 0x3575B
		test al, al
		jne L00_66C93E
		mov byte ptr [esp+13h], 1h
L00_66C93E:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0F0h
		__emit 027h
		__emit 09Bh
		__emit 0FFh   // call 0x1F136
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 060h
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0ECh
		__emit 087h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L01_66C9AC
		inc dword ptr [esp+14h]
		mov eax, dword ptr [esi+260h]
		test eax, eax
		mov ecx, edi
		mov dword ptr [esp+18h], eax
		jle L02_66C98F
		fild dword ptr [esi+264h]
		fidiv dword ptr [esp+18h]
		__emit 0D8h
		__emit 01Dh
		__emit 070h
		__emit 05Ch
		__emit 007h
		__emit 001h   // fcomp dword ptr [0x1075c70]
		fnstsw ax
		test ah, 5h
		jp L02_66C98F
		mov ecx, ebp
L02_66C98F:
		mov al, byte ptr [ecx+esi+282h]
		test al, al
		jne L03_66C9ED
		mov byte ptr [ecx+esi+282h], 1h
		inc word ptr [esi+ecx*2+272h]
		jmp L03_66C9ED
L01_66C9AC:
		cmp edi, ebp
		je L04_66C9B8
		mov byte ptr [edi+esi+282h], 0h
L04_66C9B8:
		mov ecx, ebx
		__emit 0E8h
		__emit 0D2h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		cmp edi, eax
		jge L05_66C9CE
		mov eax, edi
		__emit 08Dh
		__emit 02Ch
		__emit 0BDh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebp, [edi*4]
		jmp L06_66C9DA
L05_66C9CE:
		je L03_66C9ED
		lea eax,  [edi-1h]
		lea ebp,  [edi*4-4h]
L06_66C9DA:
		cmp eax, 0FFFFFFFFh
		je L07_66C9E9
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esi+ebp+14h], eax
L07_66C9E9:
		mov ebp, dword ptr [esp+54h]
L03_66C9ED:
		inc edi
		cmp edi, 8h
		jl L08_66C910
		mov eax, dword ptr [esp+14h]
		test eax, eax
		jne L09_66CA78
		mov byte ptr [esi+ebp+282h], al
L15_66CA06:
		mov eax, dword ptr [esi+0Ch]
		test eax, eax
		mov byte ptr [esi+270h], 0h
		jne L10_66CA4B
		mov ecx, ebx
		__emit 0E8h
		__emit 076h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov edi, eax
		cmp dword ptr [esi+0Ch], 1h
		je L10_66CA4B
		__emit 0E8h
		__emit 043h
		__emit 083h
		__emit 09Bh
		__emit 0FFh   // call 0x24D6B
		mov dword ptr [esi+0Ch], 1h
		lea eax,  [esi+edi*8+30h]
		mov ecx, 8h
L11_66CA38:
		mov byte ptr [eax], 0h
		add eax, 40h
		dec ecx
		jne L11_66CA38
		mov dword ptr [esi+25Ch], 0h
L10_66CA4B:
		cmp dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		je L12_66CA62
		mov ecx, dword ptr [eax+3Ch]
		cmp dword ptr [esi+4h], ecx
		je L13_66CB1D
L12_66CA62:
		mov eax, dword ptr [eax+3Ch]
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
		mov dword ptr [esi+4h], eax
		call ebp
		mov dword ptr [esi+8h], eax
		jmp L14_66CB23
L09_66CA78:
		jle L15_66CA06
		mov byte ptr [esi+270h], 1h
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		test eax, eax
		je L16_66CA94
		mov ecx, dword ptr [eax+118h]
		test ecx, ecx
		jne L17_66CB10
L16_66CA94:
		cmp dword ptr [esi+0Ch], 1h
		jne L17_66CB10
		cmp word ptr [esi+ebp*2+272h], 5h
		jb L18_66CAAF
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		jne L19_66CB0B
L18_66CAAF:
		mov ecx, ebx
		__emit 0E8h
		__emit 0A7h
		__emit 06Ah
		__emit 099h
		__emit 0FFh   // call 0x355D
		cmp eax, 2h
		jl L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		test ecx, ecx
		je L21_66CAEC
		mov edx, dword ptr [ecx]
		call dword ptr [edx+38h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+34h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+40h]
		test al, al
		jne L20_66CB01
L21_66CAEC:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 00Ch
		__emit 07Eh
		__emit 09Ch
		__emit 0FFh   // call 0x34900
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 01Ch
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L20_66CB01:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L17_66CB10
L19_66CB0B:
		mov eax, dword ptr [ecx]
		call dword ptr [eax+78h]
L17_66CB10:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 000h
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L13_66CB1D:
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
L14_66CB23:
		cmp dword ptr [esi+0Ch], 1h
		je L22_66CB31
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 0E4h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x27615
L22_66CB31:
		mov al, byte ptr [esp+13h]
		test al, al
		mov ebx, 7D0h
		je L23_66CC5E
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		call ebp
		sub eax, dword ptr [esi+268h]
		cmp eax, 0BB8h
		jbe L25_66CC72
		mov eax, dword ptr [esp+14h]
		test eax, eax
		je L26_66CB7D
		call ebp
		sub eax, dword ptr [esi+25Ch]
		cmp eax, 1388h
		jae L25_66CC72
L26_66CB7D:
		lea ecx,  [esp+1Ch]
		__emit 0E8h
		__emit 004h
		__emit 039h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0E4h
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f70e4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+54h]
		push eax
		mov dword ptr [esp+50h], 0h
		call dword ptr [edx+4h]
		mov ecx, dword ptr [eax]
		mov eax, dword ptr [ecx]
		mov eax, dword ptr [eax+8h]
		test eax, eax
		mov byte ptr [esp+4Ch], 1h
		lea ecx,  [eax+8h]
		jne L27_66CBB6
		mov ecx, 107388Bh
L27_66CBB6:
		mov eax, ecx
		lea edi,  [eax+1h]
		jmp L28_66CBC0
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L28_66CBC0:
		mov dl, byte ptr [eax]
		inc eax
		test dl, dl
		jne L28_66CBC0
		sub eax, edi
		add eax, ecx
		push eax
		push ecx
		lea ecx,  [esp+24h]
		__emit 0E8h
		__emit 0C1h
		__emit 0E6h
		__emit 09Bh
		__emit 0FFh   // call 0x2B297
		lea ecx,  [esp+54h]
		mov byte ptr [esp+4Ch], 0h
		__emit 0E8h
		__emit 027h
		__emit 0C4h
		__emit 09Ah
		__emit 0FFh   // call 0x1900B
		mov eax, dword ptr [esp+54h]
		test eax, eax
		je L29_66CBF7
		push 0Ch
		push eax
		__emit 0E8h
		__emit 0FCh
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L29_66CBF7:
		mov ecx, dword ptr [esi+260h]
		mov eax, 5h
		add ecx, eax
		mov dword ptr [esp+28h], eax
		mov dword ptr [esi+260h], ecx
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		lea eax,  [esp+1Ch]
		mov dword ptr [esp+2Ch], ebx
		mov edx, dword ptr [ecx]
		push eax
		call dword ptr [edx+10h]
		call ebp
		mov ecx, dword ptr [esp+1Ch]
		mov dword ptr [esi+268h], eax
		mov eax, dword ptr [esp+24h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L25_66CC72
		cmp eax, 80h
		jbe L30_66CC52
		push ecx
		__emit 0E8h
		__emit 063h
		__emit 052h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		jmp L25_66CC72
L30_66CC52:
		push eax
		push ecx
		__emit 0E8h
		__emit 097h
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		jmp L25_66CC72
L23_66CC5E:
		xor eax, eax
		mov dword ptr [esi+260h], eax
		mov dword ptr [esi+264h], eax
		mov dword ptr [esi+268h], eax
L25_66CC72:
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		lea ecx,  [esp+30h]
		__emit 0E8h
		__emit 002h
		__emit 038h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		mov dword ptr [esp+50h], 2h
		call dword ptr [edx+1Ch]
		test al, al
		je L31_66CCD8
L33_66CCA4:
		mov al, byte ptr [esp+13h]
		test al, al
		je L32_66CCC4
		cmp dword ptr [esp+3Ch], ebx
		jge L32_66CCC4
		mov eax, dword ptr [esi+264h]
		mov ecx, dword ptr [esp+40h]
		add eax, ecx
		mov dword ptr [esi+264h], eax
L32_66CCC4:
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		call dword ptr [edx+1Ch]
		test al, al
		jne L33_66CCA4
L31_66CCD8:
		mov ecx, dword ptr [esp+30h]
		mov eax, dword ptr [esp+38h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L24_66CD1D
		cmp eax, 80h
		jbe L34_66CD13
		push ecx
		__emit 0E8h
		__emit 0B5h
		__emit 051h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov ecx, dword ptr [esp+34h]
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
L34_66CD13:
		push eax
		push ecx
		__emit 0E8h
		__emit 0D6h
		__emit 018h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L24_66CD1D:
		mov ecx, dword ptr [esp+44h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
	}
}

// The destructor body. 0x00681E10 is its scalar deleting wrapper -- call this,
// then operator delete when the low bit of the flag argument is set -- and the
// native Network teardown at 0x00681E40 and 0x006823B0 call it too. It releases
// the tail objects at this+0x12104, +0x12108, +0x1210C, +0x12118, +0x1211C,
// +0x12124, +0x12128 and +0x12130 and hands their STL nodes back to the pool.
// Ghidra sizes it 558, three bytes short of its ret.
__declspec(naked) void BFMEConnectionManager::destroy()
{
	__asm {
		push 0FFFFFFFFh
		push 104453Dh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		push ebp
		mov ebp, ecx
		push esi
		push edi
		mov dword ptr [esp+14h], ebp
		mov dword ptr [ebp], 111A2B0h
		mov esi, dword ptr [ebp+12024h]
		test esi, esi
		mov dword ptr [esp+24h], 3h
		je L00_668DDB
		mov ecx, esi
		__emit 0E8h
		__emit 0B9h
		__emit 016h
		__emit 09Dh
		__emit 0FFh   // call 0x3A48B
		push esi
		__emit 0E8h
		__emit 0D8h
		__emit 090h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L00_668DDB:
		lea edi,  [ebp+4h]
		mov dword ptr [esp+10h], 8h
		mov ebx, 4h
		jmp L01_668DF0
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L01_668DF0:
		mov ecx, dword ptr [edi+120E0h]
		test ecx, ecx
		je L02_668E00
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L02_668E00:
		mov esi, dword ptr [edi]
		test esi, esi
		je L03_668E31
		mov dword ptr [esp+18h], esi
		mov ecx, dword ptr [esi+18h]
		test ecx, ecx
		mov byte ptr [esp+24h], bl
		je L04_668E1B
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L04_668E1B:
		lea ecx,  [esi+14h]
		mov byte ptr [esp+24h], 3h
		__emit 0E8h
		__emit 0A8h
		__emit 0F3h
		__emit 021h
		__emit 000h   // call 0x8881D0
		push esi
		__emit 0E8h
		__emit 082h
		__emit 090h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L03_668E31:
		mov eax, dword ptr [esp+10h]
		add edi, ebx
		dec eax
		mov dword ptr [esp+10h], eax
		jne L01_668DF0
		__emit 0E8h
		__emit 028h
		__emit 0BFh
		__emit 09Bh
		__emit 0FFh   // call 0x24D6B
		mov ecx, dword ptr [ebp+120E0h]
		xor edi, edi
		cmp ecx, edi
		je L05_668E55
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L05_668E55:
		mov ecx, dword ptr [ebp+12104h]
		cmp ecx, edi
		je L06_668E65
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L06_668E65:
		mov ecx, dword ptr [ebp+12108h]
		cmp ecx, edi
		je L07_668E75
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L07_668E75:
		mov ecx, dword ptr [ebp+1210Ch]
		cmp ecx, edi
		je L08_668E85
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L08_668E85:
		mov eax, dword ptr [ebp+1211Ch]
		cmp eax, edi
		lea esi,  [ebp+12118h]
		je L09_668EB4
		mov eax, dword ptr [esi]
		mov ecx, dword ptr [eax+4h]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 049h
		__emit 09Ah
		__emit 09Ah
		__emit 0FFh   // call 0x128EB
		mov eax, dword ptr [esi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [esi]
		mov dword ptr [edx+4h], edi
		mov eax, dword ptr [esi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [esi+4h], edi
L09_668EB4:
		mov eax, dword ptr [ebp+12128h]
		lea ebx,  [ebp+12124h]
		xor ecx, ecx
		cmp eax, ecx
		je L10_668F03
		mov eax, dword ptr [ebx]
		mov esi, dword ptr [eax+4h]
		cmp esi, ecx
		je L11_668EF1
		nop
L12_668ED0:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, ebx
		__emit 0E8h
		__emit 044h
		__emit 0FCh
		__emit 09Ah
		__emit 0FFh   // call 0x18B1F
		mov edi, dword ptr [esi+8h]
		push 14h
		push esi
		__emit 0E8h
		__emit 00Ah
		__emit 057h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test edi, edi
		mov esi, edi
		jne L12_668ED0
		xor ecx, ecx
L11_668EF1:
		mov eax, dword ptr [ebx]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [ebx]
		mov dword ptr [edx+4h], ecx
		mov eax, dword ptr [ebx]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [ebx+4h], ecx
L10_668F03:
		lea edi,  [ebp+12130h]
		mov dword ptr [esp+10h], 8h
L16_668F11:
		cmp dword ptr [edi+4h], ecx
		je L13_668F57
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ecx
		je L14_668F45
		nop
L15_668F20:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 02Fh
		__emit 0F6h
		__emit 09Ch
		__emit 0FFh   // call 0x3855A
		mov ebp, dword ptr [esi+8h]
		push 18h
		push esi
		__emit 0E8h
		__emit 0BAh
		__emit 056h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L15_668F20
		mov ebp, dword ptr [esp+14h]
		xor ecx, ecx
L14_668F45:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ecx
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ecx
L13_668F57:
		mov eax, dword ptr [esp+10h]
		add edi, 0Ch
		dec eax
		mov dword ptr [esp+10h], eax
		jne L16_668F11
		push 43C961h
		push 8h
		push 0Ch
		lea eax,  [ebp+12130h]
		push eax
		mov byte ptr [esp+34h], 2h
		__emit 0E8h
		__emit 0F7h
		__emit 0DDh
		__emit 038h
		__emit 000h   // call 0x9F6D76
		mov ecx, ebx
		mov byte ptr [esp+24h], 1h
		__emit 0E8h
		__emit 08Ch
		__emit 0C7h
		__emit 09Ah
		__emit 0FFh   // call 0x15717
		lea ecx,  [ebp+12118h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 0F5h
		__emit 090h
		__emit 099h
		__emit 0FFh   // call 0x2090
		lea ecx,  [ebp+12058h]
		mov dword ptr [esp+24h], 0FFFFFFFFh
		__emit 0E8h
		__emit 022h
		__emit 0F2h
		__emit 021h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 18h
		ret
	}
}

// Reassembles a chunked command. Feeds the message to
// NetCommandWrapperList::processWrapper on the list at this+0x12130, keyed by
// getWrappedCommandID, then reports progress with getPercentComplete and sends
// the acknowledgement back through sendLocalCommand.
__declspec(naked) void BFMEConnectionManager::processWrappedCommand(void *msg)
{
	__asm {
		push 0FFFFFFFFh
		push 104464Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		mov ebp, dword ptr [esp+1Ch]
		push esi
		mov esi, ecx
		mov ecx, dword ptr [ebp]
		push edi
		__emit 0E8h
		__emit 04Fh
		__emit 0BBh
		__emit 099h
		__emit 0FFh   // call 0x57C7
		lea edi,  [esi+12118h]
		mov ecx, edi
		mov dword ptr [esp+10h], 0h
		mov dword ptr [esp+24h], eax
		lea eax,  [esp+24h]
		push eax
		__emit 0E8h
		__emit 074h
		__emit 0BBh
		__emit 09Ch
		__emit 0FFh   // call 0x3580A
		mov ebx, eax
		cmp ebx, dword ptr [edi]
		je L00_669CBC
		mov eax, dword ptr [esi+12028h]
		lea ecx,  [esp+24h]
		__emit 08Dh
		__emit 014h
		__emit 040h   // lea edx, [eax + eax*2]
		push ecx
		lea ecx,  [esi+edx*4+12130h]
		__emit 0E8h
		__emit 03Bh
		__emit 066h
		__emit 09Ch
		__emit 0FFh   // call 0x302F1
		mov eax, dword ptr [eax]
		mov dword ptr [esp+10h], eax
L00_669CBC:
		mov ecx, dword ptr [esi+1210Ch]
		test ecx, ecx
		je L01_669DA9
		push ebp
		__emit 0E8h
		__emit 039h
		__emit 06Eh
		__emit 09Ah
		__emit 0FFh   // call 0x10B09
		cmp ebx, dword ptr [edi]
		je L01_669DA9
		mov ecx, dword ptr [esp+24h]
		push ecx
		mov ecx, dword ptr [esi+1210Ch]
		__emit 0E8h
		__emit 083h
		__emit 00Dh
		__emit 09Eh
		__emit 0FFh   // call 0x4AA6B
		mov ebp, eax
		cmp ebp, dword ptr [esp+10h]
		jle L01_669DA9
		cmp ebp, 64h
		jge L01_669DA9
		mov eax, dword ptr [esi+12028h]
		lea edx,  [esp+24h]
		__emit 08Dh
		__emit 004h
		__emit 040h   // lea eax, [eax + eax*2]
		push edx
		lea ecx,  [esi+eax*4+12130h]
		__emit 0E8h
		__emit 0DAh
		__emit 065h
		__emit 09Ch
		__emit 0FFh   // call 0x302F1
		mov dword ptr [eax], ebp
		mov ecx, dword ptr [esi+12028h]
		mov ebx, 1h
		shl ebx, cl
		push 24h
		xor ebx, 0FFh
		__emit 0E8h
		__emit 0FDh
		__emit 081h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		xor edi, edi
		cmp eax, edi
		mov dword ptr [esp+1Ch], edi
		je L02_669D4D
		mov ecx, eax
		__emit 0E8h
		__emit 08Fh
		__emit 06Ch
		__emit 09Dh
		__emit 0FFh   // call 0x409DA
		mov edi, eax
L02_669D4D:
		mov ecx, dword ptr [esi+12028h]
		mov eax, dword ptr [edi+14h]
		push eax
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov dword ptr [edi+0Ch], ecx
		mov word ptr [edi+10h], 0h
		__emit 0E8h
		__emit 005h
		__emit 0BEh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L03_669D7D
		__emit 0E8h
		__emit 0DFh
		__emit 067h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [edi+10h], ax
L03_669D7D:
		mov edx, dword ptr [esp+24h]
		push edx
		mov ecx, edi
		__emit 0E8h
		__emit 065h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x247EE
		push ebp
		mov ecx, edi
		__emit 0E8h
		__emit 025h
		__emit 0B6h
		__emit 09Ah
		__emit 0FFh   // call 0x153B6
		push ebx
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0E0h
		__emit 053h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0D1h
		__emit 065h
		__emit 09Ch
		__emit 0FFh   // call 0x30373
		mov ecx, edi
		__emit 0E8h
		__emit 0FBh
		__emit 062h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L01_669DA9:
		mov ecx, dword ptr [esp+14h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Retires acknowledged commands. Reads the acknowledged id and originating
// player from either a stage-2 or a both-stages ack message, then searches the
// two pending-command lists at this+0x12104 and this+0x12108 with
// NetCommandList::findMessage and removes the entry.
__declspec(naked) void BFMEConnectionManager::processAckCommand(void *msg)
{
	__asm {
		push 0FFFFFFFFh
		push 104420Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 8h
		push ebx
		push esi
		push edi
		mov edi, dword ptr [esp+24h]
		mov eax, dword ptr [edi+14h]
		cmp eax, 2h
		mov esi, ecx
		mov dword ptr [esp+0Ch], esi
		jne L00_66574A
		mov ecx, edi
		__emit 0E8h
		__emit 041h
		__emit 002h
		__emit 09Ah
		__emit 0FFh   // call 0x5975
		mov ecx, edi
		mov ebx, eax
		__emit 0E8h
		__emit 00Fh
		__emit 01Ah
		__emit 09Ch
		__emit 0FFh   // call 0x2714C
		mov byte ptr [esp+24h], al
		mov eax, dword ptr [edi+20h]
		mov dword ptr [esp+10h], eax
		jmp L01_66576D
L00_66574A:
		test eax, eax
		jne L02_66586F
		mov ecx, edi
		__emit 0E8h
		__emit 088h
		__emit 01Dh
		__emit 09Ah
		__emit 0FFh   // call 0x74E1
		mov ecx, edi
		mov ebx, eax
		__emit 0E8h
		__emit 0B5h
		__emit 015h
		__emit 09Eh
		__emit 0FFh   // call 0x46D17
		mov ecx, dword ptr [edi+20h]
		mov byte ptr [esp+24h], al
		mov dword ptr [esp+10h], ecx
L01_66576D:
		mov ecx, dword ptr [esi+12104h]
		test ecx, ecx
		push ebp
		mov ebp, dword ptr [esp+28h]
		je L03_6657A9
		push ebp
		push ebx
		__emit 0E8h
		__emit 0D2h
		__emit 0A8h
		__emit 09Ah
		__emit 0FFh   // call 0x10055
		mov esi, eax
		test esi, esi
		je L03_6657A9
		mov edx, dword ptr [esp+10h]
		mov ecx, dword ptr [edx+12104h]
		push esi
		__emit 0E8h
		__emit 0D1h
		__emit 096h
		__emit 09Ch
		__emit 0FFh   // call 0x2EE6A
		mov ecx, esi
		__emit 0E8h
		__emit 0C0h
		__emit 031h
		__emit 09Dh
		__emit 0FFh   // call 0x38960
		push esi
		__emit 0E8h
		__emit 00Ah
		__emit 0C7h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L03_6657A9:
		mov eax, dword ptr [esp+10h]
		mov ecx, dword ptr [eax+12108h]
		test ecx, ecx
		je L04_66586E
		mov edx, dword ptr [esp+14h]
		push edx
		push ebp
		push ebx
		__emit 0E8h
		__emit 0CFh
		__emit 083h
		__emit 09Ch
		__emit 0FFh   // call 0x2DB96
		mov esi, eax
		test esi, esi
		je L04_66586E
		mov ecx, dword ptr [edi+0Ch]
		mov dl, byte ptr [esi+0Ch]
		mov al, 1h
		shl al, cl
		not al
		and al, dl
		jne L05_66586B
		mov ebx, dword ptr [esp+10h]
		mov ecx, dword ptr [ebx+12108h]
		push esi
		__emit 0E8h
		__emit 075h
		__emit 096h
		__emit 09Ch
		__emit 0FFh   // call 0x2EE6A
		push 24h
		__emit 0E8h
		__emit 034h
		__emit 0C7h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+28h], eax
		test eax, eax
		mov dword ptr [esp+20h], 0h
		je L06_66581D
		mov ecx, dword ptr [esi]
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 068h
		__emit 0CFh
		__emit 09Ch
		__emit 0FFh   // call 0x32781
		mov edi, eax
		jmp L07_66581F
L06_66581D:
		xor edi, edi
L07_66581F:
		mov ecx, edi
		mov dword ptr [esp+20h], 0FFFFFFFFh
		__emit 0E8h
		__emit 01Eh
		__emit 019h
		__emit 09Ch
		__emit 0FFh   // call 0x2714C
		xor edx, edx
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		mov ecx, ebx
		push edx
		push edi
		__emit 0E8h
		__emit 03Bh
		__emit 099h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 01Ah
		__emit 031h
		__emit 09Dh
		__emit 0FFh   // call 0x38960
		push esi
		__emit 0E8h
		__emit 064h
		__emit 0C6h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		mov ecx, edi
		__emit 0E8h
		__emit 04Eh
		__emit 0A8h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop ebp
		pop edi
		pop esi
		pop ebx
		mov ecx, dword ptr [esp+8h]
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret 4h
L05_66586B:
		mov byte ptr [esi+0Ch], al
L04_66586E:
		pop ebp
L02_66586F:
		mov ecx, dword ptr [esp+14h]
		pop edi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret 4h
	}
}

// Starts a player's departure. Marks that player's FrameDataManager at
// this+0x120E4 with setQuitFrame, skipping managers already reporting
// getIsQuitting, and builds and sends the follow-up command directly to the
// affected peers. NetworkKeepAliveDelay from TheGlobalData +0xCB4 bounds how far
// ahead the quit frame may be placed.
__declspec(naked) void BFMEConnectionManager::beginPlayerLeave(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 104444Bh
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebp
		push esi
		push edi
		movzx edi, byte ptr [esp+28h]
		mov ebp, ecx
		cmp edi, dword ptr [ebp+12028h]
		jne L00_66737E
		lea esi,  [ebp+4h]
		mov edi, 8h
L02_667352:
		mov ecx, dword ptr [esi]
		test ecx, ecx
		je L01_667376
		mov eax, dword ptr [ebp+12028h]
		push eax
		__emit 0E8h
		__emit 0FDh
		__emit 0B6h
		__emit 09Bh
		__emit 0FFh   // call 0x22A61
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+3Ch]
		mov ecx, dword ptr [esi]
		inc eax
		push eax
		__emit 0E8h
		__emit 0E4h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x4845A
L01_667376:
		add esi, 4h
		dec edi
		jne L02_667352
		jmp L03_6673C6
L00_66737E:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov ecx, dword ptr [ebp+edi*4+4h]
		test ecx, ecx
		mov eax, dword ptr [edx+3Ch]
		lea esi,  [eax+1h]
		je L04_667398
		push esi
		__emit 0E8h
		__emit 0C2h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x4845A
L04_667398:
		mov ecx, dword ptr [ebp+edi*4+120E4h]
		test ecx, ecx
		je L03_6673C6
		__emit 0E8h
		__emit 034h
		__emit 0C3h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne L03_6673C6
		__emit 0A1h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov eax, dword ptr [0x12ed5c8]
		mov ecx, dword ptr [eax+0CB4h]
		add ecx, esi
		push ecx
		mov ecx, dword ptr [ebp+edi*4+120E4h]
		__emit 0E8h
		__emit 0A1h
		__emit 039h
		__emit 09Ah
		__emit 0FFh   // call 0xAD67
L03_6673C6:
		movzx eax, byte ptr [esp+28h]
		push eax
		mov ecx, ebp
		__emit 0E8h
		__emit 08Ah
		__emit 019h
		__emit 09Ch
		__emit 0FFh   // call 0x28D5D
		cmp eax, 2h
		mov dword ptr [esp+10h], eax
		__emit 00Fh
		__emit 085h
		__emit 031h
		__emit 001h
		__emit 000h
		__emit 000h   // jne 0x667511
		push ebx
		xor bl, bl
		mov byte ptr [esp+10h], bl
		lea edi,  [ebp+8h]
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L11_6673F0:
		mov ecx, dword ptr [ebp+12028h]
		lea edx,  [eax-2h]
		cmp edx, ecx
		je L06_667412
		mov ecx, dword ptr [edi-4h]
		test ecx, ecx
		je L06_667412
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L06_667412
		lea ecx,  [eax-2h]
		mov dl, 1h
		shl dl, cl
		or bl, dl
L06_667412:
		mov edx, dword ptr [ebp+12028h]
		lea ecx,  [eax-1h]
		cmp ecx, edx
		je L07_667433
		mov ecx, dword ptr [edi]
		test ecx, ecx
		je L07_667433
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L07_667433
		lea ecx,  [eax-1h]
		mov dl, 1h
		shl dl, cl
		or bl, dl
L07_667433:
		cmp eax, dword ptr [ebp+12028h]
		je L08_66744F
		mov ecx, dword ptr [edi+4h]
		test ecx, ecx
		je L08_66744F
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L08_66744F
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		or bl, dl
L08_66744F:
		mov ecx, dword ptr [ebp+12028h]
		lea esi,  [eax+1h]
		cmp esi, ecx
		je L09_667474
		mov edx, dword ptr [edi+8h]
		test edx, edx
		je L09_667474
		cmp esi, ecx
		je L10_66746C
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L09_667474
L10_66746C:
		mov dl, 1h
		mov ecx, esi
		shl dl, cl
		or bl, dl
L09_667474:
		add eax, 4h
		lea ecx,  [eax-2h]
		add edi, 10h
		cmp ecx, 8h
		jl L11_6673F0
		mov byte ptr [esp+10h], bl
		test bl, bl
		pop ebx
		__emit 00Fh
		__emit 084h
		__emit 07Eh
		__emit 000h
		__emit 000h
		__emit 000h   // je 0x667511
		push 24h
		__emit 0E8h
		__emit 096h
		__emit 0AAh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+14h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+20h], esi
		je L12_6674B4
		mov ecx, eax
		__emit 0E8h
		__emit 07Dh
		__emit 032h
		__emit 09Ch
		__emit 0FFh   // call 0x2A72F
		mov esi, eax
L12_6674B4:
		mov edx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+20h], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 0A2h
		__emit 0E6h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L13_6674E0
		__emit 0E8h
		__emit 07Ch
		__emit 090h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L13_6674E0:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 0DBh
		__emit 036h
		__emit 09Ch
		__emit 0FFh   // call 0x2ABCB
		movzx eax, byte ptr [esp+28h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 035h
		__emit 030h
		__emit 09Bh
		__emit 0FFh   // call 0x1A532
		mov edx, dword ptr [esp+0Ch]
		push edx
		push esi
		mov ecx, ebp
		__emit 0E8h
		__emit 0CDh
		__emit 09Ch
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 093h
		__emit 08Bh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L05_667511:
		__emit 0E8h
		__emit 038h
		__emit 01Ah
		__emit 09Ah
		__emit 0FFh   // call 0x8F4E
		mov ecx, dword ptr [esp+18h]
		mov eax, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		add esp, 18h
		ret 4h
	}
}

// Reads a slice of a file through TheFileSystem and ships it as a
// NetFileCommandMsg -- it is the only caller of NetFileCommandMsg::setFileData
// in this band -- then hands the message to sendLocalCommand. The progress text
// it formats goes out as a UnicodeString.
__declspec(naked) void BFMEConnectionManager::sendFileChunk(const char *path, int playerMask, int chunk)
{
	__asm {
		push 0FFFFFFFFh
		push 10443B3h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		push ebp
		push esi
		push edi
		mov ebx, ecx
		mov eax, dword ptr [esp+2Ch]
		xor edi, edi
		cmp eax, edi
		mov dword ptr [esp+24h], edi
		je L00_666A41
		add eax, 8h
		jmp L01_666A46
L00_666A41:
		mov eax, 107388Bh
L01_666A46:
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0CBh
		__emit 034h
		__emit 001h   // mov ecx, dword ptr [0x134cb48]
		push edi
		push eax
		__emit 0E8h
		__emit 00Dh
		__emit 01Eh
		__emit 036h
		__emit 000h   // call 0x9C8860
		mov esi, eax
		cmp esi, edi
		je L02_666AFC
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+2Ch]
		test eax, eax
		je L02_666AFC
		mov edx, dword ptr [esi]
		mov ecx, esi
		call dword ptr [edx+2Ch]
		mov ebp, eax
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+34h]
		push 28h
		mov edi, eax
		__emit 0E8h
		__emit 0ABh
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		test eax, eax
		mov byte ptr [esp+24h], 3h
		je L03_666AA0
		mov ecx, eax
		__emit 0E8h
		__emit 0AFh
		__emit 0BEh
		__emit 099h
		__emit 0FFh   // call 0x294B
		mov esi, eax
		jmp L04_666AA2
L03_666AA0:
		xor esi, esi
L04_666AA2:
		mov cx, word ptr [esp+34h]
		mov eax, dword ptr [ebx+12028h]
		mov word ptr [esi+10h], cx
		lea edx,  [esp+2Ch]
		mov byte ptr [esp+24h], 0h
		mov dword ptr [esi+0Ch], eax
		push ecx
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 096h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x887B60
		mov ecx, esi
		__emit 0E8h
		__emit 025h
		__emit 046h
		__emit 09Eh
		__emit 0FFh   // call 0x4B0F6
		push ebp
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0FBh
		__emit 028h
		__emit 09Bh
		__emit 0FFh   // call 0x193D5
		push edi
		__emit 0E8h
		__emit 010h
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x881EF0
		mov eax, dword ptr [esp+34h]
		add esp, 4h
		push eax
		push esi
		mov ecx, ebx
		__emit 0E8h
		__emit 08Ah
		__emit 086h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0ADh
		__emit 095h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		jmp L05_666B9D
L02_666AFC:
		mov dword ptr [esp+34h], edi
		movzx ecx, byte ptr [esp+30h]
		mov eax, dword ptr [esp+2Ch]
		cmp eax, edi
		mov bl, 1h
		mov byte ptr [esp+24h], bl
		push ecx
		je L06_666B19
		add eax, 8h
		jmp L07_666B1E
L06_666B19:
		mov eax, 107388Bh
L07_666B1E:
		push eax
		push ecx
		mov dword ptr [esp+3Ch], esp
		mov ecx, esp
		push 111A268h
		__emit 0E8h
		__emit 0B0h
		__emit 022h
		__emit 022h
		__emit 000h   // call 0x888DE0
		lea edx,  [esp+40h]
		push edx
		__emit 0E8h
		__emit 056h
		__emit 026h
		__emit 022h
		__emit 000h   // call 0x889190
		__emit 0A1h
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7730]
		add esp, 10h
		cmp eax, edi
		je L08_666B8F
		push 2h
		push ecx
		lea eax,  [esp+3Ch]
		mov dword ptr [esp+38h], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 0A7h
		__emit 018h
		__emit 022h
		__emit 000h   // call 0x888400
		lea ecx,  [esp+1Ch]
		push ecx
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 111A250h
		mov byte ptr [esp+38h], 2h
		mov dword ptr [esp+28h], edi
		mov word ptr [esp+2Ch], di
		__emit 0E8h
		__emit 063h
		__emit 022h
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 08Bh
		__emit 00Dh
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7730]
		mov edx, dword ptr [ecx]
		mov byte ptr [esp+34h], bl
		call dword ptr [edx+8Ch]
L08_666B8F:
		lea ecx,  [esp+34h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 033h
		__emit 016h
		__emit 022h
		__emit 000h   // call 0x8881D0
L05_666B9D:
		lea ecx,  [esp+2Ch]
		mov dword ptr [esp+24h], 0FFFFFFFFh
		__emit 0E8h
		__emit 092h
		__emit 00Dh
		__emit 022h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 18h
		ret 0Ch
	}
}

// Walks the per-transfer map at this+0x12130 with the STL red-black tree
// iterator and refreshes the progress bookkeeping at this+0x12118, releasing
// the AsciiString buffers it built along the way.
__declspec(naked) void BFMEConnectionManager::updateFileProgress()
{
	__asm {
		push 0FFFFFFFFh
		push 1044608h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		push edi
		mov dword ptr [esp+10h], ecx
		mov ecx, dword ptr [ecx+12118h]
		mov eax, dword ptr [ecx+8h]
		cmp eax, ecx
		mov dword ptr [esp+1Ch], 0h
		je L00_669A9C
L10_669A33:
		mov ecx, dword ptr [esp+28h]
		test ecx, ecx
		je L01_669A44
		movzx ebp, word ptr [ecx+4h]
		lea edi,  [ecx+8h]
		jmp L02_669A4B
L01_669A44:
		xor ebp, ebp
		mov edi, 107388Bh
L02_669A4B:
		mov ecx, dword ptr [eax+14h]
		test ecx, ecx
		je L03_669A58
		movzx ebx, word ptr [ecx+4h]
		jmp L04_669A5A
L03_669A58:
		xor ebx, ebx
L04_669A5A:
		test ecx, ecx
		lea esi,  [ecx+8h]
		jne L05_669A66
		mov esi, 107388Bh
L05_669A66:
		cmp ebx, ebp
		mov ecx, ebx
		jl L06_669A6E
		mov ecx, ebp
L06_669A6E:
		xor edx, edx
		repe cmpsb
		je L07_669A79
		sbb edx, edx
		sbb edx, 0FFFFFFFFh
L07_669A79:
		test edx, edx
		jne L08_669A85
		sub ebx, ebp
		mov edx, ebx
		test edx, edx
		je L09_669AC4
L08_669A85:
		push eax
		__emit 0E8h
		__emit 0E5h
		__emit 01Dh
		__emit 01Ch
		__emit 000h   // call 0x82B870
		mov ecx, dword ptr [esp+14h]
		mov edx, dword ptr [ecx+12118h]
		add esp, 4h
		cmp eax, edx
		jne L10_669A33
L00_669A9C:
		lea ecx,  [esp+28h]
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 093h
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x887940
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		mov ecx, dword ptr [esp+4h]
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 8h
L09_669AC4:
		add eax, 10h
		push eax
		mov eax, dword ptr [esp+28h]
		__emit 08Dh
		__emit 014h
		__emit 040h   // lea edx, [eax + eax*2]
		mov eax, dword ptr [esp+14h]
		lea ecx,  [eax+edx*4+12130h]
		__emit 0E8h
		__emit 012h
		__emit 068h
		__emit 09Ch
		__emit 0FFh   // call 0x302F1
		mov esi, dword ptr [eax]
		lea ecx,  [esp+28h]
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 04Eh
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		pop edi
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 8h
	}
}

// Composes the per-player status line the disconnect and load screens show. It
// reads the slot list through GameInfo::getConstSlot, asks each
// FrameDataManager at this+0x120E4 whether it is quitting, consults the id
// array at this+0x12030 and the state array at this+0x12080, and assembles the
// result as a UnicodeString.
__declspec(naked) void BFMEConnectionManager::buildPlayerStatusText(void *out)
{
	__asm {
		push 0FFFFFFFFh
		push 10442F0h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		mov ebx, dword ptr [esp+20h]
		push ebp
		push esi
		push edi
		xor edi, edi
		cmp ebx, edi
		mov ebp, ecx
		mov dword ptr [esp+10h], edi
		__emit 00Fh
		__emit 08Ch
		__emit 0F8h
		__emit 001h
		__emit 000h
		__emit 000h   // jl 0x666528
		cmp ebx, 8h
		__emit 00Fh
		__emit 08Dh
		__emit 0EFh
		__emit 001h
		__emit 000h
		__emit 000h   // jge 0x666528
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		cmp ecx, edi
		je L01_66635E
		push ebx
		__emit 0E8h
		__emit 0CFh
		__emit 088h
		__emit 09Bh
		__emit 0FFh   // call 0x1EC18
		cmp eax, edi
		je L01_66635E
		cmp dword ptr [eax+3Ch], edi
		jne L01_66635E
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		mov dword ptr [eax+3Ch], edx
L01_66635E:
		mov dword ptr [esp+2Ch], edi
		push ebx
		lea eax,  [esp+18h]
		push eax
		mov ecx, ebp
		mov dword ptr [esp+2Ch], edi
		__emit 0E8h
		__emit 0EFh
		__emit 0C6h
		__emit 09Ah
		__emit 0FFh   // call 0x12A62
		push eax
		lea ecx,  [esp+30h]
		mov byte ptr [esp+28h], 1h
		__emit 0E8h
		__emit 0AEh
		__emit 021h
		__emit 022h
		__emit 000h   // call 0x888530
		lea ecx,  [esp+14h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 040h
		__emit 01Eh
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esp+2Ch]
		cmp eax, edi
		je L02_6663CE
		movzx ecx, word ptr [eax+4h]
		cmp ecx, edi
		jle L02_6663CE
		cmp dword ptr [ebp+ebx*4+4h], edi
		je L02_6663CE
		add eax, 8h
		push eax
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 1104E54h
		__emit 0E8h
		__emit 005h
		__emit 028h
		__emit 022h
		__emit 000h   // call 0x888BC0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		push eax
		call dword ptr [ecx+3Ch]
		add esp, 0Ch
		__emit 0E8h
		__emit 012h
		__emit 0C9h
		__emit 0FFh
		__emit 0FFh   // call 0x662CE0
L02_6663CE:
		mov ecx, dword ptr [ebp+ebx*4+120E4h]
		cmp ecx, edi
		je L03_6663FA
		__emit 0E8h
		__emit 0FEh
		__emit 0D2h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne L03_6663FA
		mov ecx, dword ptr [ebp+ebx*4+120E4h]
		cmp ecx, edi
		je L04_6663F3
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L04_6663F3:
		mov dword ptr [ebp+ebx*4+120E4h], edi
L03_6663FA:
		mov esi, dword ptr [ebp+ebx*4+4h]
		cmp esi, edi
		je L05_66641B
		cmp dword ptr [esi], 0FFFFFFFFh
		jne L05_66641B
		mov ecx, esi
		__emit 0E8h
		__emit 0C1h
		__emit 06Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3CECF
		push esi
		__emit 0E8h
		__emit 09Ch
		__emit 0BAh
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		mov dword ptr [ebp+ebx*4+4h], edi
L05_66641B:
		mov dword ptr [ebp+ebx*4+12080h], 3h
		mov eax, dword ptr [ebp+1202Ch]
		cmp ebx, eax
		__emit 00Fh
		__emit 085h
		__emit 07Dh
		__emit 000h
		__emit 000h
		__emit 000h   // jne 0x6664b1
		cmp eax, 8h
		jae L07_66644B
		shl eax, 0Dh
		lea edi,  [eax+ebp+24h]
		xor eax, eax
		mov ecx, 800h
		rep stosd
		xor edi, edi
L07_66644B:
		xor eax, eax
		lea ecx,  [ebp+12030h]
L09_666453:
		mov edx, dword ptr [ecx]
		cmp edx, dword ptr [ebp+1202Ch]
		je L08_666466
		inc eax
		add ecx, 4h
		cmp eax, 7h
		jb L09_666453
L08_666466:
		mov eax, dword ptr [ebp+eax*4+12034h]
		cmp eax, 8h
		mov dword ptr [ebp+1202Ch], eax
		jae L10_66648A
		shl eax, 0Dh
		lea edi,  [eax+ebp+24h]
		xor eax, eax
		mov ecx, 800h
		rep stosd
		xor edi, edi
L10_66648A:
		mov eax, dword ptr [ebp+12028h]
		cmp eax, dword ptr [ebp+1202Ch]
		je L11_6664A9
		xor eax, eax
		mov ecx, 800h
		lea edi,  [ebp+10024h]
		rep stosd
		xor edi, edi
L11_6664A9:
		mov dword ptr [esp+10h], 2h
L06_6664B1:
		cmp dword ptr [ebp+12028h], ebx
		jne L12_6664C1
		mov dword ptr [esp+10h], 1h
L12_6664C1:
		xor eax, eax
		lea ecx,  [ebp+12030h]
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L14_6664D0:
		cmp dword ptr [ecx], ebx
		je L13_6664DD
		inc eax
		add ecx, 4h
		cmp eax, 8h
		jl L14_6664D0
L13_6664DD:
		cmp eax, 7h
		jge L15_6664F9
		mov ecx, 7h
		lea edi,  [ebp+eax*4+12030h]
		lea esi,  [ebp+eax*4+12034h]
		sub ecx, eax
		rep movsd
L15_6664F9:
		or eax, 0FFFFFFFFh
		lea ecx,  [esp+2Ch]
		mov dword ptr [ebp+1204Ch], eax
		mov dword ptr [esp+24h], eax
		__emit 0E8h
		__emit 0C1h
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esp+10h]
		mov ecx, dword ptr [esp+1Ch]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 18h
		ret 4h
L00_666528:
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		mov eax, 3h
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 18h
		ret 4h
	}
}

// Builds a command message and puts it on the outgoing path. It runs the same
// filter at 0x00682E80 that sendLocalCommand uses, branches on whether
// m_localSlot equals m_packetRouterSlot, and hands the result to the packet
// assembler at 0x006624A0.
__declspec(naked) void BFMEConnectionManager::queueLocalCommand(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 1043FA6h
		push eax
		mov dword ptr fs:[0h], esp
		push ebx
		push ebp
		push esi
		mov esi, ecx
		mov eax, dword ptr [esi+4h]
		push edi
		mov edi, dword ptr [esp+20h]
		mov ebx, dword ptr [edi]
		xor cl, cl
		or ebp, 0FFFFFFFFh
		test eax, eax
		je L00_662EB3
		cmp dword ptr [eax], ebp
		jne L00_662EB3
		mov cl, 1h
L00_662EB3:
		mov eax, dword ptr [esi+8h]
		test eax, eax
		je L01_662EC1
		cmp dword ptr [eax], ebp
		jne L01_662EC1
		or cl, 2h
L01_662EC1:
		mov eax, dword ptr [esi+0Ch]
		test eax, eax
		je L02_662ECF
		cmp dword ptr [eax], ebp
		jne L02_662ECF
		or cl, 4h
L02_662ECF:
		mov eax, dword ptr [esi+10h]
		test eax, eax
		je L03_662EDD
		cmp dword ptr [eax], ebp
		jne L03_662EDD
		or cl, 8h
L03_662EDD:
		mov eax, dword ptr [esi+14h]
		test eax, eax
		je L04_662EEB
		cmp dword ptr [eax], ebp
		jne L04_662EEB
		or cl, 10h
L04_662EEB:
		mov eax, dword ptr [esi+18h]
		test eax, eax
		je L05_662EF9
		cmp dword ptr [eax], ebp
		jne L05_662EF9
		or cl, 20h
L05_662EF9:
		mov eax, dword ptr [esi+1Ch]
		test eax, eax
		je L06_662F07
		cmp dword ptr [eax], ebp
		jne L06_662F07
		or cl, 40h
L06_662F07:
		mov eax, dword ptr [esi+20h]
		test eax, eax
		je L07_662F15
		cmp dword ptr [eax], ebp
		jne L07_662F15
		or cl, 80h
L07_662F15:
		and cl, byte ptr [edi+0Ch]
		push 24h
		jne L08_662F40
		__emit 0E8h
		__emit 00Fh
		__emit 0F0h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		test eax, eax
		mov dword ptr [esp+18h], 0h
		je L09_662F64
		mov edx, dword ptr [edi]
		push edx
		mov ecx, eax
		__emit 0E8h
		__emit 0CAh
		__emit 054h
		__emit 09Bh
		__emit 0FFh   // call 0x18408
		jmp L10_662F66
L08_662F40:
		__emit 0E8h
		__emit 0EBh
		__emit 0EFh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		test eax, eax
		mov dword ptr [esp+18h], 1h
		je L09_662F64
		mov ecx, dword ptr [edi]
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 0B1h
		__emit 0E2h
		__emit 09Dh
		__emit 0FFh   // call 0x41213
		jmp L10_662F66
L09_662F64:
		xor eax, eax
L10_662F66:
		mov dword ptr [esp+18h], ebp
		mov ebp, eax
		mov eax, dword ptr [esi+12028h]
		push ebx
		mov dword ptr [ebp+0Ch], eax
		__emit 0E8h
		__emit 0D9h
		__emit 0C1h
		__emit 09Bh
		__emit 0FFh   // call 0x1F154
		add esp, 4h
		test al, al
		je L11_662FA8
		mov eax, dword ptr [ebx+0Ch]
		cmp eax, 8h
		jae L12_663048
		mov ecx, dword ptr [esi+eax*4+4h]
		test ecx, ecx
		je L12_663048
		xor edx, edx
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		push edx
		jmp L13_66303E
L11_662FA8:
		mov edi, dword ptr [esp+24h]
		xor dl, dl
		mov edi, edi
L16_662FB0:
		movzx eax, dl
		mov eax, dword ptr [esi+eax*4+4h]
		test eax, eax
		je L14_662FCF
		test edi, edi
		je L14_662FCF
		mov ecx, dword ptr [eax+0Ch]
		cmp ecx, dword ptr [edi]
		mov eax, dword ptr [eax+10h]
		jne L14_662FCF
		cmp ax, word ptr [edi+4h]
		je L15_662FF4
L14_662FCF:
		inc dl
		cmp dl, 8h
		jb L16_662FB0
		mov ecx, dword ptr [esi+1202Ch]
		cmp ecx, 8h
		jae L12_663048
		mov eax, dword ptr [esi+ecx*4+4h]
		test eax, eax
		je L17_66301D
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, eax
		push edx
		jmp L18_663042
L15_662FF4:
		movzx ecx, dl
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, dword ptr [esi+ecx*4+4h]
		push edx
		push ebp
		__emit 0E8h
		__emit 034h
		__emit 03Dh
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
		mov ecx, dword ptr [esp+10h]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0Ch
		ret 8h
L17_66301D:
		cmp dword ptr [esi+12028h], ecx
		jne L12_663048
		mov eax, dword ptr [ebx+0Ch]
		cmp eax, 8h
		jae L12_663048
		mov ecx, dword ptr [esi+eax*4+4h]
		test ecx, ecx
		je L12_663048
		mov ecx, eax
		xor eax, eax
		mov al, 1h
		shl al, cl
		push eax
L13_66303E:
		mov ecx, dword ptr [esi+ecx*4+4h]
L18_663042:
		push ebp
		__emit 0E8h
		__emit 0F4h
		__emit 03Ch
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L12_663048:
		mov ecx, ebp
		__emit 0E8h
		__emit 055h
		__emit 0D0h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 0Ch
		ret 8h
	}
}

// Populates the per-player state from the lobby's GameInfo: for each slot it
// checks GameSlot::isHuman, copies the name out with GameSlot::getName, fills
// the id array at this+0x12030, and constructs that slot's FrameDataManager
// (0x00670410) into this+0x120E4.
__declspec(naked) void BFMEConnectionManager::attachPlayersFromGameInfo(void *gameInfo)
{
	__asm {
		push 0FFFFFFFFh
		mov eax, dword ptr fs:[0h]
		push 1044339h
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 20h
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp+3Ch]
		test esi, esi
		push edi
		mov ebx, ecx
		je L00_666850
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+14h]
		xor ecx, ecx
		mov cx, ax
		mov dword ptr [ebx+12028h], eax
		push ecx
		__emit 0E8h
		__emit 092h
		__emit 0B8h
		__emit 09Ch
		__emit 0FFh   // call 0x31EE4
		add esp, 4h
		xor ebp, ebp
		lea edx,  [ebx+12030h]
		mov dword ptr [esp+14h], ebp
		mov dword ptr [esp+10h], edx
		lea edi,  [ebx+120E4h]
		jmp L01_666671
L12_66666D:
		mov esi, dword ptr [esp+40h]
L01_666671:
		push ebp
		mov ecx, esi
		__emit 0E8h
		__emit 0E7h
		__emit 02Dh
		__emit 09Ch
		__emit 0FFh   // call 0x29460
		mov esi, eax
		test esi, esi
		je L02_66683F
		mov ecx, esi
		__emit 0E8h
		__emit 041h
		__emit 013h
		__emit 09Ch
		__emit 0FFh   // call 0x279CB
		test al, al
		je L02_66683F
		cmp ebp, dword ptr [ebx+12028h]
		jne L03_666701
		lea eax,  [esp+18h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 065h
		__emit 03Bh
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		lea ecx,  [ebx+12058h]
		push eax
		mov dword ptr [esp+3Ch], 0h
		__emit 0E8h
		__emit 076h
		__emit 01Eh
		__emit 022h
		__emit 000h   // call 0x888530
		or esi, 0FFFFFFFFh
		lea ecx,  [esp+18h]
		mov dword ptr [esp+38h], esi
		__emit 0E8h
		__emit 006h
		__emit 01Bh
		__emit 022h
		__emit 000h   // call 0x8881D0
		push 10h
		__emit 0E8h
		__emit 05Fh
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+14h], eax
		test eax, eax
		mov dword ptr [esp+38h], 1h
		je L04_6666F6
		push 1h
		mov ecx, eax
		__emit 0E8h
		__emit 039h
		__emit 0E5h
		__emit 09Bh
		__emit 0FFh   // call 0x24C26
		mov dword ptr [esp+38h], esi
		jmp L05_666822
L04_6666F6:
		xor eax, eax
		mov dword ptr [esp+38h], esi
		jmp L05_666822
L03_666701:
		push 358h
		__emit 0E8h
		__emit 025h
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+24h], eax
		test eax, eax
		mov dword ptr [esp+38h], 2h
		je L06_666727
		mov ecx, eax
		__emit 0E8h
		__emit 0A7h
		__emit 0CAh
		__emit 09Ch
		__emit 0FFh   // call 0x331CC
		jmp L07_666729
L06_666727:
		xor eax, eax
L07_666729:
		lea ecx,  [esp+1Ch]
		push ecx
		or ebp, 0FFFFFFFFh
		mov ecx, esi
		mov dword ptr [esp+3Ch], ebp
		mov dword ptr [edi-120E0h], eax
		__emit 0E8h
		__emit 0C9h
		__emit 03Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		mov edx, dword ptr [ebx+12024h]
		mov ecx, dword ptr [edi-120E0h]
		push edx
		push eax
		lea eax,  [esi+30h]
		push eax
		mov dword ptr [esp+44h], 3h
		__emit 0E8h
		__emit 03Ah
		__emit 0E7h
		__emit 09Ch
		__emit 0FFh   // call 0x34E9B
		lea ecx,  [esp+1Ch]
		mov dword ptr [esp+38h], ebp
		__emit 0E8h
		__emit 062h
		__emit 01Ah
		__emit 022h
		__emit 000h   // call 0x8881D0
		__emit 0A0h
		__emit 0E9h
		__emit 0D4h
		__emit 02Eh
		__emit 001h   // mov al, byte ptr [0x12ed4e9]
		test al, al
		je L08_6667F3
		mov ecx, dword ptr [ebx+12024h]
		push ecx
		lea edx,  [esp+24h]
		push edx
		mov ecx, esi
		__emit 0E8h
		__emit 081h
		__emit 03Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		push eax
		__emit 0A1h
		__emit 0F0h
		__emit 0D4h
		__emit 02Eh
		__emit 001h   // mov eax, dword ptr [0x12ed4f0]
		test eax, eax
		mov dword ptr [esp+40h], 4h
		lea ebp,  [eax+8h]
		jne L09_6667A4
		mov ebp, 107388Bh
L09_6667A4:
		push ecx
		mov dword ptr [esp+30h], esp
		mov ecx, esp
		push 12ED4ECh
		__emit 0E8h
		__emit 0ABh
		__emit 013h
		__emit 022h
		__emit 000h   // call 0x887B60
		__emit 0E8h
		__emit 04Eh
		__emit 074h
		__emit 09Dh
		__emit 0FFh   // call 0x3DC08
		push ebp
		mov esi, eax
		__emit 0FFh
		__emit 015h
		__emit 084h
		__emit 093h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359384]
		mov ecx, dword ptr [edi-120E0h]
		mov word ptr [esp+3Ch], ax
		add esp, 8h
		lea eax,  [esp+30h]
		push eax
		mov dword ptr [esp+34h], esi
		__emit 0E8h
		__emit 0BCh
		__emit 0E6h
		__emit 09Ch
		__emit 0FFh   // call 0x34E9B
		lea ecx,  [esp+20h]
		mov dword ptr [esp+38h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0E0h
		__emit 019h
		__emit 022h
		__emit 000h   // call 0x8881D0
		or ebp, 0FFFFFFFFh
L08_6667F3:
		push 10h
		__emit 0E8h
		__emit 036h
		__emit 0B7h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+24h], eax
		test eax, eax
		mov dword ptr [esp+38h], 5h
		je L10_666818
		push 0h
		mov ecx, eax
		__emit 0E8h
		__emit 010h
		__emit 0E4h
		__emit 09Bh
		__emit 0FFh   // call 0x24C26
		jmp L11_66681A
L10_666818:
		xor eax, eax
L11_66681A:
		mov dword ptr [esp+38h], ebp
		mov ebp, dword ptr [esp+14h]
L05_666822:
		mov ecx, eax
		mov dword ptr [edi], eax
		__emit 0E8h
		__emit 0B7h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x212E2
		mov ecx, dword ptr [edi]
		__emit 0E8h
		__emit 014h
		__emit 07Dh
		__emit 09Ch
		__emit 0FFh   // call 0x2E546
		mov eax, dword ptr [esp+10h]
		mov dword ptr [eax], ebp
		add eax, 4h
		mov dword ptr [esp+10h], eax
L02_66683F:
		inc ebp
		add edi, 4h
		cmp ebp, 8h
		mov dword ptr [esp+14h], ebp
		jl L12_66666D
L00_666850:
		mov ecx, dword ptr [esp+30h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 2Ch
		ret 4h
	}
}

// Turns a player name into a Player. It formats the name into a UnicodeString,
// puts it through NameKeyGenerator::nameToKey, and looks the result up with
// PlayerList::findPlayerWithNameKey.
__declspec(naked) void BFMEConnectionManager::resolvePlayerFromName(void *msg)
{
	__asm {
		push 0FFFFFFFFh
		push 1044420h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 1Ch
		push ebx
		push ebp
		push esi
		xor ebx, ebx
		push edi
		mov ebp, ecx
		mov dword ptr [esp+10h], ebx
		mov esi, dword ptr [esp+3Ch]
		lea eax,  [esp+18h]
		push eax
		mov ecx, esi
		mov dword ptr [esp+38h], ebx
		__emit 0E8h
		__emit 0A0h
		__emit 0E2h
		__emit 09Bh
		__emit 0FFh   // call 0x25338
		mov eax, dword ptr [eax]
		cmp eax, ebx
		mov byte ptr [esp+34h], 1h
		je L00_6670A8
		add eax, 8h
		jmp L01_6670AD
L00_6670A8:
		mov eax, 107388Ch
L01_6670AD:
		push eax
		mov eax, dword ptr [esi+0Ch]
		push eax
		lea ecx,  [esp+44h]
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 0A4h
		__emit 0B9h
		__emit 09Ah
		__emit 0FFh   // call 0x12A62
		mov eax, dword ptr [eax]
		cmp eax, ebx
		mov byte ptr [esp+38h], 2h
		je L02_6670CE
		add eax, 8h
		jmp L03_6670D3
L02_6670CE:
		mov eax, 107388Ch
L03_6670D3:
		push eax
		push ecx
		mov dword ptr [esp+28h], esp
		mov ecx, esp
		push 1117AECh
		__emit 0E8h
		__emit 0FBh
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x888DE0
		lea edx,  [esp+1Ch]
		push edx
		__emit 0E8h
		__emit 0A1h
		__emit 020h
		__emit 022h
		__emit 000h   // call 0x889190
		add esp, 10h
		lea ecx,  [esp+3Ch]
		mov byte ptr [esp+34h], 1h
		__emit 0E8h
		__emit 0D0h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x8881D0
		lea ecx,  [esp+18h]
		mov byte ptr [esp+34h], 0h
		__emit 0E8h
		__emit 0C2h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esi+0Ch]
		cmp eax, 8h
		jae L04_66726B
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push eax
		__emit 0E8h
		__emit 0F2h
		__emit 07Ah
		__emit 09Bh
		__emit 0FFh   // call 0x1EC18
		add eax, 2Ch
		push eax
		lea ecx,  [esp+18h]
		__emit 0E8h
		__emit 02Dh
		__emit 00Ah
		__emit 022h
		__emit 000h   // call 0x887B60
		mov eax, dword ptr [esp+14h]
		cmp eax, ebx
		mov byte ptr [esp+34h], 3h
		je L05_667145
		add eax, 8h
		jmp L06_66714A
L05_667145:
		mov eax, 107388Bh
L06_66714A:
		__emit 08Bh
		__emit 00Dh
		__emit 000h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed600]
		push eax
		__emit 0E8h
		__emit 081h
		__emit 03Ch
		__emit 09Dh
		__emit 0FFh   // call 0x3ADD7
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0D7h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed748]
		push eax
		__emit 0E8h
		__emit 024h
		__emit 084h
		__emit 09Ch
		__emit 0FFh   // call 0x2F586
		mov edi, eax
		cmp edi, ebx
		jne L07_6671C6
		__emit 08Bh
		__emit 00Dh
		__emit 068h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed668]
		cmp ecx, ebx
		je L08_66718F
		mov eax, dword ptr [ecx]
		call dword ptr [eax+124h]
		cmp eax, ebx
		je L08_66718F
		__emit 08Bh
		__emit 00Dh
		__emit 068h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed668]
		mov edx, dword ptr [ecx]
		add eax, 0C40h
		push eax
		call dword ptr [edx+44h]
L08_66718F:
		mov eax, dword ptr [esp+10h]
		cmp eax, ebx
		je L09_66719C
		add eax, 8h
		jmp L10_6671A1
L09_66719C:
		mov eax, 107388Ch
L10_6671A1:
		push eax
		push ecx
		mov dword ptr [esp+44h], esp
		mov ecx, esp
		push 10FF4BCh
		__emit 0E8h
		__emit 02Dh
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		push eax
		call dword ptr [ecx+40h]
		add esp, 0Ch
		jmp L11_66725D
L07_6671C6:
		mov ecx, edi
		__emit 0E8h
		__emit 0F0h
		__emit 007h
		__emit 09Bh
		__emit 0FFh   // call 0x179BD
		neg al
		sbb al, al
		inc al
		mov byte ptr [esp+3Ch], al
		jne L12_6671F3
		mov eax, dword ptr [esi+0Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push eax
		__emit 0E8h
		__emit 078h
		__emit 022h
		__emit 09Ch
		__emit 0FFh   // call 0x29460
		mov cl, byte ptr [eax+0Ah]
		test cl, cl
		jne L12_6671F3
		mov bl, 1h
		jmp L13_6671F5
L12_6671F3:
		xor bl, bl
L13_6671F5:
		mov ecx, esi
		__emit 0E8h
		__emit 020h
		__emit 0B9h
		__emit 099h
		__emit 0FFh   // call 0x2B1C
		mov ecx, dword ptr [ebp+12028h]
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0C2h   // test edx, eax
		je L11_66725D
		test bl, bl
		je L11_66725D
		__emit 0E8h
		__emit 0CAh
		__emit 0BAh
		__emit 0FFh
		__emit 0FFh   // call 0x662CE0
		mov eax, dword ptr [edi+1C4h]
		push eax
		lea ecx,  [esp+24h]
		__emit 0E8h
		__emit 0A1h
		__emit 05Bh
		__emit 09Ch
		__emit 0FFh   // call 0x2CDC7
		mov eax, dword ptr [esp+10h]
		test eax, eax
		je L14_667233
		add eax, 8h
		jmp L15_667238
L14_667233:
		mov eax, 107388Ch
L15_667238:
		push eax
		push ecx
		mov dword ptr [esp+44h], esp
		mov ecx, esp
		push 10FF4BCh
		__emit 0E8h
		__emit 096h
		__emit 01Bh
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		lea edx,  [esp+28h]
		push edx
		push eax
		call dword ptr [ecx+38h]
		add esp, 10h
L11_66725D:
		lea ecx,  [esp+14h]
		mov byte ptr [esp+34h], 0h
		__emit 0E8h
		__emit 0D5h
		__emit 006h
		__emit 022h
		__emit 000h   // call 0x887940
L04_66726B:
		lea ecx,  [esp+10h]
		mov dword ptr [esp+34h], 0FFFFFFFFh
		__emit 0E8h
		__emit 054h
		__emit 00Fh
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+2Ch]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 28h
		ret 4h
	}
}

// Opens a file through TheFileSystem and pushes it out as wrapped commands,
// registering the transfer in the map at this+0x12130 and stamping each message
// with a fresh command id from 0x00682D10.
__declspec(naked) void BFMEConnectionManager::sendFileToPlayers(const char *path)
{
	__asm {
		push 0FFFFFFFFh
		push 104467Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp+20h]
		push edi
		lea eax,  [esp+24h]
		mov ebx, ecx
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0C3h
		__emit 001h
		__emit 09Bh
		__emit 0FFh   // call 0x1A00F
		mov eax, dword ptr [eax]
		test eax, eax
		mov dword ptr [esp+1Ch], 0h
		je L00_669E5F
		add eax, 8h
		jmp L01_669E64
L00_669E5F:
		mov eax, 107388Bh
L01_669E64:
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0CBh
		__emit 034h
		__emit 001h   // mov ecx, dword ptr [0x134cb48]
		push eax
		__emit 0E8h
		__emit 030h
		__emit 0E8h
		__emit 035h
		__emit 000h   // call 0x9C86A0
		lea ecx,  [esp+24h]
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 0BFh
		__emit 0DAh
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, esi
		__emit 0E8h
		__emit 010h
		__emit 017h
		__emit 09Dh
		__emit 0FFh   // call 0x3B598
		mov ecx, esi
		mov ebp, eax
		__emit 0E8h
		__emit 02Ch
		__emit 049h
		__emit 09Bh
		__emit 0FFh   // call 0x1E7BD
		lea ecx,  [esp+24h]
		push ecx
		mov ecx, esi
		mov dword ptr [esp+14h], eax
		__emit 0E8h
		__emit 06Eh
		__emit 001h
		__emit 09Bh
		__emit 0FFh   // call 0x1A00F
		mov eax, dword ptr [eax]
		test eax, eax
		mov dword ptr [esp+1Ch], 1h
		je L02_669EB4
		add eax, 8h
		jmp L03_669EB9
L02_669EB4:
		mov eax, 107388Bh
L03_669EB9:
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0CBh
		__emit 034h
		__emit 001h   // mov ecx, dword ptr [0x134cb48]
		push 4Ah
		push eax
		__emit 0E8h
		__emit 099h
		__emit 0E9h
		__emit 035h
		__emit 000h   // call 0x9C8860
		lea ecx,  [esp+24h]
		mov edi, eax
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 066h
		__emit 0DAh
		__emit 021h
		__emit 000h   // call 0x887940
		test edi, edi
		je L04_669EF2
		mov eax, dword ptr [esp+10h]
		mov edx, dword ptr [edi]
		push eax
		push ebp
		mov ecx, edi
		call dword ptr [edx+10h]
		mov edx, dword ptr [edi]
		mov ecx, edi
		call dword ptr [edx+8h]
L04_669EF2:
		movzx ebp, word ptr [esi+10h]
		lea eax,  [esp+24h]
		push eax
		mov eax, dword ptr [ebx+12028h]
		__emit 08Dh
		__emit 00Ch
		__emit 040h   // lea ecx, [eax + eax*2]
		lea ecx,  [ebx+ecx*4+12130h]
		mov dword ptr [esp+28h], ebp
		__emit 0E8h
		__emit 0DDh
		__emit 063h
		__emit 09Ch
		__emit 0FFh   // call 0x302F1
		mov dword ptr [eax], 64h
		mov ecx, dword ptr [ebx+12028h]
		mov edi, 1h
		shl edi, cl
		push 24h
		xor edi, 0FFh
		__emit 0E8h
		__emit 0FCh
		__emit 07Fh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+24h], eax
		test eax, eax
		mov dword ptr [esp+1Ch], 2h
		je L05_669F52
		mov ecx, eax
		__emit 0E8h
		__emit 08Ch
		__emit 06Ah
		__emit 09Dh
		__emit 0FFh   // call 0x409DA
		mov esi, eax
		jmp L06_669F54
L05_669F52:
		xor esi, esi
L06_669F54:
		mov edx, dword ptr [ebx+12028h]
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov dword ptr [esi+0Ch], edx
		mov word ptr [esi+10h], 0h
		__emit 0E8h
		__emit 0FEh
		__emit 0BBh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L07_669F84
		__emit 0E8h
		__emit 0D8h
		__emit 065h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L07_669F84:
		push ebp
		mov ecx, esi
		__emit 0E8h
		__emit 062h
		__emit 0A8h
		__emit 09Bh
		__emit 0FFh   // call 0x247EE
		push 64h
		mov ecx, esi
		__emit 0E8h
		__emit 021h
		__emit 0B4h
		__emit 09Ah
		__emit 0FFh   // call 0x153B6
		push edi
		push esi
		mov ecx, ebx
		__emit 0E8h
		__emit 0DCh
		__emit 051h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		push esi
		mov ecx, ebx
		__emit 0E8h
		__emit 0CDh
		__emit 063h
		__emit 09Ch
		__emit 0FFh   // call 0x30373
		mov ecx, esi
		__emit 0E8h
		__emit 0F7h
		__emit 060h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+14h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Announces a file transfer to the other players: opens the file to size it,
// builds the announcement command, and sends it with sendLocalCommand.
__declspec(naked) void BFMEConnectionManager::sendFileAnnouncement(const char *path, int playerMask)
{
	__asm {
		push 0FFFFFFFFh
		push 10446D3h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push ebx
		push ebp
		push esi
		push edi
		mov ebp, ecx
		mov eax, dword ptr [esp+30h]
		xor ebx, ebx
		cmp eax, ebx
		mov dword ptr [esp+28h], ebx
		je L00_66A1A1
		add eax, 8h
		jmp L01_66A1A6
L00_66A1A1:
		mov eax, 107388Bh
L01_66A1A6:
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0CBh
		__emit 034h
		__emit 001h   // mov ecx, dword ptr [0x134cb48]
		push ebx
		push eax
		__emit 0E8h
		__emit 0ADh
		__emit 0E6h
		__emit 035h
		__emit 000h   // call 0x9C8860
		mov esi, eax
		cmp esi, ebx
		je L02_66A2A4
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+2Ch]
		test eax, eax
		je L02_66A2A4
		mov edx, dword ptr [esi]
		mov ecx, esi
		call dword ptr [edx+8h]
		mov ecx, dword ptr [ebp+12028h]
		mov edi, 1h
		shl edi, cl
		push 24h
		xor edi, 0FFh
		__emit 0E8h
		__emit 043h
		__emit 07Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebx
		mov byte ptr [esp+28h], 3h
		je L03_66A208
		mov ecx, eax
		__emit 0E8h
		__emit 00Dh
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x45F11
		mov esi, eax
		jmp L04_66A20A
L03_66A208:
		xor esi, esi
L04_66A20A:
		mov eax, dword ptr [ebp+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov byte ptr [esp+2Ch], bl
		__emit 0E8h
		__emit 052h
		__emit 0B9h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		cmp al, 1h
		jne L05_66A230
		__emit 0E8h
		__emit 02Ch
		__emit 063h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L05_66A230:
		push ecx
		lea eax,  [esp+34h]
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 01Fh
		__emit 0D9h
		__emit 021h
		__emit 000h   // call 0x887B60
		mov ecx, esi
		__emit 0E8h
		__emit 0E8h
		__emit 04Ah
		__emit 09Bh
		__emit 0FFh   // call 0x1ED30
		mov ecx, dword ptr [esp+34h]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 095h
		__emit 071h
		__emit 09Dh
		__emit 0FFh   // call 0x413E9
		__emit 0E8h
		__emit 0FFh
		__emit 062h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov ecx, esi
		mov ebx, eax
		push ebx
		__emit 0E8h
		__emit 020h
		__emit 072h
		__emit 099h
		__emit 0FFh   // call 0x1483
		push esi
		mov ecx, ebp
		__emit 0E8h
		__emit 089h
		__emit 0E7h
		__emit 099h
		__emit 0FFh   // call 0x89F4
		push edi
		push esi
		mov ecx, ebp
		__emit 0E8h
		__emit 006h
		__emit 04Fh
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 029h
		__emit 05Eh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		lea ecx,  [esp+30h]
		mov dword ptr [esp+28h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0B4h
		__emit 0D6h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ax, bx
		mov ecx, dword ptr [esp+20h]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 1Ch
		ret 8h
L02_66A2A4:
		mov dword ptr [esp+10h], ebx
		movzx edx, byte ptr [esp+34h]
		mov eax, dword ptr [esp+30h]
		cmp eax, ebx
		mov byte ptr [esp+28h], 1h
		push edx
		je L06_66A2C0
		add eax, 8h
		jmp L07_66A2C5
L06_66A2C0:
		mov eax, 107388Bh
L07_66A2C5:
		push eax
		push ecx
		mov dword ptr [esp+40h], esp
		mov ecx, esp
		push 111A268h
		__emit 0E8h
		__emit 009h
		__emit 0EBh
		__emit 021h
		__emit 000h   // call 0x888DE0
		lea eax,  [esp+1Ch]
		push eax
		__emit 0E8h
		__emit 0AFh
		__emit 0EEh
		__emit 021h
		__emit 000h   // call 0x889190
		__emit 0A1h
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7730]
		add esp, 10h
		cmp eax, ebx
		je L08_66A337
		push 2h
		push ecx
		lea edx,  [esp+18h]
		mov dword ptr [esp+3Ch], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 000h
		__emit 0E1h
		__emit 021h
		__emit 000h   // call 0x888400
		lea eax,  [esp+20h]
		push eax
		push ecx
		mov dword ptr [esp+24h], esp
		mov ecx, esp
		push 111A250h
		mov byte ptr [esp+3Ch], 2h
		mov dword ptr [esp+2Ch], ebx
		mov word ptr [esp+30h], bx
		__emit 0E8h
		__emit 0BCh
		__emit 0EAh
		__emit 021h
		__emit 000h   // call 0x888DE0
		__emit 08Bh
		__emit 00Dh
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7730]
		mov edx, dword ptr [ecx]
		mov byte ptr [esp+38h], 1h
		call dword ptr [edx+8Ch]
L08_66A337:
		lea ecx,  [esp+10h]
		mov byte ptr [esp+28h], bl
		__emit 0E8h
		__emit 08Ch
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x8881D0
		lea ecx,  [esp+30h]
		mov dword ptr [esp+28h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0EBh
		__emit 0D5h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+20h]
		pop edi
		pop esi
		pop ebp
		xor ax, ax
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 1Ch
		ret 8h
	}
}

// Retail's name -- the ZH reference declares it with this signature. Returns
// m_packetRouterSlot at this+0x1202C.
__declspec(naked) unsigned int ConnectionManager::getPacketRouterSlot()
{
	__asm {
		mov eax, dword ptr [ecx+1202Ch]
		ret
	}
}

// Retail's name, and the callee DisconnectManager::isPlayerVotedOut wants.
// Counts the connected slots exactly as the reference does, except that BFME
// inlines isPlayerConnected: a slot counts when it is our own or its Connection
// pointer at this+0x04 is set.
__declspec(naked) int ConnectionManager::getNumPlayers()
{
	__asm {
		push ebx
		push esi
		push edi
		mov edi, dword ptr [ecx+12028h]
		mov esi, 2h
		xor eax, eax
		add ecx, 8h
		mov ebx, esi
L08_663785:
		lea edx,  [esi-2h]
		cmp edx, edi
		je L00_663798
		mov edx, dword ptr [ecx-4h]
		test edx, edx
		je L01_663799
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L01_663799
L00_663798:
		inc eax
L01_663799:
		lea edx,  [esi-1h]
		cmp edx, edi
		je L02_6637AB
		mov edx, dword ptr [ecx]
		test edx, edx
		je L03_6637AC
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L03_6637AC
L02_6637AB:
		inc eax
L03_6637AC:
		cmp esi, edi
		je L04_6637BC
		mov edx, dword ptr [ecx+4h]
		test edx, edx
		je L05_6637BD
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L05_6637BD
L04_6637BC:
		inc eax
L05_6637BD:
		lea edx,  [esi+1h]
		cmp edx, edi
		je L06_6637D0
		mov edx, dword ptr [ecx+8h]
		test edx, edx
		je L07_6637D1
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L07_6637D1
L06_6637D0:
		inc eax
L07_6637D1:
		add ecx, 10h
		add esi, 4h
		dec ebx
		jne L08_663785
		pop edi
		pop esi
		pop ebx
		ret
	}
}

// Sends command type 12 (KEEPALIVE), built by the constructor at 0x00673B80. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendKeepAliveCommand()
{
	__asm {
		push 0FFFFFFFFh
		push 104400Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 8h
		push ebx
		push ebp
		push esi
		push edi
		mov ebx, ecx
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esp+10h], eax
		xor edi, edi
		lea ebp,  [ebx+4h]
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L03_663610:
		mov eax, dword ptr [ebp]
		xor esi, esi
		cmp eax, esi
		je L00_66368E
		mov eax, dword ptr [eax+348h]
		mov ecx, dword ptr [esp+10h]
		sub ecx, eax
		cmp ecx, 3E8h
		jbe L00_66368E
		push 1Ch
		__emit 0E8h
		__emit 0FCh
		__emit 0E8h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+14h], eax
		cmp eax, esi
		mov dword ptr [esp+20h], esi
		je L01_66364C
		mov ecx, eax
		__emit 0E8h
		__emit 03Dh
		__emit 019h
		__emit 09Ch
		__emit 0FFh   // call 0x24F87
		mov esi, eax
L01_66364C:
		mov eax, dword ptr [esi+14h]
		mov edx, dword ptr [ebx+12028h]
		push eax
		mov dword ptr [esp+24h], 0FFFFFFFFh
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 00Ch
		__emit 025h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		cmp al, 1h
		jne L02_663676
		__emit 0E8h
		__emit 0E6h
		__emit 0CEh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_663676:
		xor eax, eax
		mov al, 1h
		mov ecx, edi
		shl al, cl
		mov ecx, ebx
		push eax
		push esi
		__emit 0E8h
		__emit 050h
		__emit 0DBh
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 016h
		__emit 0CAh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L00_66368E:
		inc edi
		add ebp, 4h
		cmp edi, 8h
		jl L03_663610
		mov ecx, dword ptr [esp+18h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret
	}
}

// Sends command type 15 (PROGRESS), built by 0x00673D60 -- it is the only caller of
// NetProgressCommandMsg::setPercentage here. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendProgressCommand(int percent)
{
	__asm {
		push 0FFFFFFFFh
		push 104402Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push esi
		push edi
		push 20h
		mov edi, ecx
		__emit 0E8h
		__emit 00Eh
		__emit 0E7h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+0Ch], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+18h], esi
		je L00_66383C
		mov ecx, eax
		__emit 0E8h
		__emit 072h
		__emit 02Eh
		__emit 09Ch
		__emit 0FFh   // call 0x266AC
		mov esi, eax
L00_66383C:
		mov eax, dword ptr [esp+20h]
		push eax
		mov ecx, esi
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 006h
		__emit 0D4h
		__emit 09Ch
		__emit 0FFh   // call 0x30C56
		mov eax, dword ptr [esi+14h]
		mov ecx, dword ptr [edi+12028h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 010h
		__emit 023h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		cmp al, 1h
		jne L01_663872
		__emit 0E8h
		__emit 0EAh
		__emit 0CCh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L01_663872:
		mov ebx, dword ptr [esi+0Ch]
		mov ecx, esi
		__emit 0E8h
		__emit 027h
		__emit 01Fh
		__emit 09Bh
		__emit 0FFh   // call 0x157A3
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		movzx edx, al
		push edx
		push ebx
		__emit 0E8h
		__emit 0E1h
		__emit 0ADh
		__emit 09Ch
		__emit 0FFh   // call 0x2E66D
		mov ecx, dword ptr [edi+12028h]
		xor eax, eax
		mov al, 1h
		shl al, cl
		mov ecx, edi
		not al
		push eax
		push esi
		__emit 0E8h
		__emit 034h
		__emit 0D9h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 0FAh
		__emit 0C7h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Sends command type 27 (DISCONNECTFRAME), built by 0x006740C0. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendDisconnectFrameCommand()
{
	__asm {
		push 0FFFFFFFFh
		push 1044056h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		push ebx
		mov ebx, dword ptr [eax+3Ch]
		push esi
		push edi
		push 20h
		mov edi, ecx
		__emit 0E8h
		__emit 0F6h
		__emit 0E5h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+0Ch], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+18h], esi
		je L00_663954
		mov ecx, eax
		__emit 0E8h
		__emit 0E4h
		__emit 0BBh
		__emit 09Ch
		__emit 0FFh   // call 0x2F536
		mov esi, eax
L00_663954:
		mov eax, dword ptr [edi+12028h]
		push ebx
		mov ecx, esi
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 0A1h
		__emit 059h
		__emit 09Ah
		__emit 0FFh   // call 0x930E
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 0FCh
		__emit 021h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_663986
		__emit 0E8h
		__emit 0D6h
		__emit 0CBh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L01_663986:
		mov ecx, dword ptr [edi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 03Ah
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov eax, dword ptr [edi+120E0h]
		test eax, eax
		je L02_663A01
		push 14h
		__emit 0E8h
		__emit 082h
		__emit 0E5h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+0Ch], eax
		test eax, eax
		mov dword ptr [esp+18h], 1h
		je L03_6639CD
		push esi
		mov ecx, eax
		__emit 0E8h
		__emit 01Dh
		__emit 040h
		__emit 09Ah
		__emit 0FFh   // call 0x79E6
		mov ebx, eax
		jmp L04_6639CF
L03_6639CD:
		xor ebx, ebx
L04_6639CF:
		mov ecx, dword ptr [edi+12028h]
		mov al, 1h
		shl al, cl
		push edi
		push ebx
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov byte ptr [ebx+0Ch], al
		mov ecx, dword ptr [edi+120E0h]
		__emit 0E8h
		__emit 07Fh
		__emit 04Fh
		__emit 09Ch
		__emit 0FFh   // call 0x28970
		mov ecx, ebx
		__emit 0E8h
		__emit 068h
		__emit 04Fh
		__emit 09Dh
		__emit 0FFh   // call 0x38960
		push ebx
		__emit 0E8h
		__emit 0B2h
		__emit 0E4h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L02_663A01:
		mov ecx, esi
		__emit 0E8h
		__emit 09Ch
		__emit 0C6h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Sends command type 28 (DISCONNECTSCREENOFF), built by 0x00674310; it also calls
// DisconnectManager::turnOffScreen, which is the same pairing
// processDisconnectScreenOff has on the receiving side. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendDisconnectScreenOffCommand(int slot)
{
	__asm {
		push 0FFFFFFFFh
		push 1044086h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push esi
		mov esi, ecx
		mov eax, dword ptr [esi+12028h]
		mov ecx, dword ptr [esi+120E0h]
		push edi
		push eax
		__emit 0E8h
		__emit 043h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x44AD0
		push 20h
		__emit 0E8h
		__emit 09Ch
		__emit 0E4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+0Ch], eax
		xor ebx, ebx
		cmp eax, ebx
		mov dword ptr [esp+18h], ebx
		je L00_663AB0
		mov ecx, eax
		__emit 0E8h
		__emit 024h
		__emit 0BEh
		__emit 09Ah
		__emit 0FFh   // call 0xF8D0
		mov edi, eax
		jmp L01_663AB2
L00_663AB0:
		xor edi, edi
L01_663AB2:
		mov eax, dword ptr [esi+12028h]
		mov dword ptr [edi+0Ch], eax
		mov eax, dword ptr [esp+20h]
		push eax
		mov ecx, edi
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 036h
		__emit 05Ah
		__emit 09Ch
		__emit 0FFh   // call 0x29505
		mov eax, dword ptr [edi+14h]
		push eax
		__emit 0E8h
		__emit 09Ah
		__emit 020h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_663AE8
		__emit 0E8h
		__emit 074h
		__emit 0CAh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [edi+10h], ax
L02_663AE8:
		mov ecx, dword ptr [esi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, esi
		not dl
		push edx
		push edi
		__emit 0E8h
		__emit 0D8h
		__emit 0D6h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		cmp dword ptr [esi+120E0h], ebx
		je L03_663B5D
		push 14h
		__emit 0E8h
		__emit 022h
		__emit 0E4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		cmp eax, ebx
		mov dword ptr [esp+18h], 1h
		je L04_663B2B
		push edi
		mov ecx, eax
		__emit 0E8h
		__emit 0BDh
		__emit 03Eh
		__emit 09Ah
		__emit 0FFh   // call 0x79E6
		mov ebx, eax
L04_663B2B:
		mov ecx, dword ptr [esi+12028h]
		mov al, 1h
		shl al, cl
		push esi
		push ebx
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov byte ptr [ebx+0Ch], al
		mov ecx, dword ptr [esi+120E0h]
		__emit 0E8h
		__emit 023h
		__emit 04Eh
		__emit 09Ch
		__emit 0FFh   // call 0x28970
		mov ecx, ebx
		__emit 0E8h
		__emit 00Ch
		__emit 04Eh
		__emit 09Dh
		__emit 0FFh   // call 0x38960
		push ebx
		__emit 0E8h
		__emit 056h
		__emit 0E3h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L03_663B5D:
		mov ecx, edi
		__emit 0E8h
		__emit 040h
		__emit 0C5h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Sends command type 7 (REQUESTPLAYERLEAVE), built by the already-matched
// BFMENetRequestPlayerLeaveCommandMsg::construct. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendRequestPlayerLeaveCommand()
{
	__asm {
		push 0FFFFFFFFh
		push 104410Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 20h
		mov edi, ecx
		__emit 0E8h
		__emit 06Fh
		__emit 0D6h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		test eax, eax
		mov dword ptr [esp+14h], 0h
		je L00_6648DF
		mov ecx, eax
		__emit 0E8h
		__emit 0F3h
		__emit 04Ch
		__emit 09Bh
		__emit 0FFh   // call 0x195CE
		mov esi, eax
		jmp L01_6648E1
L00_6648DF:
		xor esi, esi
L01_6648E1:
		mov eax, dword ptr [edi+12028h]
		push eax
		mov ecx, esi
		mov dword ptr [esp+18h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0E2h
		__emit 0BDh
		__emit 09Ch
		__emit 0FFh   // call 0x306D9
		mov eax, dword ptr [esi+14h]
		mov ecx, dword ptr [edi+12028h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 069h
		__emit 012h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_664919
		__emit 0E8h
		__emit 043h
		__emit 0BCh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_664919:
		xor edx, edx
		mov dword ptr [esi+8h], 0FFFFFFFFh
		mov ecx, dword ptr [edi+12028h]
		mov dl, 1h
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 0A0h
		__emit 0C8h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, edi
		__emit 0E8h
		__emit 0CEh
		__emit 0D9h
		__emit 09Dh
		__emit 0FFh   // call 0x4230C
		mov ecx, esi
		__emit 0E8h
		__emit 05Fh
		__emit 0B7h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov eax, dword ptr [edi+12110h]
		test eax, eax
		jne L03_66495B
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [edi+12110h], eax
L03_66495B:
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Sends command type 16 (LOADCOMPLETE). Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendLoadCompleteCommand()
{
	__asm {
		push 0FFFFFFFFh
		push 104412Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 1Ch
		mov edi, ecx
		__emit 0E8h
		__emit 0AFh
		__emit 0D4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+14h], esi
		je L00_664A9B
		mov ecx, eax
		__emit 0E8h
		__emit 01Bh
		__emit 0E8h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov esi, eax
L00_664A9B:
		mov dword ptr [esi+14h], 10h
		mov eax, dword ptr [edi+12028h]
		push 10h
		mov dword ptr [esp+18h], 0FFFFFFFFh
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 0B8h
		__emit 010h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_664ACA
		__emit 0E8h
		__emit 092h
		__emit 0BAh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L01_664ACA:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		__emit 0E8h
		__emit 02Ch
		__emit 0B9h
		__emit 09Bh
		__emit 0FFh   // call 0x20405
		mov ecx, dword ptr [edi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 08Ah
		__emit 0A6h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0ADh
		__emit 0B5h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Sends command type 10 (PLAYERLEAVE) and 11 (DESTROYPLAYER) -- it builds both. Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendPlayerLeaveCommands()
{
	__asm {
		push 0FFFFFFFFh
		push 104424Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 20h
		mov edi, ecx
		__emit 0E8h
		__emit 0FFh
		__emit 0C2h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+14h], esi
		je L00_665C4B
		mov ecx, eax
		__emit 0E8h
		__emit 044h
		__emit 0F0h
		__emit 09Dh
		__emit 0FFh   // call 0x44C8D
		mov esi, eax
L00_665C4B:
		xor eax, eax
		mov al, byte ptr [edi+12028h]
		mov ecx, esi
		mov dword ptr [esp+14h], 0FFFFFFFFh
		push eax
		__emit 0E8h
		__emit 0EAh
		__emit 067h
		__emit 09Dh
		__emit 0FFh   // call 0x3C44D
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0FFh
		__emit 0FEh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_665C83
		__emit 0E8h
		__emit 0D9h
		__emit 0A8h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L01_665C83:
		mov ecx, dword ptr [edi+12028h]
		push 0FFh
		mov dword ptr [esi+0Ch], ecx
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0E1h
		__emit 094h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 004h
		__emit 0A4h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov ecx, dword ptr [esp+0Ch]
		mov dword ptr [edi+12110h], eax
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Sends command type 3 (FRAMEINFO), the single-recipient counterpart to sendFrameInfo. Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendFrameInfoToPlayer(int slot)
{
	__asm {
		push 0FFFFFFFFh
		push 104428Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 28h
		mov edi, ecx
		__emit 0E8h
		__emit 03Fh
		__emit 0C0h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+8h], esi
		test esi, esi
		mov dword ptr [esp+14h], 0h
		je L00_665F31
		mov ecx, esi
		__emit 0E8h
		__emit 0A7h
		__emit 0D3h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], 0h
		mov dword ptr [esi+20h], 0h
		mov dword ptr [esi+24h], 0FFFFFFFFh
		mov dword ptr [esi+14h], 3h
		jmp L01_665F33
L00_665F31:
		xor esi, esi
L01_665F33:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		dec eax
		mov dword ptr [esi+1Ch], eax
		__emit 08Bh
		__emit 00Dh
		__emit 064h
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f1464]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+14h], 0FFFFFFFFh
		call dword ptr [edx+68h]
		mov dword ptr [esi+20h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 014h
		__emit 0FCh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_665F6E
		__emit 0E8h
		__emit 0EEh
		__emit 0A5h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_665F6E:
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+1202Ch]
		cmp eax, ecx
		jne L03_665F94
		xor edx, edx
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		not dl
		push edx
		jmp L04_665F9B
L03_665F94:
		xor eax, eax
		mov al, 1h
		shl al, cl
		push eax
L04_665F9B:
		mov ecx, edi
		push esi
		__emit 0E8h
		__emit 0D7h
		__emit 091h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0FAh
		__emit 0A0h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Sends command type 13 (DISCONNECTCHAT). Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendDisconnectChatCommand(void *text)
{
	__asm {
		push 0FFFFFFFFh
		push 1044373h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		mov edi, ecx
		push 20h
		mov dword ptr [esp+18h], 0h
		__emit 0E8h
		__emit 007h
		__emit 0B6h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		test eax, eax
		mov byte ptr [esp+14h], 1h
		je L00_666944
		mov ecx, eax
		__emit 0E8h
		__emit 00Ah
		__emit 0F5h
		__emit 09Ch
		__emit 0FFh   // call 0x35E4A
		mov esi, eax
		jmp L01_666946
L00_666944:
		xor esi, esi
L01_666946:
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov byte ptr [esp+18h], 0h
		__emit 0E8h
		__emit 015h
		__emit 0F2h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_66696D
		__emit 0E8h
		__emit 0EFh
		__emit 09Bh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_66696D:
		push ecx
		lea eax,  [esp+20h]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 082h
		__emit 01Ah
		__emit 022h
		__emit 000h   // call 0x888400
		mov ecx, esi
		__emit 0E8h
		__emit 019h
		__emit 05Ch
		__emit 09Bh
		__emit 0FFh   // call 0x1C59E
		mov ecx, dword ptr [edi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 03Bh
		__emit 0A8h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Eh
		__emit 002h
		__emit 09Ah
		__emit 0FFh   // call 0x6BC2
		mov ecx, esi
		__emit 0E8h
		__emit 0F9h
		__emit 096h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		lea ecx,  [esp+1Ch]
		mov dword ptr [esp+14h], 0FFFFFFFFh
		__emit 0E8h
		__emit 014h
		__emit 018h
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 10h
		ret 4h
	}
}

// Sends command type 26 (DISCONNECTVOTE), and 14 (CHAT) on the other arm. Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendDisconnectVoteCommand(int slot, unsigned int frame)
{
	__asm {
		push 0FFFFFFFFh
		push 1044473h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		mov edi, ecx
		push 24h
		mov dword ptr [esp+18h], 0h
		__emit 0E8h
		__emit 027h
		__emit 0A9h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		test eax, eax
		mov byte ptr [esp+14h], 1h
		je L00_667624
		mov ecx, eax
		__emit 0E8h
		__emit 0DFh
		__emit 06Eh
		__emit 09Dh
		__emit 0FFh   // call 0x3E4FF
		mov esi, eax
		jmp L01_667626
L00_667624:
		xor esi, esi
L01_667626:
		push ecx
		lea eax,  [esp+20h]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 0C4h
		__emit 00Dh
		__emit 022h
		__emit 000h   // call 0x888400
		mov ecx, esi
		__emit 0E8h
		__emit 00Eh
		__emit 09Bh
		__emit 09Ch
		__emit 0FFh   // call 0x31151
		mov ecx, dword ptr [esp+20h]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 0EFh
		__emit 0C2h
		__emit 09Bh
		__emit 0FFh   // call 0x2393E
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 011h
		__emit 0E5h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_667671
		__emit 0E8h
		__emit 0EBh
		__emit 08Eh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_667671:
		mov ecx, dword ptr [edi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 04Fh
		__emit 09Bh
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 077h
		__emit 0D3h
		__emit 099h
		__emit 0FFh   // call 0x4A07
		mov ecx, esi
		__emit 0E8h
		__emit 00Dh
		__emit 08Ah
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		lea ecx,  [esp+1Ch]
		mov dword ptr [esp+14h], 0FFFFFFFFh
		__emit 0E8h
		__emit 028h
		__emit 00Bh
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 10h
		ret 8h
	}
}

// Sends command type 6 (GAMESPY_STATS_AUTHKEY), built by 0x00675BE0. Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendGameSpyStatsAuthKey(void *key)
{
	__asm {
		push 0FFFFFFFFh
		mov eax, dword ptr fs:[0h]
		push 104422Eh
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 108h
		push ebx
		mov ebx, dword ptr [esp+11Ch]
		push ebp
		push esi
		push edi
		lea eax,  [esp+14h]
		mov ebp, ecx
		push eax
		mov ecx, ebx
		__emit 0E8h
		__emit 02Eh
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x204D2
		mov eax, dword ptr [eax]
		test eax, eax
		je L00_665AAF
		add eax, 8h
		jmp L01_665AB4
L00_665AAF:
		mov eax, 107388Bh
L01_665AB4:
		push eax
		__emit 0E8h
		__emit 0F6h
		__emit 0E8h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		add esp, 4h
		lea ecx,  [esp+14h]
		mov esi, eax
		__emit 0E8h
		__emit 078h
		__emit 01Eh
		__emit 022h
		__emit 000h   // call 0x887940
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+30h]
		push eax
		__emit 0E8h
		__emit 0D7h
		__emit 0E8h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		mov edi, eax
		lea eax,  [esp+1Ch]
		push eax
		push edi
		push esi
		__emit 0E8h
		__emit 0C9h
		__emit 0CFh
		__emit 036h
		__emit 000h   // call 0x9D2AB0
		push esi
		__emit 08Bh
		__emit 035h
		__emit 0D4h
		__emit 093h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x13593d4]
		call esi
		push edi
		call esi
		push 24h
		__emit 0E8h
		__emit 036h
		__emit 0C4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 1Ch
		mov dword ptr [esp+10h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+120h], esi
		je L02_665B17
		mov ecx, eax
		__emit 0E8h
		__emit 084h
		__emit 0CCh
		__emit 09Dh
		__emit 0FFh   // call 0x42799
		mov esi, eax
L02_665B17:
		mov ecx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+120h], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 03Ch
		__emit 000h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L03_665B46
		__emit 0E8h
		__emit 016h
		__emit 0AAh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L03_665B46:
		push ecx
		lea edx,  [esp+1Ch]
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 069h
		__emit 030h
		__emit 022h
		__emit 000h   // call 0x888BC0
		mov ecx, esi
		__emit 0E8h
		__emit 0C5h
		__emit 098h
		__emit 09Ch
		__emit 0FFh   // call 0x2F423
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+2Ch]
		push ecx
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 04Ah
		__emit 030h
		__emit 022h
		__emit 000h   // call 0x888BC0
		mov ecx, esi
		__emit 0E8h
		__emit 09Eh
		__emit 015h
		__emit 09Bh
		__emit 0FFh   // call 0x1711B
		mov ecx, dword ptr [ebx+0Ch]
		cmp ecx, 8h
		jae L04_665B94
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebp
		push edx
		push esi
		__emit 0E8h
		__emit 043h
		__emit 0B6h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
L04_665B94:
		mov ecx, esi
		__emit 0E8h
		__emit 009h
		__emit 0A5h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+118h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 114h
		ret 4h
	}
}

// Sends command type 4 (GAMECOMMAND), built by the constructor at 0x00674A40.
// This is where a player's order enters the lockstep: it is the BFME analogue of
// the reference's ConnectionManager::sendLocalGameMessage.
__declspec(naked) void BFMEConnectionManager::sendGameCommand(void *msg)
{
	__asm {
		push 0FFFFFFFFh
		push 10442CBh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 30h
		mov edi, ecx
		__emit 0E8h
		__emit 0CFh
		__emit 0BCh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+8h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+14h], esi
		je L00_666280
		mov ecx, dword ptr [esp+1Ch]
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 003h
		__emit 0BFh
		__emit 09Dh
		__emit 0FFh   // call 0x42181
		mov esi, eax
L00_666280:
		or eax, 0FFFFFFFFh
		mov dword ptr [esi+8h], eax
		mov edx, dword ptr [edi+12028h]
		mov dword ptr [esp+14h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 0D6h
		__emit 0F8h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_6662AC
		__emit 0E8h
		__emit 0B0h
		__emit 0A2h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L01_6662AC:
		push 0FFh
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0C1h
		__emit 08Eh
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0E4h
		__emit 09Dh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Works out who a command has to reach. It compares m_localSlot against
// m_packetRouterSlot and the message's own player id at +0x0C, asks
// DoesCommandRequireACommandID whether the command needs an id at all, and
// hands off to 0x006688D0.
__declspec(naked) void BFMEConnectionManager::decideCommandRelay(void *msg)
{
	__asm {
		push esi
		mov esi, dword ptr [esp+8h]
		push edi
		mov edi, ecx
		mov eax, dword ptr [edi+1202Ch]
		cmp dword ptr [edi+12028h], eax
		jne L00_66941C
		mov ecx, dword ptr [esi+0Ch]
		cmp ecx, eax
		je L01_669450
		cmp ecx, 8h
		jae L01_669450
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 087h
		__emit 0C7h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_669450
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		mov eax, dword ptr [esi+0Ch]
		xor edx, edx
		mov dx, word ptr [esi+10h]
		push ecx
		shl eax, 0Dh
		lea ecx,  [eax+edi+24h]
		push edx
		__emit 0E8h
		__emit 02Ah
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x1423B
		test al, al
		jne L01_669450
		pop edi
		mov al, 1h
		pop esi
		ret 4h
L00_66941C:
		cmp dword ptr [esi+0Ch], eax
		jne L01_669450
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 048h
		__emit 0C7h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L01_669450
		mov eax, dword ptr [esi+8h]
		movzx esi, word ptr [esi+10h]
		push eax
		push esi
		lea ecx,  [edi+10024h]
		__emit 0E8h
		__emit 0F6h
		__emit 0ADh
		__emit 09Ah
		__emit 0FFh   // call 0x1423B
		test al, al
		jne L01_669450
		pop edi
		mov al, 1h
		pop esi
		ret 4h
L01_669450:
		pop edi
		xor al, al
		pop esi
		ret 4h
	}
}

// Copies a player's display name out. For our own slot it reads the string at
// this+0x12058 directly; otherwise it takes the copy path through
// StringBase<UnsignedShort>.
__declspec(naked) void BFMEConnectionManager::getPlayerNameForSlot(void *out, int slot)
{
	__asm {
		push ecx
		mov eax, dword ptr [esp+0Ch]
		cmp eax, dword ptr [ecx+12028h]
		push esi
		mov dword ptr [esp+4h], 0h
		jne L00_664A0F
		mov esi, dword ptr [esp+0Ch]
		add ecx, 12058h
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 0F8h
		__emit 039h
		__emit 022h
		__emit 000h   // call 0x888400
		mov eax, esi
		pop esi
		pop ecx
		ret 8h
L00_664A0F:
		mov ecx, dword ptr [ecx+eax*4+4h]
		test ecx, ecx
		je L01_664A2D
		mov esi, dword ptr [esp+0Ch]
		add ecx, 14h
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 0DAh
		__emit 039h
		__emit 022h
		__emit 000h   // call 0x888400
		mov eax, esi
		pop esi
		pop ecx
		ret 8h
L01_664A2D:
		mov esi, dword ptr [esp+0Ch]
		push 1336E54h
		mov ecx, esi
		__emit 0E8h
		__emit 0C3h
		__emit 039h
		__emit 022h
		__emit 000h   // call 0x888400
		mov eax, esi
		pop esi
		pop ecx
		ret 8h
	}
}
