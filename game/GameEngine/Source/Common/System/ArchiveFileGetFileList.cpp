// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "Common/GameMemory.h"

#ifndef BFME_ARCHIVEFILE_STRINGBASE_H
#define BFME_ARCHIVEFILE_STRINGBASE_H

class AsciiString;
class UnicodeString;
class BFMERetailAsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
    friend class BFMERetailAsciiString;

public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int getLength() const;
    const T *str() const;
    const T *find(T c) const;
    T getCharAt(int index) const;
    StringBase<T> &operator=(const StringBase<T> &src);
    int compare(const StringBase<T> &str) const;
    int compare(const T *str) const;
    int compare(const T *str, int len) const;
    int compareNoCase(const StringBase<T> &str) const;
    int compareNoCase(const T *str) const;
    int compareNoCase(const T *str, int len) const;
    void concat(const StringBase<T> &str);
    void concat(T c);
    void concat(const T *str);
    void concat(const T *str, int len);
    const T *reverseFind(T c) const;
    bool startsWith(const StringBase<T> &str) const;
    bool startsWith(const T *str) const;
    bool startsWith(const T *str, int len) const;
    bool startsWithNoCase(const StringBase<T> &str) const;
    bool startsWithNoCase(const T *str) const;
    bool startsWithNoCase(const T *str, int len) const;
    bool endsWith(const StringBase<T> &str) const;
    bool endsWith(const T *str) const;
    bool endsWith(const T *str, int len) const;
    bool endsWithNoCase(const StringBase<T> &str) const;
    bool endsWithNoCase(const T *str) const;
    bool endsWithNoCase(const T *str, int len) const;
    void set(const StringBase<T> &src);
    void set(const StringBase<T> &src, int start, int len);
    void set(T c);
    void set(const T *str);
    void set(const T *str, int len);
    void swap(StringBase<T> &other);
    void clear();
    void __cdecl format(const T *fmt, ...);
    void format_va(const StringBase<T> &fmt, char *args);
    void format_va(const T *fmt, char *args);
    T *getBufferForRead(int len);
    bool nextToken(StringBase<T> *out, const T *delimiters);
    void removeLastChar();
    void toLower();
    void toUpper();
    void trim();

private:
    StringBase() : m_data(0) {}
    StringBase(T c);
    StringBase(const T *str);
    StringBase(const T *str, int len);
    StringBase(const StringBase<T> &src);
    StringBase(const StringBase<T> &src, int start, int len);
    ~StringBase() {}
    void validate() const;
    T *peek() const;
    void releaseBuffer();
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1,
                                  int src1Len, const T *src2, int src2Len);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

