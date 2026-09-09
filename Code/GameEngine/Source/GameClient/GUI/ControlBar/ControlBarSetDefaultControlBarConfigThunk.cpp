// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00043E73 is a five-byte incremental-link thunk for
// ControlBar::setDefaultControlBarConfig at RVA 0x0049E090.
// The matched ControlBar body provides the destination, and this local
// forwarding class makes MSVC emit the same direct jump without editing the
// generated assembly file.

class ControlBar
{
	friend class ControlBarSetDefaultControlBarConfigThunk;

	protected:
	void setDefaultControlBarConfig();
};

class ControlBarSetDefaultControlBarConfigThunk
{
public:
	void forward();
};

void ControlBarSetDefaultControlBarConfigThunk::forward()
{
	((ControlBar *)this)->setDefaultControlBarConfig();
}
