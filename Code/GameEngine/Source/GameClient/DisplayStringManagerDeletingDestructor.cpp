// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DisplayStringManager scalar-deleting destructor at retail RVA
// 0x004102A0 (30 bytes). The matched constructor at 0x00410240 installs
// vtable 0x010F1014, and the matched W3DDisplayStringManager destructor calls
// the base destructor at 0x00410290 through ILT 0x000472E9. This wrapper uses
// that same ILT before conditionally invoking scalar operator delete.

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager();
};

void forceDisplayStringManagerDeletingDestructor()
{
	DisplayStringManager value;
}
