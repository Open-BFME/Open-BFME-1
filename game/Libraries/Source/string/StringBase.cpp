// cl: /DNDEBUG /MD /EHs-c-
// readable body of ??1AIUpdateModuleData@@: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ??4AudioEventRTS@@: game/GameEngine/Source/Common/Audio/AudioEventRTS.cpp
// readable body of ?format_va@AsciiString@@: game/GameEngine/Source/Common/System/AsciiString.cpp
// readable body of ?format_va@UnicodeString@@: game/GameEngine/Source/Common/System/UnicodeString.cpp
// readable body of ?freeBytes@AsciiString@@: game/GameEngine/Source/Common/System/AsciiString.cpp
// readable body of ?set@UnicodeString@@: game/GameEngine/Source/Common/System/UnicodeString.cpp
#include "../WWVegas/WWLib/string_base.h"

// The original translation unit linked the dynamic CRT, so CRT calls that are
// not compiler intrinsics (e.g. wcslen) go through the import table. Defining
// _DLL before the CRT headers reproduces that dllimport linkage.
#define _DLL
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

class DebugStringOutputShim
{
public:
    virtual void pad00();
    virtual void pad01();
    virtual void pad02();
    virtual void pad03();
    virtual void pad04();
    virtual void pad05();
    virtual void pad06();
    virtual void pad07();
    virtual void pad08();
    virtual void pad09();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual DebugStringOutputShim &write(const char *text);
};

static int stringLength(const char *s)
{
    return (int)strlen(s);
}

static int stringLength(const wchar_t *s)
{
    return (int)wcslen(s);
}

// Retail compares wide strings through a temporary traits functor (the this
// pointer lands in a dead parameter slot); the member is the 0x0005C4B0 body.
struct Rva0005C4B0WideTraits
{
    int compare(const wchar_t *a, const wchar_t *b, int len);
};
// The no-case wide compare is the private StringBase<wchar_t>::compareNoCaseRaw
// body at 0x0009ECA0, reached the same way; the length-aware compare at
// 0x0005DC70 is a five-argument cdecl helper (the last argument selects case
// folding). A null m_data reads str()'s TheNullChr (exported at 0x00C7388C).
struct Rva0009ECA0NoCaseTraits
{
    int compareNoCaseRaw(const wchar_t *a, const wchar_t *b, int len) const;
};
struct Rva0005DC70Flags
{
    bool noCase;
};
int __cdecl Rva0005DC70CompareWideLengths(const wchar_t *a, int aLen, const wchar_t *b, int bLen, Rva0005DC70Flags flags);


// Per-character-type buffer lock. Retail guards each instantiation's shared
// buffers with its own critical-section singleton: 0x008876E0 for char and
// 0x008877A0 for wchar_t. Both standalone copies and their .text$yd atexit
// thunks (0x00C70EE0, 0x00C70EC0) are this object's; the getters are inlined
// into every user here. The
// imports are retail's KERNEL32 IAT cells (imports.csv): 0x01358E4C
// InitializeCriticalSection, 0x01358D0C DeleteCriticalSection, 0x01358D18
// EnterCriticalSection, 0x01358E74 LeaveCriticalSection; the buffer release
// calls MSVCR71 free (0x013593D4).
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

class Rva008877A0Type
{
public:
	char m_pad0[0x18];
	bool m_flag18;

	Rva008877A0Type()
	{
		m_flag18 = true;
		InitializeCriticalSection(this);
	}
	~Rva008877A0Type()
	{
		DeleteCriticalSection(this);
		m_flag18 = false;
	}
};

class Rva008876E0Type
{
public:
	char m_pad0[0x18];
	bool m_flag18;

	Rva008876E0Type()
	{
		m_flag18 = true;
		InitializeCriticalSection(this);
	}
	~Rva008876E0Type()
	{
		DeleteCriticalSection(this);
		m_flag18 = false;
	}
};

inline void *getRva008877A0Singleton()
{
	static Rva008877A0Type obj;
	return &obj;
}

inline void *getRva008876E0Singleton()
{
	static Rva008876E0Type obj;
	return &obj;
}

template <typename T> struct StringBaseLock;
template <> struct StringBaseLock<char>
{
	typedef Rva008876E0Type Type;
	static Type *get() { return (Type *)getRva008876E0Singleton(); }
};
template <> struct StringBaseLock<wchar_t>
{
	typedef Rva008877A0Type Type;
	static Type *get() { return (Type *)getRva008877A0Singleton(); }
};

