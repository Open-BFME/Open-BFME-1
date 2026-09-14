// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: IMEManager scalar-deleting destructor at retail RVA
// 0x0048DEA0 (30 bytes). The IMEManager constructor at 0x0048D200 installs
// vtable 0x010F9978 and the matched complete destructor at 0x0048D8B0
// restores the IMEManagerInterface table before releasing its IMM contexts
// and candidate windows. The authored destructor and init TUs establish the
// object layout including fields at +0x10/+0x14 and +0x304c/+0x3050.

class IMEManager
{
public:
	virtual ~IMEManager();
};

void forceIMEManagerDeletingDestructor()
{
	IMEManager value;
}
