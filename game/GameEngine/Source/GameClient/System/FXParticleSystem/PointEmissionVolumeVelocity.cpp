// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Point emission-volume virtual slot zero, RVA 0x005FA400, complete 56-byte body.
// Vtables VA 0x01111864 and VA 0x011122D8 reach it through ILT 0x00036318.
// The method name and unused argument words are address-qualified ABI views.

namespace FXParticleSystem {

struct Coord3D {
	Coord3D(void) {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	float x;
	float y;
	float z;
};

// Address-qualified cdecl output helper: retail ILT RVA 0x000107EE reaches
// body RVA 0x005FAD00. Its full 246-byte body fills a normalized random vector.
extern "C" Coord3D *Rva005FAD00FillUnitVector(Coord3D *out);

class PointEmissionVolumeModule {
public:
	Coord3D Rva005FA400Velocity(unsigned int, float scale, unsigned int);
};

Coord3D PointEmissionVolumeModule::Rva005FA400Velocity(
	unsigned int, float scale, unsigned int)
{
	Coord3D direction;
	Rva005FAD00FillUnitVector(&direction);

	Coord3D result;
	result.x = direction.x * scale;
	result.y = direction.y * scale;
	result.z = direction.z * scale;
	return result;
}

} // namespace FXParticleSystem