template <typename L>
class StringBaseScopedLock
{
public:
	StringBaseScopedLock(L *lock) : m_lock(lock)
	{
		if (m_lock->m_flag18)
			EnterCriticalSection(m_lock);
	}
	~StringBaseScopedLock()
	{
		if (m_lock->m_flag18)
			LeaveCriticalSection(m_lock);
	}

private:
	L *m_lock;
};

template <typename T>
void StringBase<T>::releaseBuffer()
{
	StringBaseScopedLock<typename StringBaseLock<T>::Type> lock(StringBaseLock<T>::get());
	if (m_data)
	{
		if (--m_data->ref_count == 0)
			free(m_data);
		m_data = 0;
	}
}

template <typename T>
StringBase<T>::StringBase(const StringBase<T> &src)
{
	StringBaseScopedLock<typename StringBaseLock<T>::Type> lock(StringBaseLock<T>::get());
	m_data = src.m_data;
	if (m_data)
		++m_data->ref_count;
}

template <typename T>
void StringBase<T>::set(const StringBase<T> &src)
{
	StringBaseScopedLock<typename StringBaseLock<T>::Type> lock(StringBaseLock<T>::get());
	if (&src != this)
	{
		releaseBuffer();
		m_data = src.m_data;
		if (m_data)
			++m_data->ref_count;
	}
}

// Retail 0x008881B0 / 0x00888A90 (exports 594, 595), inside this block.
template <typename T>
StringBase<T> &StringBase<T>::operator=(const StringBase<T> &src)
{
	set(src);
	return *this;
}

template <typename T>
StringBase<T>::StringBase(const T *str)
{
	m_data = 0;
	int len = str ? stringLength(str) : 0;
	if (m_data != 0 && str == &m_data->data[0])
		return;
	if (len != 0)
		ensureUniqueBufferOfSize(len, false, str, len, 0, 0);
	else
		releaseBuffer();
}

template <typename T>
void StringBase<T>::set(const StringBase<T> &src, int start, int len)
{
	if (start + len < 0 || start >= src.getLength())
	{
		releaseBuffer();
		return;
	}
	if (start < 0)
	{
		len += start;
		start = 0;
	}
	if (start + len >= src.getLength())
		len = src.getLength() - start;

	const T *str = src.str() + start;
	if (m_data != 0 && str == &m_data->data[0])
		return;
	if (len != 0)
		ensureUniqueBufferOfSize(len, false, str, len, 0, 0);
	else
		releaseBuffer();
}


template <typename T>
void StringBase<T>::debugIgnoreLeaks()
{
}

template <typename T>
bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template <typename T>
bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *start = m_data ? &m_data->data[0] : (const T *)"";
    const T *end = start + (m_data ? m_data->length : 0);

    for (const T *p = start; p != end; ++p) {
        if (*p == c) {
            return p;
        }
    }

    return 0;
}

template <typename T>
T StringBase<T>::getCharAt(int index) const
{
    return m_data ? m_data->data[index] : 0;
}

// Retail's copies of compare, compareNoCase, concat(const StringBase &),
// startsWith/startsWithNoCase(const char *, const StringBase<char> &) and
// endsWith(const char *) lie outside this file's block (0x00887080-0x00888F84):
// header-inline COMDATs that other TUs emitted. Inline here as well, so this
// object's copies are SELECT_ANY rather than exclusive definitions that collide
// with theirs. noinline keeps the out-of-line calls retail's callers make.
template <>
inline __declspec(noinline) int StringBase<char>::compare(const char *str) const
{
    const int strLen = str ? stringLength(str) : 0;
    const int len = m_data ? m_data->length : 0;
    const char *data = m_data ? &m_data->data[0] : "";
    int result = memcmp(data, str, len < strLen ? len : strLen);
    if (result == 0) {
        result = len - strLen;
    }
    return result;
}



template <typename T>
void StringBase<T>::concat(T c)
{
    concat(&c, 1);
}

template <typename T>
const T *StringBase<T>::reverseFind(T c) const
{
    const T *start = m_data ? &m_data->data[0] : (const T *)"";
    const T *p = start + (m_data ? m_data->length : 0);

    while (p != start) {
        --p;
        if (*p == c) {
            return p;
        }
    }

    return 0;
}

template <>
inline int StringBase<char>::compare(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return compare(data, len);
}

template <>
inline int StringBase<char>::compare(const char *str, int len) const
{
    const int myLen = m_data ? m_data->length : 0;
    const char *data = m_data ? &m_data->data[0] : "";
    int result = memcmp(data, str, myLen < len ? myLen : len);
    if (result == 0) {
        result = myLen - len;
    }
    return result;
}

