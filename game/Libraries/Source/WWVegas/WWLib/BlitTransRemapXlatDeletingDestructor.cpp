// cl: /O2

// The exact constructor at 0x0043CD10 identifies this 30-byte scalar-deleting destructor.
template<class T>
class BlitTransRemapXlat
{
public:
	virtual ~BlitTransRemapXlat();
};

void forceBlitTransRemapXlatDeletingDestructor()
{
	BlitTransRemapXlat<unsigned char> value;
}
