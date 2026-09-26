// cl: /DNDEBUG /MD /EHa /Oy-

class Rva0088A6E0Interface
{
protected:
    virtual ~Rva0088A6E0Interface(void) {}

public:
    Rva0088A6E0Interface(void) {}
    virtual int Read(char *, int) = 0;
    virtual void Write(int, const char *, const char *) = 0;
    virtual void EmergencyFlush(void) = 0;
    virtual void Execute(void) = 0;
    virtual void Delete(void) = 0;
};

class Rva0088A6E0Virtual : public Rva0088A6E0Interface
{
public:
    explicit Rva0088A6E0Virtual(void) {}
    virtual int Read(char *, int) { return 0; }
    virtual void Write(int, const char *, const char *) {}
    virtual void EmergencyFlush(void) {}
    virtual void Execute(void) {}
    virtual void Delete(void) { this->~Rva0088A6E0Virtual(); }
};

Rva0088A6E0Interface *Rva0088A6E0Create(void)
{
    return new Rva0088A6E0Virtual();
}
