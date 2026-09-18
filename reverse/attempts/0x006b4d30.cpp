// ?dup006b4d30@Rva006B4D30Owner@@QAEXPAX@Z
// partial score=0.05 date=2026-09-17
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x006B4D30, 2326 bytes.  The carved boundary is a thiscall body
// ending in ret 4 at +0x913.  No source evidence proves the semantic owner,
// so the class and method retain the address token.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long *value);

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &source);
	void releaseBuffer();
};

class UnicodeString : public StringBase<unsigned short>
{
};

class BFMERetailAsciiString : public StringBase<char>
{
};

class Rva006B4D30Xfer
{
public:
	void xfer(class Rva006B4D30XferArg *value);
};

class Rva006B4D30XferArg
{
public:
	virtual void slot00();
	virtual unsigned char slot01();
	virtual void slot02();
	virtual unsigned char slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10(void *value);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27(void *value);
	virtual void slot28();
	virtual void slot29(void *value);
	virtual void slot30(void *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35(void *value);
	virtual void slot36(const char *name, void *value, int size);
};

// The retail body calls the 5-byte thunk symbols with several different
// hidden signatures.  These unions preserve the thunk symbol while allowing
// the call sites to carry the witnessed thiscall/cdecl argument shape.
extern void j_00003544();
extern void j_00008be3();
extern void j_0000b61d();
extern void j_0000e665();
extern void j_0001b009();
extern void j_00025987();
extern void j_00026652();
extern void j_0002e6ae();
extern void j_0003d7cb();
extern void j_00045f0c();

class Rva006B4D30VectorOps
{
public:
	void insert(void *where, void *first, void *last, int count, int flag);
};

class Rva006B4D30Helper
{
public:
	void transfer(Rva006B4D30XferArg *xfer, void *first, void *last);
	void reset();
};

class Rva006B4D30NodeHelper
{
public:
	void destroy();
};

class Rva006B4D30RoomOwner
{
public:
	void setRoomType(int value);
};

class Rva006B4D30Cleanup
{
public:
	void destroy();
};

struct Rva006B4D30Pair
{
	void *first;
	void *second;
};

struct Rva006B4D30Output
{
	unsigned char state;
	unsigned char level;
	unsigned char pad[6];
};

struct Rva006B4D30Ref
{
	void *vftable;
	long references;
};

struct Rva006B4D30ListNode
{
	Rva006B4D30ListNode *next;
	Rva006B4D30ListNode *previous;
	void *value;
	char pad0c[0x18];
};

class Rva006B4D30MutexGuard
{
public:
	Rva006B4D30MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B4D30MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B4D30Owner
{
public:
	void dup006b4d30(void *value);

private:
	char m_pad00[0x3c];
	int m_3c;
	int m_40;
	char m_pad44[0x5fc - 0x44];
	void *m_5fc;
	char m_pad600[0x614 - 0x600];
	char m_614[0x15];
	unsigned char m_629;
	char m_pad62a[4];
	unsigned char m_62e;
	unsigned char m_62f;
	int m_630;
	int m_634[3];
	char m_pad640[0x954 - 0x640];
	void *m_mutex;
	char m_pad958[0x978 - 0x958];
	void *m_978;
	void *m_97c;
	void *m_980;
	void *m_984;
	void *m_988;
	char m_pad98c[0x9c8 - 0x98c];
	Rva006B4D30ListNode *m_9c8;
	char m_pad9cc[0xac8 - 0x9cc];
	Rva006B4D30Ref *m_ac8[3];
	Rva006B4D30Pair *m_ad4;
	Rva006B4D30Pair *m_ad8;
	Rva006B4D30Pair *m_ae0;
	Rva006B4D30Pair *m_ae4;
	char m_padAe8[0xb4c - 0xae8];
	void *m_b4c;
	char m_padB50[0xb68 - 0xb50];
	unsigned char m_b68;
};

#pragma comment(linker, "/alternatename:?xfer@Rva006B4D30Xfer@@QAEXPAVRva006B4D30XferArg@@@Z=?j_0003d7cb@@YAXXZ")
#pragma comment(linker, "/alternatename:?insert@Rva006B4D30VectorOps@@QAEXPAX00HH@Z=?j_00025987@@YAXXZ")
#pragma comment(linker, "/alternatename:?setRoomType@Rva006B4D30RoomOwner@@QAEXH@Z=?j_00045f0c@@YAXXZ")

extern void __cdecl rva006B4D30XferTree(
	Rva006B4D30XferArg *xfer, void *tree);
#pragma comment(linker, "/alternatename:?rva006B4D30XferTree@@YAXPAVRva006B4D30XferArg@@PAX@Z=?j_00003544@@YAXXZ")

static void rva006B4D30Release(Rva006B4D30Ref *value)
{
	if (value != 0 && InterlockedDecrement(&value->references) <= 0)
	{
		typedef void (Rva006B4D30Ref::*Destroy)(int);
		union
		{
			void (__cdecl *plain)();
			Destroy member;
		} call;
		call.plain = (void (__cdecl *)())value->vftable;
		(value->*call.member)(1);
	}
}

static void rva006B4D30AddRef(Rva006B4D30Ref *value)
{
	if (value != 0)
		InterlockedIncrement(&value->references);
}

void Rva006B4D30Owner::dup006b4d30(void *value)
{
	Rva006B4D30XferArg *xfer = (Rva006B4D30XferArg *)value;
	if (xfer->slot03())
		return;

	void *handle = m_mutex;
	Rva006B4D30MutexGuard guard(handle);
	Rva006B4D30Output output;
	output.state = 1;
	output.level = 4;

	if (xfer->slot01())
	{
		m_62f = 1;
		m_630 = 0;
		xfer->slot10(&output);
		void *oldValue = m_5fc;
		xfer->slot36((const char *)0x0111bf48, &m_5fc, 4);
		if (oldValue != m_5fc)
		{
			m_629 = 1;
			xfer->slot36((const char *)0x0111bf58, &m_614[0], 4);
			xfer->slot35((void *)((char *)this + 0x62b));
		}

		for (int i = 0; i < 3; ++i)
		{
			if (i == 2 && output.level >= 3 && m_b68)
			{
				xfer->slot36((const char *)0x0111bf70,
					(char *)this + 0xabc + i * 4, 4);
			}

			Rva006B4D30Xfer *record =
				(Rva006B4D30Xfer *)((char *)this + 0xb0 + i * 0x1c4);
			record->xfer(xfer);
			rva006B4D30XferTree(xfer,
				(char *)this + 0x264 + i * 0xc);

			if (output.level >= 4)
				xfer->slot36((const char *)0x0111bd5c,
					(char *)this + 0x634 + i * 4, 4);
		}
	}

	if (!xfer->slot01())
		goto finish;

	{
		Rva006B4D30Pair *begin = m_ae0;
		Rva006B4D30Pair *end = m_ae4;
		if (begin != end)
		{
			Rva006B4D30Pair *source = begin + 1;
			while (source != end)
			{
				*begin = *source;
				++begin;
				++source;
			}
			m_ae4 = begin;
		}

		void *incoming = 0;
		xfer->slot30(&incoming);
		if (incoming != 0)
		{
			int stride = 8;
			void *first = 0;
			void *last = 0;
			xfer->slot30(&first);
			xfer->slot27(&last);
			if (m_ae0 != m_ae4)
			{
				m_ae0->first = first;
				m_ae0->second = last;
				m_ae0 = (Rva006B4D30Pair *)((char *)m_ae0 + stride);
			}
			else
			{
				Rva006B4D30VectorOps vector;
				vector.insert(m_ae4, first, last, 1, 1);
			}
			m_62e = 1;
		}
	}

	{
		int groupCount = (int)(m_ad8 - m_ad4);
		xfer->slot30(&groupCount);
		Rva006B4D30Pair *group = m_ad4;
		while (group != m_ad8)
		{
			Rva006B4D30Pair *next = group + 1;
			void *scratch = 0;
			xfer->slot30(&scratch);
			if (group->first != 0)
			{
				Rva006B4D30Helper helper;
				helper.transfer(xfer, group->first, group->second);
			}
			group = next;
		}
	}

	if (m_b68 && output.level >= 3)
	{
		for (int i = 0; i < 3; ++i)
		{
			Rva006B4D30Ref *reference = m_ac8[i];
			if (reference != 0)
			{
				rva006B4D30Release(reference);
				m_ac8[i] = 0;
			}
		}
	}

	{
		StringBase<unsigned short> *wide =
			(StringBase<unsigned short> *)m_978;
		StringBase<unsigned short> *wideEnd =
			(StringBase<unsigned short> *)m_97c;
		while (wide != wideEnd)
		{
			((StringBase<unsigned short> *)m_97c)->set(*wide);
			++wide;
		}
		m_97c = wide;

		UnicodeString *unicode = (UnicodeString *)m_984;
		UnicodeString *unicodeEnd = (UnicodeString *)m_988;
		while (unicode != unicodeEnd)
		{
			unicode->set(*unicodeEnd);
			++unicode;
		}
		m_988 = unicode;
	}

	{
		Rva006B4D30ListNode local;
		local.next = &local;
		local.previous = &local;
		Rva006B4D30ListNode *head = m_9c8;
		if (head != 0)
		{
			Rva006B4D30ListNode *node = head->next;
			while (node != head)
			{
				Rva006B4D30Ref *reference =
					(Rva006B4D30Ref *)node->value;
				if (reference != 0)
					rva006B4D30AddRef(reference);
				Rva006B4D30Helper helper;
				helper.transfer(xfer, node + 1, node + 2);
				node = node->next;
			}
		}
	}

finish:
	{
		Rva006B4D30Cleanup cleanup;
		cleanup.destroy();
	}
	{
		Rva006B4D30Helper helper;
		helper.transfer(xfer, (char *)this + 0x978,
			(char *)this + 0x97c);
		helper.transfer(xfer, (char *)this + 0x984,
			(char *)this + 0x988);
	}
}
