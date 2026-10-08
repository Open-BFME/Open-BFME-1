// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00C715CA (10 B) loads the address of the global TheDcPool (VA 0x0134FB38)
// into ECX and tail-jumps to the CDCCache destructor (matched at 0x009F6855, the
// four-entry DC cache teardown). The object is the cache that release and acquire
// in Win32DcCache.cpp share.

class CDCCache
{
public:
	~CDCCache(void);
};

class DcPool;
extern DcPool TheDcPool;

void rva00C715CAForward(void)
{
	((CDCCache *)(void *)&TheDcPool)->~CDCCache();
}
