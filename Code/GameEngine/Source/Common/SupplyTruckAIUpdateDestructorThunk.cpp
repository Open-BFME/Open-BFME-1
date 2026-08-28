// cl: /DNDEBUG /MD /EHsc
// readable body of ??1SupplyTruckAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// Open-BFME5: lift SupplyTruckAIUpdate dtor __emit thunk to clean C++.
// Primary base (0x340 bytes) carries the four interface subobjects at
// +0x0C/+0x10/+0x20/+0x24; SupplyTruckAIInterface is the secondary direct
// base at +0x340. Body virtual-deletes the heap pointer at +0x344 and clears
// it; the member at +0x364 has an out-of-line dtor; the primary base dtor is
// out-of-line as well.

class ST_RootBase
{
public:
    virtual ~ST_RootBase();

private:
    unsigned char m_pad[8];
};

class ST_Iface1 { public: virtual void vslot(); };
class ST_Iface2 { public: virtual void vslot(); private: unsigned char m_pad[0xC]; };
class ST_Iface3 { public: virtual void vslot(); };
class ST_Iface4 { public: virtual void vslot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public ST_RootBase, public ST_Iface1, public ST_Iface2, public ST_Iface3, public ST_Iface4
{
public:
    virtual ~AIUpdateInterface();

private:
    unsigned char m_pad[0x318];
};

class ST_SupplyTruckAIInterface { public: virtual void vslot(); };

class ST_HeapObj
{
public:
    virtual ~ST_HeapObj();
};

class ST_MemberObj
{
public:
    ~ST_MemberObj();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIUpdate : public AIUpdateInterface, public ST_SupplyTruckAIInterface
{
public:
    virtual ~SupplyTruckAIUpdate();

private:
    ST_HeapObj *m_member;
    unsigned char m_pad2[0x1C];
    ST_MemberObj m_obj;
};

// ??1SupplyTruckAIUpdate@@UAE@XZ
SupplyTruckAIUpdate::~SupplyTruckAIUpdate()
{
    delete m_member;
    m_member = 0;
}
