// cl: /DNDEBUG /MD /EHsc
// The Shutdown caller at 0x0090B640 invokes this device-release helper.

class VertexBufferClass
{
public:
	void Release_Engine_Ref() const;
	void Release_Ref()
	{
		--m_numRefs;
		if( m_numRefs == 0 )
			Delete_This();
	}
	virtual void Delete_This() = 0;

private:
	int m_numRefs;
};

class IndexBufferClass
{
public:
	void Release_Engine_Ref() const;
	void Release_Ref()
	{
		--m_numRefs;
		if( m_numRefs == 0 )
			Delete_This();
	}
	virtual void Delete_This() = 0;

private:
	int m_numRefs;
};

struct Rva006C9270Device;

struct Rva00907B00DeviceVtable
{
	void *m_queryInterface;
	void *m_addRef;
	long (__stdcall *m_release)( Rva006C9270Device *device );
	void *m_slots3To64[ 62 ];
	long (__stdcall *m_setTexture)( Rva006C9270Device *device, unsigned stage, void *texture );
	void *m_slots66To99[ 34 ];
	long (__stdcall *m_setStreamSource)( Rva006C9270Device *device, unsigned stream, void *buffer, unsigned offset, unsigned stride );
	void *m_slots101To103[ 3 ];
	long (__stdcall *m_setIndices)( Rva006C9270Device *device, void *buffer );
};

struct Rva006C9270Device
{
	Rva00907B00DeviceVtable *m_vtable;
};

extern Rva006C9270Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;
extern void d_00907960( void );

extern VertexBufferClass *Rva01341120VertexBuffers[];
extern IndexBufferClass *Rva01341128IndexBuffer;

// ?d_00907b00@@YAXXZ
void d_00907b00( void )
{
	void *zero = 0;
	if( Rva01340534Device == (Rva006C9270Device *)zero )
		return;

	for( unsigned stage = 0; stage < 8; ++stage )
	{
		Rva01340534Device->m_vtable->m_setTexture( Rva01340534Device, stage, zero );
		++Rva01340594DX8Calls;
	}

	Rva01340534Device->m_vtable->m_setStreamSource( Rva01340534Device, (unsigned)zero, zero, (unsigned)zero, (unsigned)zero );
	++Rva01340594DX8Calls;
	Rva01340534Device->m_vtable->m_setIndices( Rva01340534Device, zero );
	++Rva01340594DX8Calls;

	for( unsigned stream = 0; stream < 8; stream += 4 )
	{
		if( *(VertexBufferClass **)((unsigned char *)Rva01341120VertexBuffers + stream) != (VertexBufferClass *)zero )
			(*(VertexBufferClass **)((unsigned char *)Rva01341120VertexBuffers + stream))->Release_Engine_Ref();
		if( *(VertexBufferClass **)((unsigned char *)Rva01341120VertexBuffers + stream) != (VertexBufferClass *)zero )
		{
			(*(VertexBufferClass **)((unsigned char *)Rva01341120VertexBuffers + stream))->Release_Ref();
			*(VertexBufferClass **)((unsigned char *)Rva01341120VertexBuffers + stream) = (VertexBufferClass *)zero;
		}
	}

	if( Rva01341128IndexBuffer != (IndexBufferClass *)zero )
		Rva01341128IndexBuffer->Release_Engine_Ref();
	if( Rva01341128IndexBuffer != (IndexBufferClass *)zero )
	{
		Rva01341128IndexBuffer->Release_Ref();
		Rva01341128IndexBuffer = (IndexBufferClass *)zero;
	}

	d_00907960();
	Rva01340534Device->m_vtable->m_release( Rva01340534Device );
	Rva01340534Device = (Rva006C9270Device *)zero;
}
