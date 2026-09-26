// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: dispatchIndexedValue, retail 0x00858070, 66 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// It is a guard in front of the GameSpy chat SDK: bail unless the object's
// field at +0x48 is set and at least one of the two per-index pointers is, then
// hand off to chatSetChannelKeysA with the object's chat handle and the channel
// name for that index.
//
// The arithmetic fixes the layout. The name array strides 0x101 from +0x80, and
// three of those end at 0x383, which is exactly where the first pointer array
// at +0x384 begins; the second array is 0x0C further on, so both hold three
// entries. That the three counts agree is what makes the reading more than a
// guess.
//
// The hand-off is a tail jump, not a call: the last four arguments pass through
// untouched at the same stack slots and only the first two are overwritten in
// place.

struct BfmeChatChannelKeyState
{
	void *m_bfmeChat;					// +0x000
	char m_bfmeHeadA[0x48 - 0x04];
	void *m_bfmeField48;					// +0x048
	char m_bfmeHeadB[0x80 - 0x4C];
	char m_bfmeChannelName[3][0x101];			// +0x080
	char m_bfmePad[0x384 - 0x383];
	void *m_bfmeKeys[3];					// +0x384
	void *m_bfmeValues[3];					// +0x390
};

extern "C" void chatSetChannelKeysA(void *chat, char *channel, void *user,
	int num, int *keys, int *values);			// retail 0x008619F0

// ?dispatchIndexedValue@@YAXPAXH0HPAH1@Z
void dispatchIndexedValue(void *object, int index, void *user, int num, int *keys, int *values)
{
	BfmeChatChannelKeyState *state = (BfmeChatChannelKeyState *)object;

	if (!state->m_bfmeField48)
		return;

	if (!state->m_bfmeKeys[index] && !state->m_bfmeValues[index])
		return;

	chatSetChannelKeysA(state->m_bfmeChat, state->m_bfmeChannelName[index],
		user, num, keys, values);
}
