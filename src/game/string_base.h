#pragma once

template <typename T>
class StringBase {
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
    int compare(const StringBase<T> &str) const;
    int compare(const T *str) const;
    int compare(const T *str, int len) const;
    int compareNoCase(const StringBase<T> &str) const;
    int compareNoCase(const T *str) const;
    int compareNoCase(const T *str, int len) const;
    void concat(const StringBase<T> &str);
    void concat(T c);
    void concat(const T *str);
    const T *reverseFind(T c) const;
    bool startsWith(const StringBase<T> &str) const;
    bool startsWith(const T *str) const;
    bool startsWithNoCase(const T *str) const;
    bool startsWithNoCase(const StringBase<T> &str) const;
    bool endsWith(const T *str) const;
    bool endsWithNoCase(const T *str) const;
    void set(T c);
    void swap(StringBase<T> &other);
    void set(const T *str);
    void clear();

private:
    StringBase();
    ~StringBase();
    void validate() const;
    T *peek() const;

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
