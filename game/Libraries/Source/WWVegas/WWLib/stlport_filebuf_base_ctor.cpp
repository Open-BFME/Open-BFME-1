// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::_Filebuf_base::_Filebuf_base(), retail 0x00849F40, 82
// bytes. The body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv
// holds the name with identity=real.
//
// It sets the file handle to INVALID_HANDLE_VALUE and clears the open mode at
// +8 and the two flags at +0x0C and +0x0D, then fills in the shared page size
// once: if the static is still zero it asks GetSystemInfo and takes dwPageSize
// -- the field at +4 of the 36-byte SYSTEM_INFO the frame reserves, not
// dwAllocationGranularity at +0x1C -- and if the result is still zero it falls
// back to 0x1000.
//
// The store that clears _M_view_id lands after that block rather than in
// declaration order; the zero is already in ebx and the scheduler puts the
// store in the join block.

namespace _STL
{

class _Filebuf_base
{
public:
	_Filebuf_base(void);

protected:
	void *_M_file_id;					// +0x00
	void *_M_view_id;					// +0x04
	int _M_openmode;					// +0x08
	bool _M_is_open;					// +0x0C
	bool _M_should_close;					// +0x0D

	static unsigned int _M_page_size;			// 0x012C7ED0 (pinned)
};

}

struct BfmeSystemInfo
{
	unsigned int dwOemId;
	unsigned int dwPageSize;				// +0x04
	void *lpMinimumApplicationAddress;
	void *lpMaximumApplicationAddress;
	unsigned int dwActiveProcessorMask;
	unsigned int dwNumberOfProcessors;
	unsigned int dwProcessorType;
	unsigned int dwAllocationGranularity;			// +0x1C
	unsigned short wProcessorLevel;
	unsigned short wProcessorRevision;
};

extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(BfmeSystemInfo *info);

// ??0_Filebuf_base@_STL@@QAE@XZ
_STL::_Filebuf_base::_Filebuf_base(void)
{
	_M_file_id = (void *)-1;
	_M_openmode = 0;
	_M_is_open = false;
	_M_should_close = false;

	if (_M_page_size == 0)
	{
		BfmeSystemInfo info;
		GetSystemInfo(&info);
		_M_page_size = info.dwPageSize;
	}

	_M_view_id = 0;

	if (_M_page_size <= 0)
		_M_page_size = 0x1000;
}
