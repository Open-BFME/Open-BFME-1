#pragma once

// BFME's StringBase<T> is Zero Hour's AsciiString made a template (upstream:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h).
// The members defined in the class below are the ones retail inlines at EVERY
// call site: the image holds no call to their COMDATs (0x0005F270 str,
// 0x0005E4A0 getLength, 0x0005E490 ~StringBase, 0x000680C0 clear, ...), only the
// incremental-link thunk's jmp, and the exports keep the bodies alive. str()
// keeps Zero Hour's function-local TheNullChr, which retail exports as
// ?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB (0x00C7388B; wide 0x00C7388C).
// isEmpty, compare, concat and the rest were header-defined too (their COMDATs
// also sit outside StringBase.cpp's block at 0x00887000-0x00889300), but MSVC
// kept real calls to them at many sites (66 to isEmpty's thunk, 391 to
// compare's), and the tree matches those sites against out-of-line bodies in
// StringBase.cpp, so they stay declared here and defined there.
template <typename T>
class StringBase {
    friend class AsciiString;
    friend class UnicodeString;

public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int getLength() const
    {
        validate();
        return m_data ? m_data->length : 0;
    }
    const T *str() const
    {
        validate();
        static const T TheNullChr = 0;
        return m_data ? peek() : &TheNullChr;
    }
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
    void swap(StringBase<T> &other)
    {
        Header *tmp = m_data;
        m_data = other.m_data;
        other.m_data = tmp;
    }
    void clear()
    {
        releaseBuffer();
    }
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
    // ??1?$StringBase@D@@AAE@XZ (0x0005E490) and ??1AsciiString@@QAE@XZ
    // (0x0005EE90) are both a bare `jmp releaseBuffer`.
    ~StringBase()
    {
        validate();
        releaseBuffer();
    }
    void validate() const {}
    T *peek() const
    {
        return &m_data->data[0];
    }
    void releaseBuffer();
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1, int src1Len, const T *src2, int src2Len);

private:
    struct Header {
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
