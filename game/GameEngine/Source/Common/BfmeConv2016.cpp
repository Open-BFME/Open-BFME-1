// Retail installs 0x010FA338 here, the vtable the ledger records as
// ??_7WinInstanceData@@6B@ and which WinInstanceData.cpp defines (its
// constructor at 0x00499B40 is the only other installer). The local name has
// to be that one, not a private placeholder.
extern "C" const char __identifier("??_7WinInstanceData@@6B@")[];

// Retail's global at 0x012F12CC is EA's DisplayStringManager; defined once in
// GameClient/DisplayStringManager.cpp.  The local view below only exists to spell
// the slots this TU calls, so every use casts.
class DisplayStringManager;

// The four small members the destructor tears down are each one releaseBuffer
// string body.  Retail's call at 0x00887940 lands on
// ??1BFMEPlayerTemplateAsciiString@@QAE@XZ (game/Libraries/Source/string/
// StringBase.cpp, a C++ alias of ?releaseBuffer@?$StringBase@D@@AAEXXZ), which
// is the only string-destructor definition among the three bodies folded at that
// VA.  The declaration below is the established local view -- see
// game/GameEngine/Source/Common/BfmeOwnerDtorBU.cpp -- and stays
// declaration-only: this TU never defines the body.
template <class T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();

	void *m_bfmeDataEAZ;
};

class BFMEPlayerTemplateAsciiString : private StringBase<char>
{
};

class Rva0048EC80Manager
{
public:
	virtual void bfmeSlot00EAZ();
	virtual void bfmeSlot01EAZ();
	virtual void bfmeSlot02EAZ();
	virtual void bfmeSlot03EAZ();
	virtual void bfmeSlot04EAZ();
	virtual void bfmeSlot05EAZ();
	virtual void bfmeSlot06EAZ();
	virtual void bfmeSlot07EAZ();
	virtual void bfmeSlot08EAZ();
	virtual void bfmeSlot09EAZ();
	virtual void bfmeReleaseEAZ(void *item);
};

extern DisplayStringManager *TheDisplayStringManager;

class BfmeHostEAZ
{
public:
	~BfmeHostEAZ();

	void *volatile m_bfmeVftEAZ;
	unsigned char m_bfmeHeadEAZ[0x184];
	BFMEPlayerTemplateAsciiString m_bfmeS0EAZ;
	BFMEPlayerTemplateAsciiString m_bfmeS1EAZ;
	BFMEPlayerTemplateAsciiString m_bfmeS2EAZ;
	BFMEPlayerTemplateAsciiString m_bfmeS3EAZ;
	int m_bfmePadEAZ;
	void *m_bfmeAEAZ;
	void *m_bfmeBEAZ;
	int m_bfmeCEAZ;
};

BfmeHostEAZ::~BfmeHostEAZ()
{
	m_bfmeVftEAZ = (void *)__identifier("??_7WinInstanceData@@6B@");

	void *a = *(void *volatile *)&m_bfmeAEAZ;

	if (a != 0)
		((Rva0048EC80Manager *)TheDisplayStringManager)->bfmeReleaseEAZ(a);

	if (m_bfmeBEAZ != 0)
		((Rva0048EC80Manager *)TheDisplayStringManager)->bfmeReleaseEAZ(m_bfmeBEAZ);

	m_bfmeCEAZ = 0;
}
