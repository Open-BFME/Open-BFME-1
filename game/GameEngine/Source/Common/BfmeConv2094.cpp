struct Coord3D
{
	float x;
	float y;
	float z;
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	void resolveOwnerPosition(Coord3D *out, bool *valid);
};

Coord3D * __stdcall bfmeGetPosXY(Coord3D *out, AudioEventRTS *ev, bool *valid)
{
	if (!ev->isPositionalAudio())
	{
		*valid = false;

		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
	}
	else
	{
		ev->resolveOwnerPosition(out, valid);
	}

	return out;
}
