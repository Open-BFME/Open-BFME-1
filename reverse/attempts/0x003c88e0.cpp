// ?consume@Glo012F1028Sub@@QAEXPAVAsciiString@@@Z
// partial score=0.75 date=2026-09-10
// cl: /O2 /DNDEBUG /MD /EHsc
//
// Glo012F1028Sub::consume, retail 0x003C88E0, 283 bytes.  setCampaign at
// 0x003B41A0 calls the 5-byte ILT 0x00045B88, whose retail jump target is this
// body.  The sub-object owns the currently selected record at +4, the
// ref-counted resource at +0x24, and a pointer vector at +0x28/+0x2c.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Glo012F1028AsciiData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class AsciiString
{
public:
	Glo012F1028AsciiData *m_data;
};

class Glo012F1028AsciiView
{
public:
	int compare(const AsciiString &that) const
	{
		int thatLength = that.m_data ? that.m_data->m_length : 0;
		const char *thatText = that.m_data ? that.m_data->m_text :
			g_bfmeEmptyAscii;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : g_bfmeEmptyAscii;
		int length = thisLength < thatLength ? thisLength : thatLength;
		int difference = memcmp(thisText, thatText, length);
		if (difference != 0)
			return difference;
		return thisLength - thatLength;
	}

	Glo012F1028AsciiData *m_data;
};

class Glo012F1028Record
{
public:
	char m_pad00[4];
	AsciiString m_name;
};

class Glo012F1028Resource
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;

	int m_refCount;
};

static __forceinline void releaseGlo012F1028Resource(
	Glo012F1028Resource *resource)
{
	if (resource != 0)
	{
		resource->slot16();
		if (--resource->m_refCount == 0)
			resource->slot00();
	}
}

class Glo012F1028Sub
{
public:
	void consume(AsciiString *key);

private:
	void *m_vptr;
	Glo012F1028Record *m_selected;
	char m_pad08[0x1c];
	Glo012F1028Resource *m_resource;
	Glo012F1028Record **m_begin;
	Glo012F1028Record **m_end;
};

// ?consume@Glo012F1028Sub@@QAEXPAVAsciiString@@@Z
void Glo012F1028Sub::consume(AsciiString *key)
{
	register Glo012F1028Sub *owner = this;
	unsigned int index = 0;

	if ((unsigned int)(owner->m_end - owner->m_begin) > 0)
	{
		Glo012F1028AsciiView query = { key->m_data };
		Glo012F1028Record **it = owner->m_begin;
		for (; index < (unsigned int)(owner->m_end - owner->m_begin);
			++index, ++it)
		{
			Glo012F1028Record *candidate = *it;
			if (query.compare(candidate->m_name) == 0)
			{
				if (owner->m_selected != 0 &&
					owner->m_selected != owner->m_begin[index])
				{
					Glo012F1028Resource *resource = owner->m_resource;
					if (resource != 0)
						releaseGlo012F1028Resource(resource);
					owner->m_resource = 0;
					owner->m_resource = 0;
					owner->m_selected = 0;
				}
				owner->m_selected = owner->m_begin[index];
				return;
			}
		}
	}
}
