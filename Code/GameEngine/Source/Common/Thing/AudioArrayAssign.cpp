// cl: /DNDEBUG /MD /EHsc
//
// BFME's AudioArray has 109 pointer slots. Its assignment follows the ZH
// memberwise copy/allocation algorithm, with one important retail difference:
// a null source slot deletes an existing destination event before clearing it.
// The named type and operator come from the authoritative ThingTemplate.h;
// the 0x74 allocation and member call at +4 prove the local event layout.

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);
	AudioEventRTS &operator=(const AudioEventRTS &that);

private:
	char m_data[0x70];
};

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS(const DynamicAudioEventRTS &that) : m_event(that.m_event) {}
	virtual ~DynamicAudioEventRTS();

	AudioEventRTS m_event;
};

class AudioArray
{
public:
	DynamicAudioEventRTS *m_audio[109];
	AudioArray &operator=(const AudioArray &that);
};

// ??4AudioArray@@QAEAAV0@ABV0@@Z
AudioArray &AudioArray::operator=(const AudioArray &that)
{
	if (this != &that)
	{
		for (int i = 0; i < 109; ++i)
		{
			if (that.m_audio[i])
			{
				if (m_audio[i])
					*m_audio[i] = *that.m_audio[i];
				else
					m_audio[i] = new DynamicAudioEventRTS(*that.m_audio[i]);
			}
			else if (m_audio[i])
			{
				delete m_audio[i];
				m_audio[i] = 0;
			}
		}
	}
	return *this;
}
