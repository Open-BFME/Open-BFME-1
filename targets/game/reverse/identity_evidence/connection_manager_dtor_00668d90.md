# ConnectionManager destructor at RVA 0x00668D90 (561 bytes)
Old: `?destroy@BFMEConnectionManager@@QAEXXZ`
New: `??1ConnectionManager@@QAE@XZ`

The matched scalar deleting destructor ConnectionManagerDeletingDestructor.cpp
(RVA 0x00681E10) calls this body through ILT 0x00019E25, then operator delete.
The independently matched Network::init and Network::~Network use the same
complete destructor identity. The existing symbols.csv pin documents that ILT.
The body installs vtable VA 0x0111A2B0 and automatically destroys the string
at +0x12058 and three STL map members, including an 8-element map array.
This is compiler destructor cleanup, not an ordinary destroy member.
The ZH ConnectionManager destructor corroborates transport/connection/frame
and pending command teardown. BFME combines the frame and connection loop.

Dependency evidence: ZH ConnectionManager.h declares ushort-to-AsciiString,
ushort-to-byte and ushort-to-int maps in the same member order. BFME constructor
allocates 24/20/24-byte nodes and the known file transfer users read those value
kinds. Aligned retail calls name erase bodies 0x00667B50 / 0x00665120 /
0x00665170 and tree destructors 0x00668990 / 0x00667820. Independently compiled
helpers match their complete 61/53/53/124/124-byte bodies modulo relocation.
Address-tagged comparator instantiations preserve less-than semantics and
separate these witnessed TU-local copies from generic helper pins elsewhere.
No additional helper rows are claimed as progress.
