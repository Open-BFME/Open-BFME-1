// ?bfmeStep2@Gen_007892D0@@AAEXXZ
// partial score=0.24 date=2026-09-09
// stlport
// Nine more bodies in three shapes.
//
// 0x004410A0, 0x0077F000 and 0x007892D0 are three no-argument member calls in
// a row on the same this: esi holds it across the first two calls and the
// third is in tail position, so it becomes a jump after esi is popped.
//
// 0x00891B80, 0x00892890 and 0x008AD330 release a shared block. The refcount
// is decremented with a sixteen-bit dec and then RE-READ by a separate cmp
// rather than branched on the flags dec already set, which is what two
// statements give -- decrement, then test the member -- not `if (--n == 0)`.
// The release itself goes through slot +0x04 of a global table of __cdecl
// function pointers, cleaned with pop ecx because there is exactly one
// argument.
//
// 0x008A0D60, 0x008C5B30 and 0x008C5C00 free a buffer only when it exists,
// passing the element count at +0x04 scaled by four; the scale is a shl, so
// the count is a count and not a byte size.

#include <hash_map>

template <class T>
class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &source);
	StringBase(const T *text);
	~StringBase();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

protected:
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &source)
		: StringBase<char>(source)
	{
	}
	~AsciiString() {}

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	const char *str() const
	{
		return m_data ? &m_data->text[0] : (const char *)0x0107388b;
	}

	void format(AsciiString format, ...);
};

typedef AsciiString BFMERetailAsciiString;

class File
{
public:
	virtual ~File();
	virtual void slot04();
	virtual void close();
	virtual int slot0c(void *buffer, int bytes);
	virtual int slot10(const void *buffer, int bytes);
	virtual int slot14(int bytes, int mode);
	virtual void nextLine(char *buffer, int bufferSize);
	virtual bool slot1c();
	virtual bool slot20(int &value);
	virtual bool slot24(float &value);
	virtual bool slot28(AsciiString &value);
	virtual bool slot2c(const char *format, ...);
	virtual int slot30();
	virtual int slot34();
	virtual char *slot38();
	virtual File *slot3c();

	bool eof();
};

class FileSystem
{
public:
	File *openFile(const char *name, int access);
};

extern FileSystem *TheOpen2FileSystem;

// This helper is static in Open2Conv007.cpp.  MSVC's private-register ABI is
// encoded by the declaration's internal linkage; the exact decorated name is
// already carried by that matched body, so this TU-local declaration can use
// it without inventing a second semantic owner.
static File *Open2OpenPastSeparators(const AsciiString &name)
{
	const char *text = name.str();
	File *file = TheOpen2FileSystem->openFile(text, 1);
	while (file == 0)
	{
		text = ::strchr(text, '\\');
		if (text == 0)
			return 0;
		++text;
		file = TheOpen2FileSystem->openFile(text, 1);
	}
	return file;
}

class DX8Wrapper
{
public:
	static void Get_Device_Resolution(int &width, int &height, int &refresh,
		bool &windowed);
};

struct GlobalData
{
	char m_pad[0xe55];
	unsigned char m_resolutionFlag;
};

extern GlobalData *TheWritableGlobalData;

class TextureClass
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudFilter : public Gen_00920a60
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();

	TextureClass *m_texture;
};

class Rva0090E250
{
public:
	void set(int value);

	void *m_inner;
};

// The body at 0x00787D80 is the matched 4-byte hash_map subscript that the
// 0x00027E30 thunk reaches.  The value is used here only as an ABI surrogate:
// this address-derived owner is not being claimed to be Player or to own a
// relationship map.
enum Relationship
{
	BfmeLookupValue0 = 0,
	BfmeLookupValue1,
	BfmeLookupValue2
};

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> >
	BfmeLookupMap;

struct BfmeTextureEntry
{
	void *m_vftable;
	ShroudFilter *m_filter;
};

extern "C" __declspec(dllimport) int __cdecl sscanf(
	const char *text, const char *format, ...);

extern void *operator new(unsigned int bytes);

class Gen_004410A0
{
public:
	void bfmeRun(void);

private:
	void bfmeStep1(void);					// ILT 0x000459CB
	void bfmeStep2(void);					// ILT 0x0000B613
	void bfmeStep3(void);					// ILT 0x0002E8CA
};

class Gen_0077F000
{
public:
	void bfmeRun(void);

private:
	void bfmeStep1(void);					// ILT 0x00039428
	void bfmeStep2(void);					// ILT 0x0002398E
	void bfmeStep3(void);					// ILT 0x0001B32E
};

class Gen_007892D0
{
public:
	void bfmeRun(void);

private:
	BFMERetailAsciiString m_bfmeName;
	char m_bfmeGap04[4];
	BfmeLookupMap m_bfmeLookup;

	void bfmeStep1(void);					// ILT 0x000270FC
	void bfmeStep2(void);					// ILT 0x0003879E
	void bfmeStep3(void);					// ILT 0x0004264A
};

struct BfmeRefBlock
{
	unsigned short m_bfmeRefCount;				// +0x00
};

struct BfmeReleaseTable
{
	void (*m_bfmeReserved)(void *block);			// +0x00
	void (*m_bfmeRelease)(void *block);			// +0x04
};

extern BfmeReleaseTable *TheBfmeReleaseTable;			// 0x01337A30

