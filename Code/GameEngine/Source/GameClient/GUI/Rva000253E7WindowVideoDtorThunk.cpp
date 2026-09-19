// cl: /O2 /MD /EHsc

class WindowVideo
{
public:
	__declspec(noinline) ~WindowVideo();
};

void __fastcall Rva000253E7WindowVideoDtorThunk(WindowVideo *video)
{
	video->~WindowVideo();
}
