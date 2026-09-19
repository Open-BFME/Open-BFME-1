// ?setRenderDeviceChecked@Rva008FD0E0Wrapper@@SA_NPBDHHHH_N@Z
class DX8Wrapper {
protected:
	static bool Set_Render_Device(const char* name, int width, int height, int bits, int windowed, bool resize);
};
class Rva008FD0E0Wrapper : public DX8Wrapper {
public:
	static bool setRenderDeviceChecked(const char* name, int width, int height, int bits, int windowed, bool resize);
};
bool Rva008FD0E0Wrapper::setRenderDeviceChecked(const char* name, int width, int height, int bits, int windowed, bool resize)
{
	bool ok = Set_Render_Device(name, width, height, bits, windowed, resize);
	return ok ? true : false;
}
