// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeMapObjectListHolder;
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

int rva00087480Get()
{
	return *reinterpret_cast<int *>(BfmeTheMapObjectListHolder);
}
