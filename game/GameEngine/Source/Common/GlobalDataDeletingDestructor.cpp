// cl: /O2
//
// GlobalData scalar-deleting destructor, retail 0x000844E0 (30 bytes).
// The GlobalData constructor at 0x00084510 installs vtable 0x0107C68C;
// slot zero routes here through ILT 0x00028853. This wrapper calls the
// 939-byte GlobalData destructor at 0x00084030 through ILT 0x0000564B.

class GlobalData
{
public:
	virtual ~GlobalData();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceGlobalDataDeletingDestructor(const GlobalData &that)
{
	GlobalData value(that);
}
