// ?d_003d0a40@@YAXXZ
// partial score=0.77 date=2026-09-24
// ?xfer@Rva003D0A40Map@@QAEXPAVXfer@@PAX@Z
// LargeGroupAudioMap layout and Xfer body at retail RVA 0x003D0A40.
// The owner and context method names remain address-derived pending a named ABI witness.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class Y1ForEachArg;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot20();
	virtual void slot24();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual Xfer &xferAsciiString(void *value);
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual Xfer &xferInt(int *value);
};

extern void j_00039117();
extern void j_00014ac4();

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap();
	~LargeGroupAudioKeyMap();

	void load(Xfer *xfer)
	{
		typedef void (LargeGroupAudioKeyMap::*Load)(Xfer *);
		union
		{
			void (*raw)(void);
			Load member;
		} target;
		target.raw = j_00039117;
		(this->*target.member)(xfer);
	}

	void save(Xfer *xfer)
	{
		typedef void (LargeGroupAudioKeyMap::*Save)(Xfer *);
		union
		{
			void (*raw)(void);
			Save member;
		} target;
		target.raw = j_00014ac4;
		(this->*target.member)(xfer);
	}

	void *m_wordsBegin;
	void *m_wordsEnd;
	void *m_wordsCapacity;
};

class Rva003D3250
{
public:
	bool equals(const Rva003D3250 *other) const;
};

class Rva003CD2D0
{
public:
	int total() const;
};

class Rva003D0720
{
public:
	void run(Y1ForEachArg *first, Y1ForEachArg *second);
};

class SoundKeyPair;

class SoundKeyVector
{
public:
	SoundKeyPair **m_begin;
	SoundKeyPair **m_end;
	SoundKeyPair **m_capacity;
};

class SoundKeyPair
{
public:
	LargeGroupAudioKeyMap m_keyMap;
	void *m_headerKey;
	void *m_groups[4];
	void *m_owner;
	SoundKeyVector m_second;
	SoundKeyVector m_first;
};

class Rva003D0A40Map
{
public:
	void xfer(Xfer *xfer, void *context);

private:
	void *m_vtable;
	void *m_owner;
	unsigned char m_isOverride;
	unsigned char m_pad09[3];
	unsigned char m_pad0c[8];
	unsigned char m_soundName[4];
	SoundKeyVector m_sound;
};

static const char *const kAudioMap = (const char *)0x010EE17C;

void Rva003D0A40Map::xfer(Xfer *xfer, void *context)
{
	Rva003D0A40Map *owner = this;
	int count = (int)(owner->m_sound.m_end - owner->m_sound.m_begin);
	xfer->xferInt(&count);

	if (xfer->isLoading())
	{
		for (int index = 0; index < count; ++index)
		{
			LargeGroupAudioKeyMap key;
			key.load(xfer);
			int elementCount;
			xfer->xferInt(&elementCount);

			SoundKeyPair **pair = owner->m_sound.m_begin;
			for (; pair != owner->m_sound.m_end; ++pair)
			{
				if (((const Rva003D3250 *)*pair)->equals(
					(const Rva003D3250 *)&key))
					break;
			}

			if (pair != owner->m_sound.m_end &&
				elementCount == ((const Rva003CD2D0 *)*pair)->total())
			{
				xfer->beginBlock(kAudioMap);
				((Rva003D0720 *)*pair)->run(
					(Y1ForEachArg *)xfer, (Y1ForEachArg *)context);
				xfer->endBlock();
			}
			else
				xfer->skipBlock(kAudioMap);
		}
	}
	else
	{
		SoundKeyPair **pair = owner->m_sound.m_begin;
		while (pair != owner->m_sound.m_end)
		{
			(*pair)->m_keyMap.save(xfer);
			int elementCount = ((const Rva003CD2D0 *)*pair)->total();
			xfer->xferInt(&elementCount);
			xfer->beginBlock(kAudioMap);
			((Rva003D0720 *)*pair)->run(
				(Y1ForEachArg *)xfer, (Y1ForEachArg *)context);
			xfer->endBlock();
			++pair;
		}
	}
}
