// ?d_003d2d00@@YAXXZ
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Retail layout: address-derived (identity unproven; see
// reverse/re_attempts.log for 0x003D2D00). Same BfmeBaseVUH family as the
// landed Code/GameEngine/Source/Common/BfmeConv1639.cpp (??1BfmeOwnVUH@@QAE@
// XZ, 0x001B5550): a guarded release of a sink pointer at +4 via
// bfmeSlot0VUH(1) (virtual, explicit "1" flag argument -- matches retail's
// `push 1; call [eax]`), installing the shared base vftable already pinned
// as ??_7BfmeBaseVUH@@6B@,0x0107FCB0. This derived class is bigger: it adds
// an AsciiString at +0x14 (releaseBuffer, retail 0x00887940) and an owning
// vector<Gen_dtor_003d2190 *> at +0x18/+0x1c/+0x20 (per-element non-virtual
// dtor through the existing pin ??1Gen_dtor_003d2190@@UAE@XZ,0x0000D0B7, then
// bfmeFreeScalar per element, then the whole array released through the
// bfmeRelease branch already established in
// Code/GameEngine/Source/Common/Bfme5TwoVectorDtors.cpp). The own vftable is
// newly pinned here as ??_7BfmeOwnVUH003D2D00@@6B@,0x010EE124 (additive; 5
// retail slots, so 4 more virtuals than the inherited bfmeSlot0VUH).

void __cdecl bfmeFreeScalar(void *block);                      // retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);  // retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeSinkVUH
{
public:
	virtual void bfmeSlot0VUH(int flags);
};

class BfmeBaseVUH
{
public:
	~BfmeBaseVUH()
	{
		BfmeSinkVUH *sink = m_bfme04;

		if (sink != 0)
			sink->bfmeSlot0VUH(1);

		m_bfme04 = 0;
	}

	virtual void bfmeSlot0VUH();
	virtual void bfmeSlot1VUH();
	virtual void bfmeSlot2VUH();
	virtual void bfmeSlot3VUH();
	virtual void bfmeSlot4VUH();
	BfmeSinkVUH *m_bfme04;
	char m_bfmePad08[4];
};

class AsciiStringVUH
{
public:
	~AsciiStringVUH() { releaseBuffer(); }
	void releaseBuffer();

private:
	char *m_data;
};

class Gen_dtor_003d2190
{
public:
	~Gen_dtor_003d2190();     // pinned ??1Gen_dtor_003d2190@@UAE@XZ, 0x0000D0B7
};

class BfmeVecPtrVUH
{
public:
	~BfmeVecPtrVUH()
	{
		Gen_dtor_003d2190 **p = m_start;
		Gen_dtor_003d2190 **end = m_finish;

		while (p != end) {
			Gen_dtor_003d2190 *elem = *p;

			if (elem) {
				elem->~Gen_dtor_003d2190();
				bfmeFreeScalar(elem);
			}

			++p;
		}

		Gen_dtor_003d2190 **start = m_start;

		if (start)
			bfmeRelease(start, (unsigned)((char *)m_capacityEnd - (char *)start));
	}

private:
	Gen_dtor_003d2190 **m_start;         // +0x18
	Gen_dtor_003d2190 **m_finish;        // +0x1c
	Gen_dtor_003d2190 **m_capacityEnd;   // +0x20
};

class BfmeOwnVUH003D2D00 : public BfmeBaseVUH
{
public:
	~BfmeOwnVUH003D2D00();

private:
	char m_gap0c[8];              // +0x0c .. +0x13, untouched by this dtor
	AsciiStringVUH m_ascii;       // +0x14
	BfmeVecPtrVUH m_vec;          // +0x18
};

// ?d_003d2d00@@YAXXZ
BfmeOwnVUH003D2D00::~BfmeOwnVUH003D2D00()
{
}