template <typename T>
bool operator<(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator==(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const T *right);

class Debug;
Debug &operator<<(Debug &debug, const StringBase<char> &str);

template <typename T>
bool operator!=(const T *left, const StringBase<T> &right);

#endif

#ifndef ASCIISTRING_H
#define ASCIISTRING_H

extern "C" int __cdecl memcmp(const void *buf, const void *other, unsigned int count);
#pragma intrinsic(memcmp)

class UnicodeString;

class AsciiString
{
public:
    AsciiString() { m_text = 0; }
    AsciiString(char c);
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }
    AsciiString(const char *str)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(str);
    }
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
        return *this;
    }
    AsciiString &operator=(char c);
    AsciiString &operator=(const char *str);
    AsciiString &operator=(const UnicodeString &that);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char c);
    AsciiString &operator+=(const char *str);
    AsciiString &operator+=(const UnicodeString &that);
    void __cdecl format(AsciiString fmt, ...);
    void translate(const UnicodeString &that);
    const char *str() const { return ((const StringBase<char> *)this)->str(); }
    int getLength() const { return ((const StringBase<char> *)this)->getLength(); }
    char getCharAt(int i) const { return ((const StringBase<char> *)this)->getCharAt(i); }
    bool isEmpty() const { return ((const StringBase<char> *)this)->isEmpty(); }
    bool isNotEmpty() const { return ((const StringBase<char> *)this)->isNotEmpty(); }
    bool isNone() const { return ((const StringBase<char> *)this)->isNone(); }
    bool isNotNone() const { return ((const StringBase<char> *)this)->isNotNone(); }
    const char *reverseFind(char c) const { return ((const StringBase<char> *)this)->reverseFind(c); }
    bool nextToken(AsciiString *out, const char *delims = 0)
    {
        return ((StringBase<char> *)this)->nextToken((StringBase<char> *)out, delims);
    }
    void clear() { ((StringBase<char> *)this)->clear(); }
    void set(const char *s) { ((StringBase<char> *)this)->set(s); }
    void set(const AsciiString &s) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&s); }
    void concat(const char *s) { ((StringBase<char> *)this)->concat(s); }
    void concat(char c) { ((StringBase<char> *)this)->concat(c); }
    void concat(const AsciiString &s) { ((StringBase<char> *)this)->concat(*(const StringBase<char> *)&s); }
    void toLower() { ((StringBase<char> *)this)->toLower(); }
    void toUpper() { ((StringBase<char> *)this)->toUpper(); }
    void trim() { ((StringBase<char> *)this)->trim(); }
    void removeLastChar() { ((StringBase<char> *)this)->removeLastChar(); }
    const char *find(char c) const { return ((const StringBase<char> *)this)->find(c); }
    bool startsWith(const char *p) const { return ((const StringBase<char> *)this)->startsWith(p); }
    bool startsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->startsWithNoCase(p); }
    bool endsWith(const char *p) const { return ((const StringBase<char> *)this)->endsWith(p); }
    bool endsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->endsWithNoCase(p); }
    int compare(const char *p) const { return ((const StringBase<char> *)this)->compare(p); }
    int compareNoCase(const char *p) const { return ((const StringBase<char> *)this)->compareNoCase(p); }
    int compare(const AsciiString &s) const
    {
        const StringBase<char> *self = (const StringBase<char> *)this;
        const StringBase<char> *that = (const StringBase<char> *)&s;
        int thatLen = that->m_data ? that->m_data->length : 0;
        const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
        int thisLen = self->m_data ? self->m_data->length : 0;
        const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
        int n = thisLen < thatLen ? thisLen : thatLen;
        int c = memcmp(thisData, thatData, n);
        if (c != 0)
            return c;
        return thisLen - thatLen;
    }
    int compareNoCase(const AsciiString &s) const
    {
        return ((const StringBase<char> *)this)->compareNoCase(*(const StringBase<char> *)&s);
    }

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b)
{
    return *(const StringBase<char> *)&a == *(const StringBase<char> *)&b;
}
inline bool operator!=(const AsciiString &a, const AsciiString &b)
{
    return *(const StringBase<char> *)&a != *(const StringBase<char> *)&b;
}
inline bool operator<(const AsciiString &a, const AsciiString &b)
{
    return *(const StringBase<char> *)&a < *(const StringBase<char> *)&b;
}

#endif

#include "PreRTS.h"

#include "Common/ArchiveFile.h"

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() { m_data = NULL; }
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString& other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

	Int getLength() const
	{
		return m_data != NULL ? m_data->length : 0;
	}

	const char *str() const
	{
		return m_data != NULL ? &m_data->data[0] : "";
	}

	void set(const AsciiString& source)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
	}

	void toLower()
	{
		((StringBase<char> *)this)->toLower();
	}

	Bool nextToken(BFMERetailAsciiString *out, const char *delimiters)
	{
		return ((StringBase<char> *)this)->nextToken((StringBase<char> *)out, delimiters);
	}

private:
	void releaseBuffer();
};

Bool SearchStringMatches(BFMERetailAsciiString str, BFMERetailAsciiString searchString);

