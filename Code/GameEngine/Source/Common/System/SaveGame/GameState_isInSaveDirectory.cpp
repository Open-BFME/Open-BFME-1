// Open-BFME5: GameState::isInSaveDirectory at retail RVA 0x0010F1E0.

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

    Header *m_data;

public:
    bool startsWithNoCase(const T *text, int length) const;

    bool startsWithNoCase(const StringBase<T> &other) const
    {
        const int length = other.m_data ? other.m_data->length : 0;
        const T *text = other.m_data ? &other.m_data->data[0] : (const T *)0x0107388b;
        return startsWithNoCase(text, length);
    }
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other);
    ~AsciiString();

    bool startsWithNoCase(const AsciiString &other) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(
            *(const StringBase<char> *)&other);
    }
};

class GameState
{
public:
    AsciiString getSaveDirectory() const;
    bool isInSaveDirectory(const AsciiString &path) const;
};

bool GameState::isInSaveDirectory(const AsciiString &path) const
{
    return path.startsWithNoCase(getSaveDirectory());
}
