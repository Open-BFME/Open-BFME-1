// ?xfer@Rva003D1020@@QAEXPAVXfer@@@Z
// partial score=0.78 date=2026-09-17
// cl: /DNDEBUG /MD /O2 /EHsc
// The owner of this body is not named by the retail evidence.  Its vector is
// at +0x04/+0x08, its transfer guard is at +0x2c, and the related record body
// is the already pinned 0x003D0A40 two-argument transfer helper.

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

	const StringBase<char>::Header *header(void) const { return m_data; }

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

static void transferRecord(Rva003D0A40Record *record, Xfer *xfer,
	BFMERetailAsciiString *name)
{
	typedef void (Rva003D0A40Record::*RecordTransfer)(Xfer *,
		BFMERetailAsciiString *);
	union
	{
		void (*raw)(void);
		RecordTransfer member;
	} call;
	call.raw = j_000175d0;
	(record->*call.member)(xfer, name);
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

static const char *const kAudioMap = (const char *)0x010EE3F8;
static const char *const kEmptyAscii = (const char *)0x0107388B;

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
				const StringBase<char>::Header **recordDataAddress =
					(const StringBase<char>::Header **)((const char *)(*record) + 0x14);
				const StringBase<char>::Header *nameData = name.header();
				int nameLength = nameData ? nameData->m_length : 0;
				const char *nameText = nameData ? nameData->m_text : kEmptyAscii;

				const StringBase<char>::Header *recordData = *recordDataAddress;
				int recordLength;
				if (recordData != 0)
					recordLength = recordData->m_length;
				else
					recordLength = 0;
				const char *recordText;
				const StringBase<char>::Header *recordTextData = recordData;
				if (recordTextData != 0)
					recordText = recordTextData->m_text;
				else
					recordText = kEmptyAscii;
				int compareLength = recordLength < nameLength ?
					recordLength : nameLength;
				if (_memicmp(recordText, nameText, compareLength) == 0 &&
					recordLength == nameLength)
					break;
			}

			if (record == owner->m_end)
				xfer->skipBlock(kAudioMap);
			else
			{
				xfer->beginBlock(kAudioMap);
				transferRecord(*record, xfer, &name);
				xfer->endBlock();
			}
		}
		else
		{
			Rva003D0A40Record *record = owner->m_begin[index];
			BFMERetailAsciiString savedName(record->m_name);
			xfer->xferAsciiString(&savedName);
			xfer->beginBlock(kAudioMap);
			transferRecord(record, xfer, &savedName);
			xfer->endBlock();
		}
	}

	xfer->isLoading();
}