static inline Int bfmeLength(const BFMERetailAsciiString& str)
{
	return str.getLength();
}

static inline Bool bfmeEndsWith(const BFMERetailAsciiString& str, const char *suffix, Int length)
{
	return ((const StringBase<char> *)&str)->endsWith(suffix, length);
}

static inline Int bfmeSuffixLength(const AsciiString& str)
{
	const char *data = *(const char * const *)&str;
	return data != NULL ? *(const unsigned short *)(data + 4) : 0;
}

static inline const char *bfmeSuffixData(const AsciiString& str)
{
	const char *data = *(const char * const *)&str;
	return data != NULL ? data + 8 : "";
}

static inline void bfmeConcat(BFMERetailAsciiString& str, const AsciiString& suffix)
{
	Int length = bfmeSuffixLength(suffix);
	const char *text = bfmeSuffixData(suffix);
	((StringBase<char> *)&str)->concat(text, length);
}

static inline void bfmeConcat(BFMERetailAsciiString& str, char suffix)
{
	((StringBase<char> *)&str)->concat(&suffix, 1);
}

// ?getFileListInDirectory@ArchiveFile@@QBEXABVAsciiString@@00AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z
void ArchiveFile::getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	BFMERetailAsciiString searchDir;
	const DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	searchDir.set(originalDirectory);
	searchDir.toLower();
	BFMERetailAsciiString token;
	searchDir.nextToken(&token, "\\/");

	while (token.getLength() > 0) {
		DetailedArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.find(*(const AsciiString *)&token);
		if (it != dirInfo->m_directories.end()) {
			dirInfo = &it->second;
		} else {
			return;
		}

		searchDir.nextToken(&token, "\\/");
	}

	getFileListInDirectory(dirInfo, originalDirectory, searchName, filenameList, searchSubdirectories);
}

// ?getFileListInDirectory@ArchiveFile@@QBEXPBVDetailedArchivedDirectoryInfo@@ABVAsciiString@@1AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z
void ArchiveFile::getFileListInDirectory(const DetailedArchivedDirectoryInfo *dirInfo, const AsciiString& currentDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	DetailedArchivedDirectoryInfoMap::const_iterator diriter = dirInfo->m_directories.begin();
	while (diriter != dirInfo->m_directories.end()) {
		const DetailedArchivedDirectoryInfo *tempDirInfo = &(diriter->second);
		BFMERetailAsciiString tempdirname;
		tempdirname.set(currentDirectory);
		if ((bfmeLength(tempdirname) > 0) && (!bfmeEndsWith(tempdirname, "\\", 1)) && (!bfmeEndsWith(tempdirname, "/", 1))) {
			bfmeConcat(tempdirname, '\\');
		}
		bfmeConcat(tempdirname, tempDirInfo->m_directoryName);
		getFileListInDirectory(tempDirInfo, *(const AsciiString *)&tempdirname, searchName, filenameList, searchSubdirectories);
		diriter++;
	}

	ArchivedFileInfoMap::const_iterator fileiter = dirInfo->m_files.begin();
	while (fileiter != dirInfo->m_files.end()) {
		if (SearchStringMatches(
			*(const BFMERetailAsciiString *)&fileiter->second.m_filename,
			*(const BFMERetailAsciiString *)&searchName)) {
			BFMERetailAsciiString tempfilename;
			tempfilename.set(currentDirectory);
			if ((bfmeLength(tempfilename) > 0) && (!bfmeEndsWith(tempfilename, "\\", 1)) && (!bfmeEndsWith(tempfilename, "/", 1))) {
				bfmeConcat(tempfilename, '\\');
			}
			bfmeConcat(tempfilename, fileiter->second.m_filename);
			if (filenameList.find(*(const AsciiString *)&tempfilename) == filenameList.end()) {
				filenameList.insert(*(const AsciiString *)&tempfilename);
			}
		}
		fileiter++;
	}
}
