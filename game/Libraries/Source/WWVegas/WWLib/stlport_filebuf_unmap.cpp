// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::_Filebuf_base::_M_unmap, retail 0x0084A3C0, 43 bytes. The
// body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the
// name with identity=real.
//
// Two guarded Win32 calls through the import table -- UnmapViewOfFile on the
// base the caller passes, then CloseHandle on the mapping handle the object
// keeps at +4 -- and the handle is cleared afterwards. The length argument is
// never read; it is there for the platforms whose unmap needs it.

namespace _STL
{

class _Filebuf_base
{
public:
	void _M_unmap(void *base, long len);

private:
	void *m_bfmeFileId;					// +0x00
	void *_M_view_id;					// +0x04
};

}

extern "C" __declspec(dllimport) int __stdcall UnmapViewOfFile(void *base);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

// ?_M_unmap@_Filebuf_base@_STL@@QAEXPAXJ@Z
void _STL::_Filebuf_base::_M_unmap(void *base, long len)
{
	if (base)
		UnmapViewOfFile(base);

	if (_M_view_id)
		CloseHandle(_M_view_id);

	_M_view_id = 0;
}
