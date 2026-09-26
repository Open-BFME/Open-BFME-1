// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00099070 (125 B) is RecorderClass's (the
// class the pinned constructor at 0x000993E0 builds, RecorderClassConstructor.cpp).
// The body frees the file handle at +0xC through the global bfmeFreeUXB import
// if it is set, then the members unwind in reverse declaration order: the
// embedded 0x278-byte ReplayGameInfo store at +0x20 (its destructor is the
// already-landed empty BfmeOwnerBU::~BfmeOwnerBU at 0x00099000), the
// AsciiString at +0x1C, the AsciiString at +0x10, then the SubsystemInterface
// base.

__declspec(dllimport) void __cdecl bfmeFreeUXB(void *p) throw();

template <typename T>
class StringBase
{
public:
    ~StringBase()
    {
        releaseBuffer();
    }

    void *m_data;

private:
    void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
    ~BFMERetailAsciiString() {}
};

// Out-of-line: retail already landed this body at 0x00099000 as
// BfmeOwnerBU::~BfmeOwnerBU (BfmeOwnerDtorBU.cpp); declare only, so the call
// resolves to that existing definition rather than redefining the layout.
class BfmeOwnerBU
{
public:
    ~BfmeOwnerBU();
};

class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
};

class RecorderClass : public SubsystemInterface
{
public:
    virtual ~RecorderClass();

private:
    char m_unreconstructed04[0x0C - 0x04];
    void *m_bfmeFile;					// +0x0C
    BFMERetailAsciiString m_bfmeFileName;		// +0x10
    int m_bfmeCurrentFilePosition;			// +0x14
    int m_bfmeMode;					// +0x18
    BFMERetailAsciiString m_bfmeCurrentReplayFilename;	// +0x1C
    BfmeOwnerBU m_bfmeGameInfo;				// +0x20
};

// ??1RecorderClass@@UAE@XZ
RecorderClass::~RecorderClass()
{
    if (m_bfmeFile)
        bfmeFreeUXB(m_bfmeFile);
}
