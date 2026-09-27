// cl: /DNDEBUG /MD /GX /Iinputs/reference/shims/stringinline
// ConnectionManager::sendFile twin, ZH ConnectionManager.cpp:2143.
// Identity/signature: matched Network::sendFile at RVA 0x00682540 passes
// (AsciiString, unsigned char, unsigned short); old PBDHH lift was mistyped.
// BFME layout: m_localSlot +0x12028 (layout witness); message size 0x28,
// player +0x0c and ID +0x10 from NetCommandMsg constructors and setters.
// LAN OnChat uses an IP/port record reference, witnessed in this call.
void __cdecl operator delete[](void *) throw();
#include "StringInline.h"
class File {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0A();
 virtual int size();
 virtual void slot0C();
 virtual char *readEntireAndClose();
};
class FileSystem { public: File *openFile(const char *filename, int flags); };
extern FileSystem *TheFileSystem;
struct BFMEFileTransferAddress { unsigned int ip; unsigned short port; BFMEFileTransferAddress(unsigned int value,unsigned short portValue):ip(value),port(portValue) {} };
class LANAPI
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void unknown08();
	virtual void unknown0C();
	virtual void unknown10();
	virtual void unknown14();
	virtual void unknown18();
	virtual void unknown1C();
	virtual void unknown20();
	virtual void unknown24();
	virtual void unknown28();
	virtual void unknown2C();
	virtual void unknown30();
	virtual void unknown34();
	virtual void unknown38();
	virtual void unknown3C();
	virtual void unknown40();
	virtual void unknown44();
	virtual void unknown48();
	virtual void unknown4C();
	virtual void unknown50();
	virtual void unknown54();
	virtual void unknown58();
	virtual void unknown5C();
	virtual void unknown60();
	virtual void unknown64();
	virtual void unknown68();
	virtual void unknown6C();
	virtual void unknown70();
	virtual void unknown74();
	virtual void unknown78();
	virtual void unknown7C();
	virtual void unknown80();
	virtual void unknown84();
	virtual void unknown88();
	virtual void OnChat(UnicodeString player, const BFMEFileTransferAddress &address,
		UnicodeString message, int format);
};
extern LANAPI *TheLAN;
class NetCommandMsg {
public:
 void detach();
 void setPlayerID(unsigned int id) { m_playerID=id; }
 void setID(unsigned short id) { m_id=id; }
 void *m_vptr;
 unsigned int m_timestamp, m_executionFrame, m_playerID;
 unsigned short m_id;
 unsigned int m_commandType;
 int m_referenceCount;
};
class NetFileCommandMsg : public NetCommandMsg {
public:
 NetFileCommandMsg();
 void setRealFilename(AsciiString path);
 void setFileData(unsigned char *data, unsigned int size);
 char unknown1c[12];
};
class ConnectionManager { public: void sendLocalCommand(NetCommandMsg *, unsigned char); };
class BFMEConnectionManager {
public:
 void sendFileChunk(AsciiString path, unsigned char playerMask, unsigned short commandID);
 char unknown00[0x12028];
 int m_localSlot;
};
void BFMEConnectionManager::sendFileChunk(AsciiString path, unsigned char playerMask, unsigned short commandID)
{
 File *theFile = TheFileSystem->openFile(path.str(), 0);
 if (!theFile || !theFile->size()) {
  UnicodeString log;
  log.format(L"Not sending file '%hs' to %X\n", path.str(), playerMask);
  if (TheLAN)
   TheLAN->OnChat(UnicodeString(L"sendFile"), BFMEFileTransferAddress(0,0), log, 2);
  return;
 }
 int len=theFile->size();
 char *buf=theFile->readEntireAndClose();
 NetFileCommandMsg *fileMsg=new NetFileCommandMsg;
 fileMsg->setPlayerID(m_localSlot);
 fileMsg->setID(commandID);
 fileMsg->setRealFilename(path);
 fileMsg->setFileData((unsigned char *)buf,len);
 delete[] buf;
 reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(fileMsg,playerMask);
 fileMsg->detach();
}
