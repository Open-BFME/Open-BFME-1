// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class Rva003AD0E0Ref
{
public:
    virtual ~Rva003AD0E0Ref();

    long m_refCount;

    void Add_Ref(void)
    {
        InterlockedIncrement(&m_refCount);
    }

    void Release_Ref(void)
    {
        if (InterlockedDecrement(&m_refCount) <= 0)
            delete this;
    }
};

class Rva003AD0E0Handle
{
public:
    Rva003AD0E0Handle &operator=(const Rva003AD0E0Handle &other)
    {
        if (this != &other)
        {
            if (other.m_ptr)
                other.m_ptr->Add_Ref();
            if (m_ptr)
                m_ptr->Release_Ref();
            m_ptr = other.m_ptr;
        }
        return *this;
    }

private:
    Rva003AD0E0Ref *m_ptr;
};

class Rva003AD0E0
{
public:
    virtual void handle();
    Rva003AD0E0 &operator=(const Rva003AD0E0 &other);

private:
    long m_field04;
    Rva003AD0E0Handle m_ptr;
    unsigned char m_flag;
};

Rva003AD0E0 &Rva003AD0E0::operator=(const Rva003AD0E0 &other)
{
    m_field04 = other.m_field04;
    m_ptr = other.m_ptr;
    m_flag = other.m_flag;
	return *this;
}