template <>
inline int StringBase<wchar_t>::compare(const wchar_t *str, int len) const
{
    Rva0005DC70Flags flags;
    flags.noCase = false;
    const int myLen = m_data ? m_data->length : 0;
    const wchar_t *data = this->str();
    return Rva0005DC70CompareWideLengths(data, myLen, str, len, flags);
}

template <>
inline __declspec(noinline) int StringBase<wchar_t>::compare(const StringBase<wchar_t> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.str();
    return compare(data, len);
}

template <>
inline __declspec(noinline) int StringBase<wchar_t>::compare(const wchar_t *str) const
{
    return compare(str, str ? stringLength(str) : 0);
}




template <>
inline int StringBase<char>::compareNoCase(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return compareNoCase(data, len);
}

template <>
inline int StringBase<char>::compareNoCase(const char *str) const
{
    return compareNoCase(str, str ? stringLength(str) : 0);
}

template <>
inline int StringBase<char>::compareNoCase(const char *str, int len) const
{
    const int myLen = m_data ? m_data->length : 0;
    const char *data = m_data ? &m_data->data[0] : "";
    int result = _memicmp(data, str, myLen < len ? myLen : len);
    if (result == 0) {
        result = myLen - len;
    }
    return result;
}

template <>
inline int StringBase<wchar_t>::compareNoCase(const wchar_t *str, int len) const
{
    const int myLen = m_data ? m_data->length : 0;
    const wchar_t *data = this->str();
    Rva0009ECA0NoCaseTraits traits;
    int result = traits.compareNoCaseRaw(data, str, myLen < len ? myLen : len);
    if (result == 0) {
        result = myLen - len;
    }
    return result;
}

template <>
inline __declspec(noinline) int StringBase<wchar_t>::compareNoCase(const StringBase<wchar_t> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.str();
    return compareNoCase(data, len);
}

template <>
inline __declspec(noinline) int StringBase<wchar_t>::compareNoCase(const wchar_t *str) const
{
    return compareNoCase(str, str ? stringLength(str) : 0);
}




template <>
bool StringBase<char>::endsWith(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return endsWith(data, len);
}

// The retail build does not inline endsWith(const char *, int) here but does
// inline it into the StringBase overload below, so the depth has to be turned
// off around this one call site rather than on the callee.
#pragma inline_depth(0)
template <>
inline __declspec(noinline) bool StringBase<char>::endsWith(const char *str) const
{
    return endsWith(str, str ? (int)strlen(str) : 0);
}
#pragma inline_depth()

