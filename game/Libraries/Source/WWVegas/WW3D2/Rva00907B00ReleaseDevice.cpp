// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"
// The Shutdown caller at 0x0090B640 invokes this device-release helper.

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

extern VertexBufferClass *Rva01341120VertexBuffers[];
extern IndexBufferClass *Rva01341128IndexBuffer;

// ?Release_Device@DX8Wrapper@@KAXXZ
void DX8Wrapper::Release_Device( void )
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

	DX8Wrapper::Do_Onetime_Device_Dependent_Shutdowns();
	Rva01340534Device->m_vtable->m_release( Rva01340534Device );
	Rva01340534Device = (Rva006C9270Device *)zero;
}
