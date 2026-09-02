// ?tryAttach@Rva007E47A0Self@@QAE_NPAVRva007E47A0Peer@@@Z
// partial score=0.4 date=2026-09-02
// Open-BFME: dual-object virtual attach/reject reconstructed from retail RVA 0x007E47A0.
// Identity not recovered; offsets and slot counts are address-derived from the disassembly.

class Rva007E47A0Peer
{
public:
    virtual void unused0(void);
    virtual void notify(int flag);
    virtual bool query(int first, int second);

private:
    unsigned char m_pad[0x24 - 4];
    int m_mode;

    friend class Rva007E47A0Self;
};

class Rva007E47A0Self
{
public:
    bool tryAttach(Rva007E47A0Peer *peer);

private:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void unused5(void);
    virtual void unused6(void);
    virtual void unused7(void);
    virtual void unused8(void);
    virtual void unused9(void);
    virtual void unused10(void);
    virtual int slotB(int flag);
    virtual int slotC(void);

    unsigned char m_pad[0x2c - 4];
    Rva007E47A0Peer *m_attached;
};

bool Rva007E47A0Self::tryAttach(Rva007E47A0Peer *peer)
{
    char flag = 0;
    if (peer->m_mode == 5)
    {
        flag = 1;
    }

    int valueA = slotB(flag);
    int valueB = slotC();

    if (peer->query(valueB, valueA))
    {
        m_attached = peer;
        return true;
    }

    peer->notify(1);
    return false;
}
