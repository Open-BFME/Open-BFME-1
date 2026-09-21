// cl: /O2 /Ob0 /DNDEBUG /MD /EHs-c-
//
// Tiny View virtuals recovered from the base vtable at 0x010F6940.

struct Rva0045BA00Coord3D
{
    float x;
    float y;
    float z;
};

class View
{
public:
    virtual unsigned int getID();
    virtual bool isZoomLimited();
    virtual void Rva0045BA00Slot(const Rva0045BA00Coord3D *,
        const Rva0045BA00Coord3D *, unsigned int, unsigned int);
    virtual void Rva0045BA10Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual void Rva0045BAC0Slot(unsigned int, unsigned int, unsigned int,
        unsigned int, unsigned int, unsigned int, unsigned int);
    virtual void Rva0045BAF0Slot(unsigned int);
    virtual void Rva0045BB10Slot(unsigned int, unsigned int, unsigned int);
    virtual void Rva0045BB20Slot(unsigned int);
    virtual void Rva0045BB30Slot(unsigned int);
    virtual void Rva0045BB40Slot(unsigned int, unsigned int, unsigned int);
    virtual void Rva0045BB70Slot(unsigned int);
    virtual void Rva0045BB80Slot(unsigned int);
    virtual void Rva0045BB90Slot(unsigned int);
    virtual void Rva0045BBB0Slot();
    virtual void Rva0045BBC0Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual int Rva0045BBD0Slot();
    virtual int Rva0045BBE0Slot();
    virtual void Rva0045BC20Slot(unsigned int, unsigned int);
    virtual void Rva0045BC30Slot(unsigned int);
    virtual void Rva0045BC50Slot(unsigned int, unsigned int, unsigned int,
        unsigned int, unsigned int);
    virtual void Rva0045BC60Slot(unsigned int, unsigned int, unsigned int,
        unsigned int, unsigned int, unsigned int);
    virtual void Rva0045BCA0Slot(unsigned int);
    virtual void Rva0045BCB0Slot(unsigned int, unsigned int, unsigned int);
    virtual void Rva0045BCD0Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual void Rva0045BCE0Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual void Rva0045BCF0Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual void Rva0045BD00Slot(unsigned int, unsigned int, unsigned int,
        unsigned int);
    virtual float Rva0045BD10Slot() const;

private:
    unsigned char m_next[4];
    unsigned int m_id;
    unsigned char m_padding[0x38];
    bool m_zoomLimited;
};

unsigned int View::getID()
{
    return m_id;
}

bool View::isZoomLimited()
{
    return m_zoomLimited;
}

void View::Rva0045BA00Slot(const Rva0045BA00Coord3D *,
    const Rva0045BA00Coord3D *, unsigned int, unsigned int)
{
}

void View::Rva0045BA10Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

void View::Rva0045BAC0Slot(unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int, unsigned int)
{
}

void View::Rva0045BAF0Slot(unsigned int)
{
}

void View::Rva0045BB10Slot(unsigned int, unsigned int, unsigned int)
{
}

void View::Rva0045BB20Slot(unsigned int)
{
}

void View::Rva0045BB30Slot(unsigned int)
{
}

void View::Rva0045BB40Slot(unsigned int, unsigned int, unsigned int)
{
}

void View::Rva0045BB70Slot(unsigned int)
{
}

void View::Rva0045BB80Slot(unsigned int)
{
}

void View::Rva0045BB90Slot(unsigned int)
{
}

void View::Rva0045BBB0Slot()
{
}

void View::Rva0045BBC0Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

int View::Rva0045BBD0Slot()
{
    return 0;
}

int View::Rva0045BBE0Slot()
{
    return 0;
}

void View::Rva0045BC20Slot(unsigned int, unsigned int)
{
}

void View::Rva0045BC30Slot(unsigned int)
{
}

void View::Rva0045BC50Slot(unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int)
{
}

void View::Rva0045BC60Slot(unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int)
{
}

void View::Rva0045BCA0Slot(unsigned int)
{
}

void View::Rva0045BCB0Slot(unsigned int, unsigned int, unsigned int)
{
}

void View::Rva0045BCD0Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

void View::Rva0045BCE0Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

void View::Rva0045BCF0Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

void View::Rva0045BD00Slot(unsigned int, unsigned int, unsigned int,
    unsigned int)
{
}

float View::Rva0045BD10Slot() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x28);
}

class Rva0045BB50Noop
{
public:
	void noop();
};

void Rva0045BB50Noop::noop()
{
}
