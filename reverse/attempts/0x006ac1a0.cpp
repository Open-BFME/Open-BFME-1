// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.43 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB

// Open-BFME5: readable reconstruction of AudioManager's music-event probe.
// Retail walks the BFME audio-name hash table at this+0x70, selects the first
// event whose sound-type field is zero and whose player-mask bits are clear,
// then constructs an AudioEventRTS from that node's AsciiString key.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}
};

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

struct AudioEventInfo
{
	virtual ~AudioEventInfo();
	long m_refCount;
	char m_pad08[0x30];
	UnsignedInt m_type;                  // +0x38
	char m_pad3c[0x48];
	UnsignedInt m_soundType;             // +0x84
};

class AudioEventInfoRef
{
public:
	explicit AudioEventInfoRef(AudioEventInfo *info) : m_ptr(info)
	{
		InterlockedIncrement(&m_ptr->m_refCount);
	}

	~AudioEventInfoRef()
	{
		if (m_ptr && InterlockedDecrement(&m_ptr->m_refCount) <= 0)
			delete m_ptr;
	}

private:
	AudioEventInfo *m_ptr;
};

namespace rts
{
template <class T> struct hash;

template <> struct hash<AsciiString>
{
	UnsignedInt operator()(const AsciiString &) const;
};
}

class Rva006AEE00Hashtable
{
public:
	struct BucketVector
	{
		void **m_start;
		void **m_finish;
		void **m_end;

		UnsignedInt size() const
		{
			return static_cast<UnsignedInt>(m_finish - m_start);
		}

		void *operator[](UnsignedInt index) const
		{
			return m_start[index];
		}
	};

	struct Value
	{
		AsciiString first;
		AudioEventInfo *second;
	};

	struct Node
	{
		Node *next;
		Value value;
	};

	struct Iterator
	{
		Node *current;
		Rva006AEE00Hashtable *table;
	};

	Iterator begin();

	UnsignedInt bucketCount() const
	{
		return m_buckets.size();
	}

	UnsignedInt bucketNumber(const AsciiString &key) const
	{
		return rts::hash<AsciiString>()(key) % bucketCount();
	}

	Node *next(Node *current) const
	{
		if (current->next)
			return current->next;

		UnsignedInt bucket = bucketNumber(current->value.first);
		UnsignedInt count = bucketCount();
		Node *result = 0;
		while (result == 0 && ++bucket < count)
			result = reinterpret_cast<Node *>(m_buckets[bucket]);
		return result;
	}

	char m_pad00[4];
	BucketVector m_buckets;
	UnsignedInt m_count;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	~AudioEventRTS();
	void generateFilename();
	AsciiString getFilename();

private:
	void *m_vtable;
	AsciiString m_filenameToLoad;
	void *m_eventInfo;
	UnsignedInt m_playingHandle;
	UnsignedInt m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	char m_pad20[0x4c];
};

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

class __declspec(novtable) AudioManager
{
public:
	virtual bool isMusicAlreadyLoaded() const;
};

// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
bool AudioManager::isMusicAlreadyLoaded() const
{
	Rva006AEE00Hashtable::Node *musicToLoad = 0;
	Rva006AEE00Hashtable::Iterator it =
		reinterpret_cast<Rva006AEE00Hashtable *>(
			reinterpret_cast<char *>(const_cast<AudioManager *>(this)) + 0x70)->begin();
	Rva006AEE00Hashtable::Node *current = it.current;
	Rva006AEE00Hashtable *table = it.table;

	while (current)
	{
		AudioEventInfo *info = current->value.second;
		if (info)
		{
			AudioEventInfoRef hold(info);
			if (info->m_soundType == 0 && (info->m_type & 0x600) == 0)
				musicToLoad = current;
		}
		current = table->next(current);
		if (musicToLoad)
			break;
	}

	if (!musicToLoad)
		return false;

	AsciiString eventName(musicToLoad->value.first);
	AudioEventRTS event(eventName, 2);
	event.generateFilename();
	AsciiString filename = event.getFilename();
	return TheFileSystem->doesFileExist(filename.str());
}
