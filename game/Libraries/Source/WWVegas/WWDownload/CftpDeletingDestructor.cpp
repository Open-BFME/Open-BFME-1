// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Cftp scalar-deleting destructor at retail RVA 0x00886AA0.
// The matched constructor at 0x00885AD0 and complete destructor at 0x00885AF0
// install the one-slot vtable 0x01132ECC; the surrounding named FTP methods
// and the WWDownload class declaration independently establish the identity.

class Cftp
{
public:
	virtual ~Cftp();
};

void forceCftpDeletingDestructor()
{
	Cftp value;
}
