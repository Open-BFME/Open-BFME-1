// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME body of the music-track completion script condition.

typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[0x8];
	int m_int;
	unsigned char m_beforeString[0x4];
	AsciiString m_string;
};

class AudioManager
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual Bool hasMusicTrackCompleted(const AsciiString *, int, int, int) const = 0;
};

extern AudioManager *TheAudio;

class ScriptConditions
{
protected:
	Bool evaluateMusicHasCompleted(Parameter *, Parameter *);
};

// ?evaluateMusicHasCompleted@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateMusicHasCompleted(
	Parameter *pMusicParm, Parameter *pIntParm)
{
	AsciiString str = pMusicParm->getString();
	return TheAudio->hasMusicTrackCompleted(&str, pIntParm->getInt(), 0, 1);
}
