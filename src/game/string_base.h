#pragma once

template <typename T>
class StringBase {
public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    bool isNotEmpty() const;
    int getLength() const;
    const T *str() const;
    T getCharAt(int index) const;

private:
    StringBase();
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
