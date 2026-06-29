#pragma once

template <typename T>
class StringBase {
public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    int getLength() const;

private:
    void validate() const;

private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};
