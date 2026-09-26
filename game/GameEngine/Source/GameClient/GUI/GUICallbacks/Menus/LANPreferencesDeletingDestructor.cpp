// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LANPreferences scalar-deleting destructor at retail RVA
// 0x00086410 (30 bytes). The matched constructor at 0x00086480 installs
// vtable 0x0107C6F8, whose first slot routes here through ILT 0x00036BBF.
// This wrapper calls the pinned LANPreferences destructor through ILT
// 0x00040DB3 before conditionally invoking scalar operator delete.

class LANPreferences
{
public:
	virtual ~LANPreferences();
};

void forceLANPreferencesDeletingDestructor()
{
	LANPreferences value;
}
