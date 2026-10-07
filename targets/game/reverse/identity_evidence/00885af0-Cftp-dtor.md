# Cftp::~Cftp at RVA 0x00885AF0

The 81-byte matched body at RVA 0x00885AF0 in `game/Libraries/Source/WWVegas/WWDownload/Rva00885AF0.cpp` is `Cftp::~Cftp()` (`??1Cftp@@UAE@XZ`). The prior claim `?d_00885af0@Rva00885AF0Class@@QAEXXZ` used an address-derived owner and method.

Evidence (`python3 tools/vtable_lookup.py 0x01132ECC`, `python3 tools/dis_retail.py 0x885AF0`): the body first stores VA 0x01132ECC, a one-slot vftable whose only slot is 0x00886AA0, the matched `??_GCftp@@UAEPAXI@Z` (CftpDeletingDestructor.cpp); the same table is installed by the matched `??0Cftp@@QAE@XZ` at 0x00885AD0 (CftpConstructorThunk.cpp), which sits immediately before this body. A scalar-deleting destructor's callee is the class's complete destructor, and storing the class's own vftable first is the destructor prologue. The body then closes the sockets at +0x08 and +0x04 and fcloses the FILE * at +0x3B8, matching ftp.h's `m_iDataSocket`, `m_iCommandSocket` and `m_pfLocalFile` (offsets per CftpConstructorThunk.cpp's layout). symbols.csv already pins `??1Cftp@@UAE@XZ` at 0x00885AF0.

The correction preserves the start, extent, instructions and relocation targets. A different vftable stored, or a caller treating this as a non-destructor, would refute it.
