// cl: /DNDEBUG /MD /EHsc

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

struct BfmePoint
{
	long x;
	long y;
};

typedef void *BfmeWindowHandle;

extern BfmeWindowHandle Rva012ED238Global;

extern "C" __declspec(dllimport) int __stdcall GetClientRect(BfmeWindowHandle window, BfmeRect *rect);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(BfmeWindowHandle window, BfmePoint *point);
extern "C" __declspec(dllimport) int __stdcall ClipCursor(const BfmeRect *rect);

void clipCursorToClient(void)
{
	BfmeRect rect;
	GetClientRect(Rva012ED238Global, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	BfmePoint point;
	point.x = rect.left;
	point.y = rect.top;
	ClientToScreen(Rva012ED238Global, &point);
	rect.left = point.x;
	rect.top = point.y;
	rect.right = point.x + width;
	rect.bottom = point.y + height;
	ClipCursor(&rect);
}
