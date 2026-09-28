// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Sound key pair transfer of a LargeGroupAudio map, retail 0x003D0A40 (401
// bytes). The receiver matches LargeGroupAudioMap's SoundKeyPair vector at
// +0x18; the owner and the pass-through context stay address-derived.

#include <vector>

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

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap();
	~LargeGroupAudioKeyMap();

	void xfer(Xfer *xfer);

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

class SoundKeyVector : public _STL::vector<SoundKeyPair *,
	_STL::allocator<SoundKeyPair *> >
{
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

// ?xfer@Rva003D0A40Map@@QAEXPAVXfer@@PAX@Z
void Rva003D0A40Map::xfer(Xfer *xfer, void *context)
{
	int count = m_sound.size();
	xfer->xferInt(&count);

	if (xfer->isLoading())
	{
		for (int index = 0; index < count; ++index)
		{
			LargeGroupAudioKeyMap key;
			key.load(xfer);
			int elementCount;
			xfer->xferInt(&elementCount);

			SoundKeyVector::iterator pair = m_sound.begin();
			for (; pair != m_sound.end(); ++pair)
			{
				if (((const Rva003D3250 *)*pair)->equals((const Rva003D3250 *)&key))
					break;
			}

			if (pair != m_sound.end() && elementCount == ((const Rva003CD2D0 *)*pair)->total())
			{
				xfer->beginBlock("SoundKeyPair");
				((Rva003D0720 *)*pair)->run((Y1ForEachArg *)xfer, (Y1ForEachArg *)context);
				xfer->endBlock();
			}
			else
				xfer->skipBlock("SoundKeyPair");
		}
	}
	else
	{
		SoundKeyVector::iterator it = m_sound.begin();
		while (it != m_sound.end())
		{
			SoundKeyPair *pair = *it;
			pair->m_keyMap.xfer(xfer);
			int elementCount = ((const Rva003CD2D0 *)pair)->total();
			xfer->xferInt(&elementCount);
			xfer->beginBlock("SoundKeyPair");
			((Rva003D0720 *)pair)->run((Y1ForEachArg *)xfer, (Y1ForEachArg *)context);
			xfer->endBlock();
			++it;
		}
	}
}
