struct Coord2DBase {
    float x;
    float y;
    bool isInitialized() const;
};
class Coord2D : public Coord2DBase {
public:
    Coord2D &Negate();
};

class Rva01046508Interface {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual Rva01046508Interface &operator<<(const char *text);
    virtual void slot15();
    virtual void slot16();
    virtual bool slot17(bool value);
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual bool slot24();
    virtual Rva01046508Interface &slot25(const char *file, int line, const char *expression);
};
extern Rva01046508Interface *Rva01046508;
bool __cdecl Rva0012E0E0(int value);

Coord2D &Coord2D::Negate() {
    if (!isInitialized() && !Rva0012E0E0(0) && !Rva01046508->slot24()) {
        (Rva01046508->slot25("z:\\lotr\\code\\libraries\\source\\math\\MathCoord2D.h", 529,
                               "(*this).isInitialized()")
            << ": " << "A math structure was used while uninitialized.  STOP!  Tell an engineer now.").slot17(false);
    }
    x = -x;
    y = -y;
    return *this;
}