class Gen_00891B80
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

class Gen_00892890
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

class Gen_008AD330
{
public:
	void bfmeRelease(void);

private:
	BfmeRefBlock *m_bfmeBlock;
};

extern void (*TheBfmeBufferFree)(void *buffer, int bytes);	// 0x01337830

class Gen_008A0D60
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

class Gen_008C5B30
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

class Gen_008C5C00
{
public:
	void bfmeFreeBuffer(void);

private:
	char m_bfmeHead[4];
	int m_bfmeCount;					// +0x04
	void *m_bfmeBuffer;					// +0x08
};

// ?bfmeRun@Gen_004410A0@@QAEXXZ
void Gen_004410A0::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeRun@Gen_0077F000@@QAEXXZ
void Gen_0077F000::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeRun@Gen_007892D0@@QAEXXZ
void Gen_007892D0::bfmeRun(void)
{
	bfmeStep1();
	bfmeStep2();
	bfmeStep3();
}

// ?bfmeStep2@Gen_007892D0@@AAEXXZ
//
// The owner remains address-derived: the caller/ILT proves this method's
// identity, while the first member, the +8 lookup object, and the callees below
// are the only layout facts used here.  In particular, the four-byte map value
// is treated as an ABI slot for the matched subscript body, not named as a
// recovered game concept.
void Gen_007892D0::bfmeStep2(void)
{
	BFMERetailAsciiString dataName(m_bfmeName);
	dataName.concat(".dat", 4);

	File *file;
	{
		BFMERetailAsciiString openName(dataName.str());
		file = Open2OpenPastSeparators(
			*(const AsciiString *)&openName);
	}

	if (file == 0)
		return;

	int width;
	int height;
	int refresh;
	bool unusedWindowed;
	DX8Wrapper::Get_Device_Resolution(width, height, refresh, unusedWindowed);
	unsigned char windowed = TheWritableGlobalData->m_resolutionFlag;
	if (width == 0x400)
		windowed = !windowed;
	int one = 1;

	for (;;)
	{
		if (file->eof())
		{
			file->close();
			break;
		}

		char line[0x400];
		line[0x3ff] = 0;
		file->nextLine(line, 0x3ff);
		if (line[0] == ';')
			continue;

		BFMERetailAsciiString textureName;
		int first;
		int second;
		int index;

		if (sscanf(line, "%d->%d", &first, &second) == 2)
		{
			index = second;
		}
		else if (sscanf(line, "%d", &first) != one)
		{
			continue;
		}
		else
		{
			index = first;
		}

		textureName.format(
			BFMERetailAsciiString("apt_%s_%d.tga"),
			m_bfmeName.str(), index);

		{
			BFMEWaterTrackTextureHandle texture =
				BFMEGetWaterTrackTexture((char *)textureName.str(), 1, 0);
			Rva0090E250 *settings = (Rva0090E250 *)&texture;
			settings->set(2);

			ShroudTexture *surface = (ShroudTexture *)&texture;
			if (windowed)
			{
				surface->getFilter()->m_04 = one;
				surface->getFilter()->m_00 = one;
			}
			else
			{
				surface->getFilter()->m_04 = 3;
				surface->getFilter()->m_00 = 3;
			}
			ShroudFilter *filter = surface->getFilter();
			filter->m(windowed ? one : 3);
			filter->m_0c = one;
			filter->m_10 = one;

			BfmeTextureEntry *entry =
				(BfmeTextureEntry *)operator new(8);
			if (entry != 0)
			{
				entry->m_vftable = (void *)0x01126ab8;
				entry->m_filter = filter;
				if (filter != 0)
					++*(unsigned short *)((char *)filter + 4);
			}

			Relationship &slot = m_bfmeLookup[index];
			*(void **)&slot = entry;
		}
	}
}

// ?bfmeRelease@Gen_00891B80@@QAEXXZ
void Gen_00891B80::bfmeRelease(void)
{
	BfmeRefBlock *block = m_bfmeBlock;

	--block->m_bfmeRefCount;

	if (block->m_bfmeRefCount == 0)
		TheBfmeReleaseTable->m_bfmeRelease(block);
}

// ?bfmeRelease@Gen_00892890@@QAEXXZ
void Gen_00892890::bfmeRelease(void)
{
	BfmeRefBlock *block = m_bfmeBlock;

	--block->m_bfmeRefCount;

	if (block->m_bfmeRefCount == 0)
		TheBfmeReleaseTable->m_bfmeRelease(block);
}

// ?bfmeRelease@Gen_008AD330@@QAEXXZ
void Gen_008AD330::bfmeRelease(void)
{
	BfmeRefBlock *block = m_bfmeBlock;

	--block->m_bfmeRefCount;

	if (block->m_bfmeRefCount == 0)
		TheBfmeReleaseTable->m_bfmeRelease(block);
}

// ?bfmeFreeBuffer@Gen_008A0D60@@QAEXXZ
void Gen_008A0D60::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}

// ?bfmeFreeBuffer@Gen_008C5B30@@QAEXXZ
void Gen_008C5B30::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}

// ?bfmeFreeBuffer@Gen_008C5C00@@QAEXXZ
void Gen_008C5C00::bfmeFreeBuffer(void)
{
	if (m_bfmeBuffer)
		TheBfmeBufferFree(m_bfmeBuffer, m_bfmeCount * 4);
}
