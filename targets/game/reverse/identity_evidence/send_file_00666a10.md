# sendFileChunk signature correction at RVA 0x00666A10

Old: `?sendFileChunk@BFMEConnectionManager@@QAEXPBDHH@Z`
New: `?sendFileChunk@BFMEConnectionManager@@QAEXVAsciiString@@EG@Z`
Extent: 435 bytes, unchanged.

The matched Network::sendFile body at RVA 0x00682540 (Network_fileTransfer.cpp)
copies AsciiString and calls this address with byte mask and ushort command ID.
Its existing symbols.csv pin already names the corrected signature at 0x00666A10.
Retail releases the incoming owning string at its epilogue (call 0x00887940),
reads command ID as a word at +0x92 and player mask as a byte in the log path.
Zero Hour GeneralsMD ConnectionManager.cpp:2143 sendFile has the same signature,
file read, message construction, filename/data setter calls, and dispatch order.
BFME uses TheFileSystem rather than TheLocalFileSystem and passes LAN address
as a two-field IP/port record by reference. The new C++ models both differences.
The existing descriptive method name is retained; only its parameter types change.
