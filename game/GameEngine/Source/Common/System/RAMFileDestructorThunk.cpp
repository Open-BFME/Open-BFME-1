// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift RAMFile dtor __emit thunk to clean C++. Retail stores its
// own vtable, array-deletes (??_V) the buffer member at this+0x14, calls
// File::close() on this (virtual, resolved directly in dtor context), then
// drops EH state to -1 and calls the out-of-line File dtor.

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

class File
{
public:
    virtual ~File();
    virtual void close();

private:
    unsigned char m_pad[0x10];
};

class RAMFile : public File
{
protected:
    virtual ~RAMFile();

private:
    char *m_buffer;
};

// ??1RAMFile@@MAE@XZ
RAMFile::~RAMFile()
{
    delete [] m_buffer;
    close();
}
