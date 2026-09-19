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
