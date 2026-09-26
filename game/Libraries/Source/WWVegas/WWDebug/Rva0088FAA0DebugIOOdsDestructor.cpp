// cl: /DNDEBUG /MD /EHa /Oy-

class Rva0088FAA0DebugIOInterface
{
protected:
    virtual ~Rva0088FAA0DebugIOInterface(void) {}

public:
    Rva0088FAA0DebugIOInterface(void) {}
    virtual int Read(char *, int) = 0;
    virtual void Write(int, const char *, const char *) = 0;
    virtual void EmergencyFlush(void) = 0;
    virtual void Execute(void) = 0;
    virtual void Delete(void) = 0;
};

class Rva0088FAA0DebugIOOds : public Rva0088FAA0DebugIOInterface
{
public:
    explicit Rva0088FAA0DebugIOOds(void) {}
    virtual int Read(char *, int) { return 0; }
    virtual void Write(int, const char *, const char *) {}
    virtual void EmergencyFlush(void) {}
    virtual void Execute(void) {}
    virtual void Delete(void) { this->~Rva0088FAA0DebugIOOds(); }
};

Rva0088FAA0DebugIOInterface *Rva0088FAA0Create(void)
{
    return new Rva0088FAA0DebugIOOds();
}
