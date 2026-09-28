// cl: /DNDEBUG /MD /O2 /EHsc
// "AudioMap" record-vector transfer, retail 0x003D1020 (500 bytes). The owner stays
// address-derived; each record is transferred by 0x003D0A40 with the version as context.

typedef bool Bool;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

template <class T> class StringBase
{
public:
	struct Header
	{
		int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};

	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);

protected:
	Header *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(void) : StringBase<char>() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other)
	{
	}
	~BFMERetailAsciiString(void) { releaseBuffer(); }

	int getLength(void) const { return m_data ? m_data->m_length : 0; }
	const char *str(void) const { return m_data ? m_data->m_text : ""; }

	int compareNoCase(const BFMERetailAsciiString &other) const
	{
		int lenOther = other.getLength();
		const char *pOther = other.str();
		int lenThis = getLength();
		const char *pThis = str();
		int shorter = lenThis < lenOther ? lenThis : lenOther;
		int diff = _memicmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;
		return lenThis - lenOther;
	}

private:
	void releaseBuffer(void);
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00(void);
	virtual Bool isLoading(void);
	virtual void slot08(void);
	virtual Bool slot0c(void);
	virtual void slot10(void);
	virtual void beginBlock(const char *name);
	virtual void endBlock(void);
	virtual void skipBlock(const char *name);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual Xfer &xferAsciiString(BFMERetailAsciiString *value);
	virtual void slot6c(void);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual Xfer &xferInt(int *value);
	virtual void slot7c(void);
	virtual void slot80(void);
	virtual void slot84(void);
	virtual void slot88(void);
	virtual Xfer &xferBool(Bool *value);
};

class Rva003D0A40Record
{
public:
	char m_pad00[0x14];
	BFMERetailAsciiString m_name;
};

extern void j_000175d0(void);

// 0x003D0A40 is __thiscall (Xfer *, void *context) with ret 8, reached through its thunk.
static void transferRecord(Rva003D0A40Record *record, Xfer *xfer,
	XferVersion *version)
{
	typedef void (Rva003D0A40Record::*RecordTransfer)(Xfer *, XferVersion *);
	union
	{
		void (*raw)(void);
		RecordTransfer member;
	} call;
	call.raw = j_000175d0;
	(record->*call.member)(xfer, version);
}

class Rva003D1020
{
public:
	void xfer(Xfer *xfer);

private:
	void *m_vtable;
	Rva003D0A40Record **m_begin;
	Rva003D0A40Record **m_end;
	Rva003D0A40Record **m_capacity;
	char m_pad10[0x1c];
	Bool m_transferGuard;
};

// ?xfer@Rva003D1020@@QAEXPAVXfer@@@Z
void Rva003D1020::xfer(Xfer *xfer)
{
	Rva003D1020 *owner = this;
	if (xfer->slot0c())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	xfer->xferBool(&owner->m_transferGuard);
	if (owner->m_transferGuard)
		return;

	int count = (int)(owner->m_end - owner->m_begin);
	xfer->xferInt(&count);
	for (int index = 0; index < count; ++index)
	{
		if (xfer->isLoading())
		{
			BFMERetailAsciiString name;
			xfer->xferAsciiString(&name);
			Rva003D0A40Record **record = owner->m_begin;
			for (; record != owner->m_end; ++record)
			{
				if ((*record)->m_name.compareNoCase(name) == 0)
					break;
			}

			if (record == owner->m_end)
			{
				xfer->skipBlock("AudioMap");
				continue;
			}
			xfer->beginBlock("AudioMap");
			transferRecord(*record, xfer, &version);
			xfer->endBlock();
		}
		else
		{
			Rva003D0A40Record *record = owner->m_begin[index];
			const BFMERetailAsciiString *source = &record->m_name;
			BFMERetailAsciiString savedName(*source);
			xfer->xferAsciiString(&savedName);
			xfer->beginBlock("AudioMap");
			transferRecord(record, xfer, &version);
			xfer->endBlock();
		}
	}

	xfer->isLoading();
}
