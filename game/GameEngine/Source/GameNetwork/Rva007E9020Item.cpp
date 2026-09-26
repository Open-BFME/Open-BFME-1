class Rva007E9020Item
{
public:
    explicit Rva007E9020Item(void *message);
    virtual ~Rva007E9020Item() {}
    virtual void slot2() {}
    virtual void slot3() {}
private:
    void *m_message;
};

Rva007E9020Item::Rva007E9020Item(void *message) : m_message(message)
{
}
