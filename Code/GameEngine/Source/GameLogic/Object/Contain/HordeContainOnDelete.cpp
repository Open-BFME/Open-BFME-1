// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// HordeContain primary vtable slot 8 cleans the owned pointer vector.
#include <vector>

class OpenContain
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07();
    virtual void onDelete();
private:
    unsigned char m_prefix04[0xe0];
};

class Rva00237950Interface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
};

class Rva0023B6E0Element;
class HordeContain : public OpenContain
{
public:
    virtual void onDelete();
private:
    Rva00237950Interface m_interface;
    unsigned char m_prefixe8[0xd8];
    _STL::vector<Rva0023B6E0Element *> m_pointerVector1C0;
};

void HordeContain::onDelete()
{
    m_interface.slot51();
    for (unsigned int i = 0; i < m_pointerVector1C0.size(); ++i)
        ::operator delete(m_pointerVector1C0[i]);
    m_pointerVector1C0.clear();
    OpenContain::onDelete();
}
