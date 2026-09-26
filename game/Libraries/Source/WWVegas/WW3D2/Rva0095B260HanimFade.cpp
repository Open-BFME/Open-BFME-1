// cl: /DNDEBUG /MD /G6 /EHsc

class TimeCodedMotionChannelClass
{
public:
	void Get_Vector(float frame, float *setvec);
};

class AdaptiveDeltaMotionChannelClass
{
public:
	void Get_Vector(float frame, float *setvec);
};

struct Rva0095B260Node
{
	int flavor;
	union
	{
		TimeCodedMotionChannelClass *time_coded[5];
		AdaptiveDeltaMotionChannelClass *adaptive[5];
	};
	void *visibility;
};

class Rva0095B260Anim
{
public:
	float Get_Fade(int pivot, float frame);

private:
	unsigned char before_flavor[0x48];
	int flavor;
	float frame_rate;
	Rva0095B260Node *node_motion;
};

float Rva0095B260Anim::Get_Fade(int pivot, float frame)
{
	Rva0095B260Node *motion = &node_motion[pivot];
	float *value = reinterpret_cast<float *>(&pivot);
	*value = 1.0f;

	switch (flavor)
	{
		case 1:
			if (motion->adaptive[4] != 0)
				motion->adaptive[4]->Get_Vector(frame, value);
			break;

		case 0:
			if (motion->time_coded[4] != 0)
				motion->time_coded[4]->Get_Vector(frame, value);
			break;
	}

	return *value;
}
