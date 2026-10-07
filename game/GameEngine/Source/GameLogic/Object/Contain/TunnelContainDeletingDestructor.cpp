// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TunnelContain's protected complete destructor (0x0022EF90) and
// its scalar-deleting wrapper (0x0022F0E0).  Vtable 0x00CADDB8 slots name
// this class; its slot zero routes through ILT 0x00040B42 to the 30-byte
// wrapper, which calls the complete destructor through ILT 0x0003BF39
// (pinned ??1TunnelContain@@MAE@XZ).  The destructor re-stores the nine
// sub-object vtables and tail-jumps to OpenContain's complete destructor
// (ILT 0x00039D6A).  Layout view as in TunnelContainCtorThunk.cpp.

class TC_GrandBase
{
public:
    virtual ~TC_GrandBase();

private:
    unsigned char m_pad[8];
};

class TC_Iface1 { public: virtual ~TC_Iface1(); };
class TC_Iface2 { public: virtual ~TC_Iface2(); private: unsigned char m_pad[0xC]; };
class TC_Iface3 { public: virtual ~TC_Iface3(); };
class TC_Iface4 { public: virtual ~TC_Iface4(); };
class TC_Iface5 { public: virtual ~TC_Iface5(); };
class TC_Iface6 { public: virtual ~TC_Iface6(); };
class TC_Iface7 { public: virtual ~TC_Iface7(); };
class TC_Iface8 { public: virtual ~TC_Iface8(); };

class OpenContain : public TC_GrandBase,
                public TC_Iface1,
                public TC_Iface2,
                public TC_Iface3,
                public TC_Iface4,
                public TC_Iface5,
                public TC_Iface6,
                public TC_Iface7,
                public TC_Iface8
{
public:
    virtual ~OpenContain();

private:
    unsigned char m_pad[0x9C];
};

class TunnelContain : public OpenContain
{
protected:
    virtual ~TunnelContain();

private:
    bool m_d4;
    bool m_d5;
};

TunnelContain::~TunnelContain()
{
}
