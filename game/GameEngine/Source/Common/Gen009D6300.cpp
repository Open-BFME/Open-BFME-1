// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the optional activation helper at retail RVA 0x009D6300.

class BfmeActivationStream
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual int bfmeTransfer(const void *value, int size);
};

class BfmeActivationPartA { public: void bfmeResetA(); private: char m_pad[0x0c]; };
class BfmeActivationPartB { public: void bfmeResetB(); private: char m_pad[0x14]; };
class BfmeActivationPartC { public: void bfmeResetC(); private: char m_pad[0x18]; };

class Gen009D6300
{
public:
	bool bfmeActivate(void *value);
	bool bfmeTryActivate(BfmeActivationStream *stream, int enabled, bool flags);

private:
	void *m_unknown0;
	BfmeActivationStream *m_stream;
	bool m_flag;
	char m_pad9[3];
	BfmeActivationPartA m_partA;
	BfmeActivationPartB m_partB;
	BfmeActivationPartC m_partC;
	int m_state;
};

bool Gen009D6300::bfmeTryActivate(
	BfmeActivationStream *stream, int enabled, bool flags)
{
	if (m_stream != 0)
		return false;

	unsigned int magic[2] = {'EALA', 'RTS2'};
	if (stream->bfmeTransfer(&magic[0], 4) != 4)
		return false;
	if (stream->bfmeTransfer(&magic[1], 4) != 4)
		return false;
	if (stream->bfmeTransfer(&enabled, 4) != 4)
		return false;

	int normalizedFlags = flags != 0;
	if (stream->bfmeTransfer(&normalizedFlags, 4) != 4)
		return false;

	m_stream = stream;
	m_flag = flags;
	m_partA.bfmeResetA();
	m_partB.bfmeResetB();
	m_partC.bfmeResetC();
	return true;
}

bool Gen009D6300::bfmeActivate(void *value)
{
	if (value != 0 &&
		!bfmeTryActivate(static_cast<BfmeActivationStream *>(value), 1, false))
		return false;

	m_state = 0;
	return true;
}
