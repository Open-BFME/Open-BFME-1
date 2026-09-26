// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00747E80 writes the NamedCameras chunk from the View camera list.
// The record layout matches Rva00741830's constructor at 0x00741830.

#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Rva00747E80Coord3D
{
	Real x;
	Real y;
	Real z;
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void writeInt(Int value);
	void writeReal(Real value);
	void writeAsciiString(const AsciiString &value);
	void closeDataChunk();
};

class Rva00741830NamedCamera
{
public:
	Rva00741830NamedCamera *m_next;
	AsciiString m_name;
	Real m_position[3];
	Real m_values[6];
	unsigned char m_flag;
};

class Rva00747E80Filter
{
public:
	virtual void destroy() = 0;
	virtual Bool shouldWrite(Rva00741830NamedCamera *camera) = 0;
};

class Rva00747E80View
{
public:
	char m_padding00[0x80];
	Rva00741830NamedCamera *m_namedCameras;
};

#define TheTacticalView (*(Rva00747E80View **)0x012F1600)

void Rva00747E80(DataChunkOutput *output, Rva00747E80Filter *filter)
{
	if (TheTacticalView == 0)
		return;

	output->openDataChunk("NamedCameras", 2);

	Int count = 0;
	for (Rva00741830NamedCamera *camera = TheTacticalView->m_namedCameras;
		camera != 0; camera = camera->m_next)
	{
		if (filter->shouldWrite(camera))
			++count;
	}
	output->writeInt(count);

	for (Rva00741830NamedCamera *camera = TheTacticalView->m_namedCameras;
		camera != 0; camera = camera->m_next)
	{
		if (!filter->shouldWrite(camera))
			continue;

		Rva00747E80Coord3D position;
		position.x = camera->m_position[0];
		position.y = camera->m_position[1];
		position.z = camera->m_position[2];
		output->writeReal(position.x);
		output->writeReal(position.y);
		output->writeReal(position.z);
		output->writeAsciiString(camera->m_name);
		output->writeReal(camera->m_values[2]);
		output->writeReal(camera->m_values[3]);
		output->writeReal(camera->m_values[1]);
		output->writeReal(camera->m_values[4]);
		output->writeReal(camera->m_values[5]);
		output->writeReal(camera->m_values[0]);
	}

	output->closeDataChunk();
}
