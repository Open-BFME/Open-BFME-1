// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WW3D2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2

#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#include "dx8indexbuffer.h"

extern DX8IndexBufferClass *Rva01341214IndexBuffer;
extern SortingIndexBufferClass *Rva01341218SortingIndexBuffer;

void Rva0090F760Init()
{
	DX8IndexBufferClass *indexBuffer = Rva01341214IndexBuffer;
	if( indexBuffer != 0 )
		return;

	indexBuffer = new DX8IndexBufferClass(
		(unsigned)0xC00, DX8IndexBufferClass::USAGE_DEFAULT );
	Rva01341214IndexBuffer = indexBuffer;
	SortingIndexBufferClass *sortingIndexBuffer =
		new SortingIndexBufferClass( 0xC00 );
	Rva01341218SortingIndexBuffer = sortingIndexBuffer;

	{
		IndexBufferClass::WriteLockClass lock(
			Rva01341214IndexBuffer, 0 );
		unsigned short *indices = lock.Get_Index_Array();
		int value = 1;
		indices += 2;
		int remaining = 0x200;

		do
		{
			indices[ -2 ] = (unsigned short)( value - 1 );
			indices[ -1 ] = (unsigned short)value;
			indices[ 1 ] = (unsigned short)value;
			indices[ 0 ] = (unsigned short)( value + 1 );
			indices[ 2 ] = (unsigned short)( value + 2 );
			indices[ 3 ] = (unsigned short)( value + 1 );
			indices += 6;
			value += 4;
		}
		while( --remaining != 0 );
	}

	{
		IndexBufferClass::WriteLockClass lock(
			Rva01341218SortingIndexBuffer, 0 );
		unsigned short *indices = lock.Get_Index_Array();
		int value = 1;
		indices += 2;
		int remaining = 0x200;

		do
		{
			indices[ -2 ] = (unsigned short)( value - 1 );
			indices[ -1 ] = (unsigned short)value;
			indices[ 1 ] = (unsigned short)value;
			indices[ 0 ] = (unsigned short)( value + 1 );
			indices[ 2 ] = (unsigned short)( value + 2 );
			indices[ 3 ] = (unsigned short)( value + 1 );
			indices += 6;
			value += 4;
		}
		while( --remaining != 0 );
	}
}
