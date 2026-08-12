// cl: /DNDEBUG /MD /EHsc

class AsciiString;
class SpecialPowerTemplate;
enum ObjectID { OBJECT_ID_INVALID = 0 };

class SuperweaponInfo
{
private:
    unsigned char m_padding[0x18];

public:
    ObjectID m_id;
};

struct SuperweaponListNode
{
    SuperweaponListNode *next;
    void *previous;
    SuperweaponInfo *value;
};

struct SuperweaponList
{
    SuperweaponListNode *head;
};

struct SuperweaponMapNode
{
    unsigned char padding[0x14];
    SuperweaponList list;
};

class SuperweaponMap
{
public:
    SuperweaponMapNode *find(const AsciiString &name);
    SuperweaponMapNode *end() const { return sentinel; }

private:
    SuperweaponMapNode *sentinel;
    void *root;
    unsigned int size;
};

class InGameUI
{
protected:
    SuperweaponInfo *findSWInfo(int playerIndex, const AsciiString &powerName,
                                ObjectID id, const SpecialPowerTemplate *powerTemplate);

private:
    unsigned char m_padding[0x5cc];
    SuperweaponMap m_superweapons[16];
};

// ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
SuperweaponInfo *InGameUI::findSWInfo(int playerIndex, const AsciiString &powerName,
                                     ObjectID id, const SpecialPowerTemplate *)
{
    SuperweaponMap &map = m_superweapons[playerIndex];
    SuperweaponMapNode *mapIt = map.find(powerName);
    if (mapIt != map.end()) {
        SuperweaponListNode *end = mapIt->list.head;
        for (SuperweaponListNode *listIt = end->next; listIt != end; listIt = listIt->next) {
            if (listIt->value->m_id == id) {
                return listIt->value;
            }
        }
    }
    return 0;
}
