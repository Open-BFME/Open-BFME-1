// ?bfmeCopyCuSnap@@YAXPAX0@Z
// partial score=0.737 date=2026-09-28
// cl: /DNDEBUG /MD
#include <math.h>

struct Rva00719AF0Element
{
	float x;
	float y;
	float weight;
};

struct Rva00719CD0FalseType
{
};

struct Rva00719CD0Vector
{
	unsigned char *begin;
	unsigned char *end;
	unsigned char *capacity;

	void insertOverflow(unsigned char *position,
		const Rva00719AF0Element &value,
		const Rva00719CD0FalseType &tag,
		unsigned int fillLength, bool atEnd);
};

extern "C" Rva00719AF0Element *__cdecl BfmeRva00719CD0Copy(
	Rva00719AF0Element *first, Rva00719AF0Element *last,
	Rva00719AF0Element *result, const Rva00719CD0FalseType &tag,
	int unused);
#pragma comment(linker, "/alternatename:_BfmeRva00719CD0Copy=?j_00039c1b@@YAXXZ")
#pragma comment(linker, "/alternatename:?insertOverflow@Rva00719CD0Vector@@QAEXPAURva00719AF0Element@@ABURva00719AF0Element@@ABURva00719CD0FalseType@@I_N@Z=?j_00027d8b@@YAXXZ")

#define Rva00719CD0DefaultBU (*(volatile float *)0x01075334)
#define Rva00719CD0K1253 (*(const float *)0x0107533C)
#define Rva00719CD0ScaleBK (*(float *)0x01075C70)
#define Rva00719CD0ZeroRange (*(const float *)0x01075350)
#define Rva00719CD0Threshold (*(const float *)0x01076C24)
#define Rva00719CD0ActionSlop (*(const float *)0x010888F0)

struct Rva00719CD0Snapshot
{
	int mode;
	int count;
	float firstAmplitude;
	float firstWidth;
	float secondAmplitude;
	float secondWidth;
};

void __cdecl bfmeCopyCuSnap(void *vectorAddress, void *snapshotAddress)
{
	Rva00719CD0Vector *vector = (Rva00719CD0Vector *)vectorAddress;
	Rva00719CD0Snapshot *snapshot = (Rva00719CD0Snapshot *)snapshotAddress;
	float firstWidth = snapshot->firstWidth;
	float secondWidth = snapshot->secondWidth;
	int count = snapshot->count;
	float sampleCount = (float)count;
	float firstAmplitude = snapshot->firstAmplitude;
	float secondAmplitude = snapshot->secondAmplitude;
	float scale = Rva00719CD0ActionSlop / sampleCount;
	int mode = snapshot->mode;
	if (scale != Rva00719CD0DefaultBU)
		scale = scale + (Rva00719CD0DefaultBU - scale) * Rva00719CD0K1253;

	float coefficients[3][2];
	coefficients[1][0] = firstAmplitude;
	coefficients[2][0] = secondAmplitude;
	coefficients[1][1] = scale * firstWidth;
	coefficients[2][1] = scale * secondWidth;

	vector->end = (unsigned char *)BfmeRva00719CD0Copy(
		(Rva00719AF0Element *)vector->end,
		(Rva00719AF0Element *)vector->end,
		(Rva00719AF0Element *)vector->begin,
		reinterpret_cast<const Rva00719CD0FalseType &>(sampleCount), 0);

	Rva00719AF0Element sample;
	if (count > 0)
	{
		sampleCount = (sampleCount - Rva00719CD0DefaultBU) * Rva00719CD0K1253;
		float centerSquared = sampleCount * sampleCount;
		for (int sampleIndex = 0; sampleIndex < count; ++sampleIndex)
		{
			float offset = (float)sampleIndex - sampleCount;
			offset -= Rva00719CD0ScaleBK;
			float normalizedOffset = offset * offset;
			normalizedOffset = normalizedOffset / centerSquared;
			float weight = Rva00719CD0ZeroRange;
			if (mode > 0)
			{
				int termIndex = 0;
				do
				{
					++termIndex;
					double denominator = exp(
						normalizedOffset * coefficients[termIndex][0]);
					double reciprocal = Rva00719CD0DefaultBU / denominator;
					weight += (float)(reciprocal * coefficients[termIndex][1]);
				}
				while (termIndex < mode);
			}
			sample.x = offset;
			sample.y = 0.0f;
			sample.weight = weight;
			if (weight > Rva00719CD0Threshold)
			{
				if (vector->end != vector->capacity && vector->end != 0)
				{
					*(Rva00719AF0Element *)vector->end = sample;
					vector->end += sizeof(Rva00719AF0Element);
				}
				else
				{
					vector->insertOverflow(vector->end, sample,
						reinterpret_cast<const Rva00719CD0FalseType &>(sampleCount), 1, true);
				}
			}
		}
	}

	sample.x = 0.0f;
	sample.y = 0.0f;
	sample.weight = 0.0f;
	int elementCount = (int)(vector->end - vector->begin) / 12;
	int padding = 4 - elementCount % 4;
	while (padding > 0)
	{
		if (vector->end != vector->capacity && vector->end != 0)
		{
			*(Rva00719AF0Element *)vector->end = sample;
			vector->end += sizeof(Rva00719AF0Element);
		}
		else
		{
			vector->insertOverflow(vector->end, sample,
				reinterpret_cast<const Rva00719CD0FalseType &>(sampleCount), 1, true);
		}
		--padding;
	}
}