template <>
bool StringBase<char>::endsWith(const char *str, int len) const
{
    if (str[0] == '\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    int length = m_data ? m_data->length : 0;
    const char *addr = (const char *)m_data - len + length + 8;
    return memcmp(addr, str, len) == 0;
}


bool StringBase<wchar_t>::endsWith(const wchar_t *str, int len) const
{
    if (str[0] == L'\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    int length = m_data ? m_data->length : 0;
    const wchar_t *addr = &m_data->data[length - len];
    Rva0005C4B0WideTraits traits;
    return traits.compare(addr, str, len) == 0;
}

bool StringBase<wchar_t>::endsWith(const StringBase<wchar_t> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.str();
    return endsWith(data, len);
}




template <>
__declspec(noinline) bool StringBase<char>::endsWithNoCase(const char *str, int len) const
{
    if (str[0] == '\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    int length = m_data ? m_data->length : 0;
    const char *addr = (const char *)m_data - len + length + 8;
    return _memicmp(addr, str, len) == 0;
}


bool StringBase<wchar_t>::endsWithNoCase(const wchar_t *str, int len) const
{
    if (str[0] == L'\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    int length = m_data ? m_data->length : 0;
    const wchar_t *addr = &m_data->data[length - len];
    Rva0009ECA0NoCaseTraits traits;
    return traits.compareNoCaseRaw(addr, str, len) == 0;
}


template <typename T>
void StringBase<T>::ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1, int src1Len, const T *src2, int src2Len)
{
	if (m_data)
	{
		if (m_data->capacity > newLen)
		{
			if (m_data->ref_count == 1)
			{
				if (src1)
				{
					memcpy(m_data->data, src1, src1Len * sizeof(T));
					m_data->length = src1Len;
				}
				if (src2)
				{
					memcpy(m_data->data + m_data->length, src2, src2Len * sizeof(T));
					m_data->length += src2Len;
				}
				m_data->data[m_data->length] = 0;
				return;
			}
		}
		else if (src2)
		{
			unsigned grown = m_data->capacity + m_data->capacity / 2;
			if ((int)grown - 1 > newLen)
				newLen = (int)grown - 1;
		}
	}

	int bytes = sizeof(int) + 2 * sizeof(unsigned short) + (newLen + 1) * sizeof(T);
	if (bytes > 0x7fff)
		throw 1;
	bytes = (bytes + 3) / 4 * 4;

	Header *newData = (Header *)malloc(bytes);
	newData->ref_count = 1;
	newData->capacity = (unsigned short)((bytes - 8) / sizeof(T));
	if (m_data && keepData)
	{
		memcpy(newData->data, m_data->data, m_data->length * sizeof(T));
		newData->length = m_data->length;
	}
	else
	{
		newData->length = 0;
	}
	if (src1)
	{
		memcpy(newData->data, src1, src1Len * sizeof(T));
		newData->length = src1Len;
	}
	if (src2)
	{
		memcpy(newData->data + newData->length, src2, src2Len * sizeof(T));
		newData->length += src2Len;
	}
	newData->data[newData->length] = 0;

	releaseBuffer();
	m_data = newData;
}


// Retail 00887BE0/00888480 allocates a fresh buffer when capacity or
// uniqueness is insufficient, then sets the requested length and terminator.
// Allocation includes the eight-byte header and rounds to a four-byte boundary.
// The bound failure throws int(1), matching retail ThrowInfo VA 012454C0.
// Volatile initialization preserves the retail header-store order before
// releaseBuffer; it does not change the Header layout or sharing contract.
template <typename T>
T *StringBase<T>::getBufferForRead(int len)
{
	if (m_data == 0 || m_data->capacity <= len || m_data->ref_count != 1)
	{
		int bytes = (len + 1) * (int)sizeof(T) + 8;
		if (bytes > 32767)
			throw 1;
		bytes = ((bytes + 3) / 4) * 4;
		Header *data = (Header *)malloc(bytes);
		((volatile int *)&data->ref_count)[0] = 1;
		((volatile unsigned short *)&data->capacity)[0] = (unsigned short)((bytes - 8) / sizeof(T));
		((volatile unsigned short *)&data->length)[0] = 0;
		((volatile T *)&data->data[0])[0] = 0;
		releaseBuffer();
		m_data = data;
	}
	else
	{
		m_data->data[m_data->length] = 0;
	}
	if (m_data)
	{
		m_data->length = (unsigned short)len;
		m_data->data[len] = 0;
	}
	return &m_data->data[0];
}



bool StringBase<wchar_t>::startsWith(const wchar_t *str, int len) const
{
    if (str[0] == L'\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    Rva0005C4B0WideTraits traits;
    return traits.compare(&m_data->data[0], str, len) == 0;
}

bool StringBase<wchar_t>::startsWith(const StringBase<wchar_t> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    return startsWith(data, len);
}

bool StringBase<wchar_t>::startsWith(const wchar_t *str) const
{
    return startsWith(str, str ? stringLength(str) : 0);
}




__declspec(noinline) bool StringBase<char>::startsWithNoCase(const char *str, int len) const
{
    if (str[0] == '\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    const char *data = &m_data->data[0];
    return _memicmp(data, str, len) == 0;
}


bool StringBase<wchar_t>::startsWithNoCase(const wchar_t *str, int len) const
{
    if (str[0] == L'\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    Rva0009ECA0NoCaseTraits traits;
    return traits.compareNoCaseRaw(&m_data->data[0], str, len) == 0;
}

bool StringBase<wchar_t>::startsWithNoCase(const StringBase<wchar_t> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    return startsWithNoCase(data, len);
}

bool StringBase<wchar_t>::startsWithNoCase(const wchar_t *str) const
{
    return startsWithNoCase(str, str ? stringLength(str) : 0);
}




template <typename T>
void StringBase<T>::concat(const T *str)
{
    concat(str, str ? stringLength(str) : 0);
}

template <typename T>
bool StringBase<T>::endsWith(const T *str) const
{
    return endsWith(str, str ? stringLength(str) : 0);
}

template <typename T>
bool StringBase<T>::endsWithNoCase(const T *str) const
{
    return endsWithNoCase(str, str ? stringLength(str) : 0);
}

template <typename T>
void StringBase<T>::set(const T *str)
{
    set(str, str ? stringLength(str) : 0);
}

template <typename T>
bool StringBase<T>::isNone() const
{
    // The compile-time-constant condition folds away, leaving one literal push of
    // the correct element type for each instantiation ("None" / L"None").
    return compareNoCase(sizeof(T) == 1 ? (const T *)"None" : (const T *)L"None") == 0;
}

template <typename T>
void __cdecl StringBase<T>::format(const T *fmt, ...)
{
    format_va(fmt, (char *)(&fmt + 1));
}

template <typename T>
__declspec(noinline) void StringBase<T>::set(const T *str, int len)
{
    if (m_data != 0 && str == &m_data->data[0])
        return;
    if (len != 0)
        ensureUniqueBufferOfSize(len, false, str, len, 0, 0);
    else
        releaseBuffer();
}

template <typename T>
__declspec(noinline) void StringBase<T>::concat(const T *str, int len)
{
    if (len == 0)
        return;
    if (m_data != 0)
        ensureUniqueBufferOfSize(m_data->length + len, true, 0, 0, str, len);
    else
        ensureUniqueBufferOfSize(len, false, str, len, 0, 0);
}

template <typename T>
void StringBase<T>::format_va(const StringBase<T> &fmt, char *args)
{
    format_va(fmt.str(), args);
}

template <typename T>
bool StringBase<T>::isNotNone() const
{
    return compareNoCase(sizeof(T) == 1 ? (const T *)"None" : (const T *)L"None") != 0;
}

template <typename T>
void StringBase<T>::set(T c)
{
    set(&c, 1);
}

void StringBase<char>::trim()
{
	if (m_data)
	{
		// strip leading white space
		char *c = peek();
		while (*c && isspace(*c))
			++c;
		if (c != peek())
		{
			int len = getLength() - (int)(c - peek());
			if (len != 0)
				ensureUniqueBufferOfSize(len, false, c, len, 0, 0);
			else
				releaseBuffer();
		}

		// clip trailing white space
		if (m_data)
		{
			for (int index = m_data->length; index > 0; )
			{
				--index;
				if (!isspace(getCharAt(index)))
					break;
				removeLastChar();
			}
		}
	}
}

template class StringBase<char>;
template class StringBase<wchar_t>;

bool operator<(const StringBase<char> &left, const StringBase<char> &right)
{
    return left.compare(right) < 0;
}

bool operator<(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
{
    return left.compare(right) < 0;
}

bool operator!=(const StringBase<char> &left, const char *right)
{
    return left.compare(right) != 0;
}

bool operator==(const StringBase<char> &left, const char *right)
{
    return left.compare(right) == 0;
}

bool operator==(const StringBase<char> &left, const StringBase<char> &right)
{
    return left.compare(right) == 0;
}

bool operator==(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
{
    return left.compare(right) == 0;
}

bool operator!=(const StringBase<char> &left, const StringBase<char> &right)
{
    return left.compare(right) != 0;
}

bool operator!=(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
{
    return left.compare(right) != 0;
}

Debug &operator<<(Debug &debug, const StringBase<char> &str)
{
    DebugStringOutputShim &output = *(DebugStringOutputShim *)&debug;
    output.write(str.str());
    return debug;
}

template <>
bool operator!=<char>(const char *left, const StringBase<char> &right)
{
    return right.compare(left) != 0;
}

template <>
__declspec(noinline) bool StringBase<char>::startsWith(const char *str, int len) const
{
    if (str[0] == '\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    return memcmp(&m_data->data[0], str, len) == 0;
}

template <>
inline __declspec(noinline) bool StringBase<char>::startsWith(const char *str) const
{
    return startsWith(str, str ? stringLength(str) : 0);
}

template <>
inline __declspec(noinline) bool StringBase<char>::startsWith(const StringBase<char> &str) const
{
    int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? str.m_data->data : "";
    return startsWith(data, len);
}
template <>
inline __declspec(noinline) bool StringBase<char>::startsWithNoCase(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return startsWithNoCase(data, len);
}

template <>
inline __declspec(noinline) void StringBase<char>::concat(const StringBase<char> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    concat(data, len);
}

template <>
inline __declspec(noinline) void StringBase<wchar_t>::concat(const StringBase<wchar_t> &str)
{
    const int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    concat(data, len);
}

bool StringBase<char>::endsWithNoCase(const StringBase<char> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const char *data = str.m_data ? &str.m_data->data[0] : "";
    return endsWithNoCase(data, len);
}

template <>
inline __declspec(noinline) bool StringBase<char>::startsWithNoCase(const char *str) const
{
    return startsWithNoCase(str, str ? stringLength(str) : 0);
}

bool StringBase<wchar_t>::endsWithNoCase(const StringBase<wchar_t> &str) const
{
    const int len = str.m_data ? str.m_data->length : 0;
    const wchar_t *data = str.m_data ? &str.m_data->data[0] : L"";
    return endsWithNoCase(data, len);
}
