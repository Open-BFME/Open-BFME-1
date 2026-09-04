// Retail 0x004A8F10: dispatch a gadget action and optionally refresh its image.

class Rva004A8F10Window
{
public:
	virtual void slot00( void );
	virtual void slot01( void );
	virtual void slot02( void );
	virtual void slot03( void );
	virtual void slot04( void );
	virtual void slot05( void );
	virtual void slot06( void );
	virtual void slot07( void );
	virtual bool isReady( void );
};

class Rva004A8F10Gate
{
public:
	bool isSet( void );
};

class Rva004A8F10Sink
{
public:
	int send( void *data, bool second, bool first );
};

class Rva004A8F10CurrentOwner
{
public:
	int current( void );
};

extern void j_00010e88( void );
extern void j_000330dc( void );
extern void j_00038a23( void );
extern void j_00044409( void );

typedef void *(*Rva004A8F10GetData)( void *window );
typedef void (*Rva004A8F10SetImage)( void *window, int image );

class Rva004A8F10
{
public:
	int dispatch( void *window, int mode );
};

int Rva004A8F10::dispatch( void *window, int mode )
{
	if ( window == 0 )
		return 0;

	void *data = ((Rva004A8F10GetData)j_00010e88)( window );
	if ( !((Rva004A8F10Window *)window)->isReady() )
		return 0;
	if ( data == 0 )
		return 0;
	if ( (*(Rva004A8F10Gate **)0x012ED748)->isSet() )
		return 0;

	*(void **)((char *)data + 0xA4) = window;
	int result = ((Rva004A8F10Sink *)this)->send(
		data, mode != 0x4009, mode == 0x400B);

	if ( *(int *)((char *)data + 0x10) != 15 )
	{
		int image = ((Rva004A8F10CurrentOwner *)data)->current();
		((Rva004A8F10SetImage)j_00038a23)( window, image );
	}
	return result;
}
