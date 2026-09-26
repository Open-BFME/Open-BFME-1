// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?getAttenuation@Rva0069B040Owner@@QAEMPAVAudioEventRTS@@@Z
// Positional falloff 0..1. ZH MilesAudioManager::getEffectiveVolume uses the
// same min/max and ST_GLOBAL split; BFME returns only the linear factor
// (max-dist)/(max-min) and resolves position via AudioEventRTS::resolveOwnerPosition.

#include <math.h>

struct Coord3D
{
	float x, y, z;

	float length(void) const
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	void sub(const Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
};

struct AudioEventInfo
{
	char m_pad0[0x38];
	unsigned char m_type;
	char m_pad1[0x74 - 0x39];
	float m_minDistance;
	float m_maxDistance;
};

class AudioEventRTS
{
public:
	void resolveOwnerPosition(Coord3D *pos, bool *ok);

	char m_pad[8];
	AudioEventInfo *m_info;
};

struct AudioSettings
{
	char m_pad[0x34];
	int m_globalMinRange;
	int m_globalMaxRange;
};

class Rva0069B040Owner
{
public:
	float getAttenuation(AudioEventRTS *event);

	char m_pad[0xc];
	AudioSettings *m_settings;
	void *m_pad10;
	Coord3D m_listenerPosition;
};

float Rva0069B040Owner::getAttenuation(AudioEventRTS *event)
{
	Coord3D pos;
	bool ok;
	event->resolveOwnerPosition(&pos, &ok);
	if (ok)
	{
		Coord3D distance;
		distance.x = m_listenerPosition.x;
		distance.y = m_listenerPosition.y;
		distance.z = m_listenerPosition.z;
		distance.sub(&pos);

		AudioEventInfo *info = event->m_info;
		float minD;
		float maxD;
		if (info->m_type & 8)
		{
			minD = (float)m_settings->m_globalMinRange;
			maxD = (float)m_settings->m_globalMaxRange;
		}
		else
		{
			minD = info->m_minDistance;
			maxD = info->m_maxDistance;
		}

		float dist = distance.length();
		if (dist >= maxD)
			return 0.0f;
		if (dist > minD && minD < maxD)
			return (maxD - dist) / (maxD - minD);
		return 1.0f;
	}
	return 0.0f;
}
