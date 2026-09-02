// cl: /DNDEBUG /MD
// Address-derived audio predicate at retail 0x004910C0.

#define BFME_VSLOT(n) virtual void slot##n();

class Rva004910C0Audio
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4)
	virtual void refresh();
	BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	BFME_VSLOT(14) BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17)
	BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20) BFME_VSLOT(21)
	BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24) BFME_VSLOT(25)
	BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33)
	BFME_VSLOT(34) BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37)
	BFME_VSLOT(38) BFME_VSLOT(39) BFME_VSLOT(40) BFME_VSLOT(41)
	BFME_VSLOT(42) BFME_VSLOT(43)
	virtual bool rejects( int kind );
};

#undef BFME_VSLOT

extern Rva004910C0Audio *TheAudio;

class Rva004910C0AudioEvent
{
public:
	bool isAllowed();

private:
	char m_pad[0x1c];
	int m_kind;
};

bool Rva004910C0AudioEvent::isAllowed()
{
	bool allowed = true;
	if( TheAudio ) {
		TheAudio->refresh();
		if( m_kind != 1 )
			allowed = !TheAudio->rejects( m_kind );
	}
	return allowed;
}
