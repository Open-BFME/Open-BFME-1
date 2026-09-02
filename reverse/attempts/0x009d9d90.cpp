// ?_bfme_dumpXferStream@@YA_NPAVFile@@0@Z
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME-only diagnostic reader for the EALA RTS1/RTS2 tagged transfer stream.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <vector>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *name, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, Int mode);
};

static void taggedPrint(File *output, const char *format, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	output->write(buffer, strlen(buffer));
}

static void taggedIndent(File *output, Int depth)
{
	while (depth-- != 0)
		output->write("  ", 2);
}

static Int taggedDepth(const std::vector<AsciiString> &blocks)
{
	return blocks.size();
}

Bool _bfme_dumpXferStream(File *input, File *output)
{
	UnsignedInt magic;
	UnsignedInt streamVersion;
	UnsignedInt options;
	UnsignedInt flags;

	if (input->read(&magic, 4) != 4)
		return FALSE;
	if (input->read(&streamVersion, 4) != 4)
		return FALSE;
	if (magic != 'EALA' || (streamVersion != 'RTS1' && streamVersion != 'RTS2'))
		return FALSE;
	options = 0;
	if (streamVersion != 'RTS1')
		input->read(&options, 4);
	if (input->read(&flags, 4) != 4 || (flags & 1) == 0)
		return FALSE;

	std::vector<AsciiString> blocks;
	std::vector<AsciiString> names;
	UnsignedInt type;
	Bool afterBlock = FALSE;

	if (input->read(&type, 4) != 4)
		return FALSE;

	do
	{
		switch (type)
		{
			case 'c3d':
			{
				Real v[3]; input->read(v, 12);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "x:%1.6f,y:%1.6f,z:%1.6f (HexX:%08x,HexY:%08x,HexZ:%08x) [coord3d]\n",
					v[0], v[1], v[2], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2]);
				break;
			}
			case 'c2d':
			{
				Real v[2]; input->read(v, 8);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "x:%1.6f,y:%1.6f (0xX:%08x,0xY:%08x) [coord2d]\n",
					v[0], v[1], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1]);
				break;
			}
			case 'i64':
			{
				Int64 v; input->read(&v, 8);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%I64i=0x%I64x [int64]\n", v, v);
				break;
			}
			case 'int':
			{
				Int v; input->read(&v, 4);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i=0x%x [int]\n", v, v);
				break;
			}
			case 'r2d':
			{
				Real v[4]; input->read(v, 16);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "x:%1.6f,y:%1.6f to x:%1.6f,y:%1.6f (0xX:%08x,0xY:%08x to 0xX:%08x,0xY:%08x) [region2d]\n",
					v[0],v[1],v[2],v[3],*(UnsignedInt *)&v[0],*(UnsignedInt *)&v[1],*(UnsignedInt *)&v[2],*(UnsignedInt *)&v[3]);
				break;
			}
			case 'r3d':
			{
				Real v[6]; input->read(v, 24);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "x:%1.6f,y:%1.6f,z:%1.6f to x:%1.6f,y:%1.6f,z:%1.6f (0xX:%08x,0xY:%08x,0xZ:%08x to 0xX:%08x,0xY:%08x,0xZ:%08x) [region3d]\n",
					v[0],v[1],v[2],v[3],v[4],v[5],*(UnsignedInt *)&v[0],*(UnsignedInt *)&v[1],*(UnsignedInt *)&v[2],*(UnsignedInt *)&v[3],*(UnsignedInt *)&v[4],*(UnsignedInt *)&v[5]);
				break;
			}
			case 'rgb':
			{
				Real v[3]; input->read(v, 12);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "r:%1.3f,g:%1.3f,b:%1.3f (0xR:%08x,0xG:%08x,0xB:%08x) [rgb]\n",
					v[0],v[1],v[2],*(UnsignedInt *)&v[0],*(UnsignedInt *)&v[1],*(UnsignedInt *)&v[2]);
				break;
			}
			case 'rgbr':
			{
				Real v[4]; input->read(v, 16);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "r:%1.3f,g:%1.3f,b:%1.3f,a:%1.3f (0xR:%08x,0xG:%08x,0xB:%08x,0xA:%08x) [rgba]\n",
					v[0],v[1],v[2],v[3],*(UnsignedInt *)&v[0],*(UnsignedInt *)&v[1],*(UnsignedInt *)&v[2],*(UnsignedInt *)&v[3]);
				break;
			}
			case 'rgbi':
			{
				UnsignedInt v[4]; input->read(v, 16);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "r:%i,g:%i,b:%i,a:%i [irgba]\n",v[0],v[1],v[2],v[3]);
				break;
			}
			case 'rnge':
			{
				Real v[2]; input->read(v, 8);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%1.6f to %1.6f (0x:%08x to 0x:%08x) [range]\n",
					v[0],v[1],*(UnsignedInt *)&v[0],*(UnsignedInt *)&v[1]);
				break;
			}
			case 'real':
			{
				Real v; input->read(&v, 4);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%1.6f (0x%08x) [float]\n",v,*(UnsignedInt *)&v);
				break;
			}
			case 'byte':
			{
				Byte v; input->read(&v, 1);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i=0x%x [byte]\n",(Int)v,(Int)v);
				break;
			}
			case 'ubyt':
			{
				UnsignedByte v; input->read(&v, 1);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i=0x%x [ubyte]\n",(UnsignedInt)v,(UnsignedInt)v);
				break;
			}
			case 'bool':
			{
				Bool v; input->read(&v, 1);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i [bool]\n",(Int)(UnsignedByte)v);
				break;
			}
			case 'shrt':
			{
				Short v; input->read(&v, 2);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i=0x%x [short]\n",(Int)v,(Int)v);
				break;
			}
			case 'usht':
			{
				UnsignedShort v; input->read(&v, 2);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i=0x%x [ushort]\n",(UnsignedInt)v,(UnsignedInt)v);
				break;
			}
			case 'uint':
			{
				UnsignedInt v; input->read(&v, 4);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%u=0x%x [uint]\n",v,v);
				break;
			}
			case 'enu1': case 'enu2': case 'enu3': case 'enu4':
			{
				UnsignedInt v = 0; input->read(&v, type - 'enu1' + 1);
				if (!afterBlock) taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "%i [enum]\n",v);
				break;
			}
			case 'vers':
			{
				UnsignedByte v; input->read(&v, 1);
				taggedIndent(output, taggedDepth(blocks));
				taggedPrint(output, "version: %i\n",(UnsignedInt)v);
				break;
			}
			case 'astr':
			case 'ustr':
			{
				UnsignedInt len = 0; input->read(&len, 1);
				if (len == 0xff) input->read(&len, 4);
				char buffer[256];
				if (type == 'astr') {
					input->read(buffer, len); buffer[len] = 0;
					taggedPrint(output, "'%s' [ascii]\n",buffer);
				} else {
					input->read(buffer, len * 2); ((WideChar *)buffer)[len] = 0;
					taggedPrint(output, "'%S' [unicode]\n",buffer);
				}
				break;
			}
			case 'raw':
			{
				UnsignedInt len; input->read(&len, 4);
				Byte buffer[16];
				for (UnsignedInt at = 0; at < len; at += 16) {
					UnsignedInt count = len - at < 16 ? len - at : 16;
					input->read(buffer, count);
					taggedIndent(output, taggedDepth(blocks));
					taggedPrint(output, "%4d:  ",at);
					for (UnsignedInt i = 0; i < 16; ++i)
						i < count ? taggedPrint(output," %02x",buffer[i]) : taggedPrint(output,"   ");
					taggedPrint(output,"       ");
					for (i = 0; i < count; ++i) taggedPrint(output,"%c",buffer[i] > 0x20 ? buffer[i] : '.');
					taggedPrint(output,"\n");
				}
				break;
			}
			case 'BLOK': case 'DSCR': case 'EBLK':
			{
				UnsignedByte len; input->read(&len,1);
				char name[256];
				if (len == 0xff) {
					UnsignedInt index; input->read(&index,4);
					strcpy(name,names[index].str());
				} else {
					input->read(name,len); name[len]=0;
					names.push_back(AsciiString(name));
				}
				if (type == 'BLOK') input->seek(4,1);
				if (type == 'EBLK') {
					taggedIndent(output, taggedDepth(blocks)-1);
					taggedPrint(output,"</%s>\n",blocks.back().str());
					blocks.pop_back();
				} else if (type == 'BLOK') {
					taggedIndent(output, taggedDepth(blocks)); taggedPrint(output,"<%s>\n",name);
					blocks.push_back(AsciiString(name));
				} else {
					taggedIndent(output, taggedDepth(blocks)); taggedPrint(output,"%s: ",name);
					afterBlock = TRUE;
				}
				break;
			}
			case 'END':
				break;
			default:
				return FALSE;
		}
		afterBlock = FALSE;
	}
	while (type != 'END' && input->read(&type,4) == 4);

	return TRUE;
}
