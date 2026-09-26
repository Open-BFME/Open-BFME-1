// Retail body at 0x000CBEC0 is the C callback selected by bfmeGoEUAc.

class AsciiString
{
public:
	void *m_data;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, int extra);
	~AudioEventRTS();
	void setPlayerIndex(int index);

private:
	unsigned char m_padding[0x70];
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class AudioClientUpdate
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void addAudioEvent(AudioEventRTS *event) = 0;
};

class Rva0039B820Accumulator
{
public:
	void adjust(int delta);

private:
	unsigned char m_padding[4];
	int m_value;
};

class BfmePlayerTemplate
{
private:
	unsigned char m_padding[0x100];

public:
	AsciiString m_audioEventName;
};

extern AudioClientUpdate *TheAudioClientUpdate;

class BfmeItemEUA
{
public:
	void bfmeRunEUAc(void *context);

private:
	unsigned char m_padding00[4];
	BfmePlayerTemplate *m_playerTemplate;
	unsigned char m_padding08[0x1c];
	int m_playerIndex;
	unsigned char m_padding28[0x24c];
	Rva0039B820Accumulator m_specialPowerState;
};

void BfmeItemEUA::bfmeRunEUAc(void *context)
{
	int delta = reinterpret_cast<int>(context);
	m_specialPowerState.adjust(delta);

	if (m_playerTemplate && delta > 0 && m_playerTemplate->m_audioEventName.m_data && TheAudioClientUpdate)
	{
		AudioEventRTS event(m_playerTemplate->m_audioEventName, 0);
		event.setPlayerIndex(m_playerIndex);
		TheAudioClientUpdate->addAudioEvent(&event);
	}
}
