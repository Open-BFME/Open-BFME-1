// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x0044F410, 150 bytes. Owner is address-derived from the
// constructor at 0x0044F4D0 and vtable 0x010F5DD8 slot 1 (via ILT 0x13480).
// Child layout follows the matched Rva0090C280 constructor. File +0x0d
// is deleteOnClose in the reference File layout; openFile is the independently
// matched thiscall body at 0x009C8860 (two stack arguments, File* result).

class File {
public:
    void deleteOnClose(void) {
        *((unsigned char *)this + 0x0d) = 1;
    }
};

class FileSystem {
public:
    File *openFile(const char *filename, int mode);
};

#define Rva0044F410TheFileSystem (*(FileSystem **)0x0134CB48)

class Rva0090C280 {
public:
    void *m_vptr;
    unsigned char m_flag;
    unsigned char m_pad05[3];
    int m_08;
    File *m_file;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
    int m_34;
    int m_38;
    int m_3c;
    int m_40;
    int m_44;
public:
    Rva0090C280();
};

class Rva0044F4D0 {
    char m_prefix[0x14];
    Rva0090C280 *m_child;
    const char *m_filename;
    int m_unknown1c[5];
    int m_30;
    int m_34;
    int m_38;
public:
    void rva0044f410(void);
};

void Rva0044F4D0::rva0044f410(void)
{
    Rva0090C280 *p = new Rva0090C280();
    m_child = p;
    p->m_34 = m_30;
    m_child->m_3c = m_34;
    m_child->m_38 = m_38;
    m_child->m_file = Rva0044F410TheFileSystem->openFile(m_filename, 0x41);
    if (m_child->m_file)
        m_child->m_file->deleteOnClose();
}
