// ??0ParticleBufferClass@@QAE@ABV0@@Z
// partial score=0.78 date=2026-09-02
// cl: same as part_buf.cpp
// banked attempt for ??0ParticleBufferClass@@QAE@ABV0@@Z @ 0x00989A20
ParticleBufferClass::ParticleBufferClass(const ParticleBufferClass & src) :
	RenderObjClass(src),
	NewParticleQueue(NULL),
	NewParticleQueueStart(0U),
	NewParticleQueueEnd(0U),
	NewParticleQueueCount(0U),
	RenderMode(src.RenderMode),
	FrameMode(src.FrameMode),
	MaxAge(src.MaxAge),
	FutureStartTime(src.FutureStartTime),
	LastUpdateTime(WW3D::Get_Sync_Time()),
	IsEmitterDead(false),
	MaxSize(src.MaxSize),
	MaxNum(src.MaxNum),
	Start(0U),
	End(0U),
	NewEnd(0U),
	NonNewNum(0),
	NewNum(0),
	BoundingBox(Vector3(0,0,0),Vector3(0,0,0)),
	BoundingBoxDirty(true),
	NumColorKeyFrames(src.NumColorKeyFrames),
	ColorKeyFrameTimes(NULL),
	ColorKeyFrameValues(NULL),
	ColorKeyFrameDeltas(NULL),
	NumAlphaKeyFrames(src.NumAlphaKeyFrames),
	AlphaKeyFrameTimes(NULL),
	AlphaKeyFrameValues(NULL),
	AlphaKeyFrameDeltas(NULL),
	NumSizeKeyFrames(src.NumSizeKeyFrames),
	SizeKeyFrameTimes(NULL),
	SizeKeyFrameValues(NULL),
	SizeKeyFrameDeltas(NULL),
	NumRotationKeyFrames(src.NumRotationKeyFrames),
	RotationKeyFrameTimes(NULL),
	RotationKeyFrameValues(NULL),
	HalfRotationKeyFrameDeltas(NULL),
	OrientationKeyFrameValues(NULL),
	NumFrameKeyFrames(src.NumFrameKeyFrames),
	FrameKeyFrameTimes(NULL),
	FrameKeyFrameValues(NULL),
	FrameKeyFrameDeltas(NULL),
	NumBlurTimeKeyFrames(src.NumBlurTimeKeyFrames),
	BlurTimeKeyFrameTimes(NULL),
	BlurTimeKeyFrameValues(NULL),
	BlurTimeKeyFrameDeltas(NULL),
	DefaultTailDiffuse(src.DefaultTailDiffuse),
	NumRandomColorEntriesMinus1(src.NumRandomColorEntriesMinus1),
	RandomColorEntries(NULL),
	NumRandomAlphaEntriesMinus1(src.NumRandomAlphaEntriesMinus1),
	RandomAlphaEntries(NULL),
	NumRandomSizeEntriesMinus1(src.NumRandomSizeEntriesMinus1),
	RandomSizeEntries(NULL),
	NumRandomRotationEntriesMinus1(src.NumRandomRotationEntriesMinus1),
	RandomRotationEntries(NULL),
	NumRandomOrientationEntriesMinus1(src.NumRandomOrientationEntriesMinus1),
	RandomOrientationEntries(NULL),
	NumRandomFrameEntriesMinus1(src.NumRandomFrameEntriesMinus1),
	RandomFrameEntries(NULL),
	NumRandomBlurTimeEntriesMinus1(src.NumRandomBlurTimeEntriesMinus1),
	RandomBlurTimeEntries(NULL),
	ColorRandom(src.ColorRandom),
	OpacityRandom(src.OpacityRandom),
	SizeRandom(src.SizeRandom),
	RotationRandom(src.RotationRandom),
	FrameRandom(src.FrameRandom),
	BlurTimeRandom(src.BlurTimeRandom),
	InitialOrientationRandom(src.InitialOrientationRandom),
	PointGroup(NULL),
	LineRenderer(NULL),
	LineGroup(NULL),
	Diffuse(NULL),
	TailDiffuse(NULL),
	Color(NULL),
	Alpha(NULL),
	Size(NULL),
	Orientation(NULL),
	Frame(NULL),
	UCoord(NULL),
	TailPosition(NULL),
	APT(NULL),
	GroupID(NULL),
	PingPongPosition(src.PingPongPosition),
	Velocity(NULL),
	TimeStamp(NULL),
	Emitter(src.Emitter),
	DecimationThreshold(src.DecimationThreshold),
	ProjectedArea(0.0f),
	CurrentGroupID(src.CurrentGroupID)
{
	Position[0] = NULL;
	Position[1] = NULL;

	unsigned int i;

	LodCount = MIN(MaxNum, 17);
	LodBias = src.LodBias;

	if (src.Color) {
		Color = NEW_REF( ShareBufferClass<Vector3> , (MaxNum, "ParticleBufferClass::Color", 0) );

		ColorKeyFrameTimes = W3DNEWARRAY unsigned int [NumColorKeyFrames];
		ColorKeyFrameValues = W3DNEWARRAY Vector3 [NumColorKeyFrames];
		ColorKeyFrameDeltas = W3DNEWARRAY Vector3 [NumColorKeyFrames];
		for (i = 0; i < NumColorKeyFrames; i++) {
			ColorKeyFrameTimes[i] = src.ColorKeyFrameTimes[i];
			ColorKeyFrameValues[i] = src.ColorKeyFrameValues[i];
			ColorKeyFrameDeltas[i] = src.ColorKeyFrameDeltas[i];
		}

		if (src.RandomColorEntries) {
			RandomColorEntries = W3DNEWARRAY Vector3 [NumRandomColorEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomColorEntriesMinus1; j++) {
				RandomColorEntries[j] = src.RandomColorEntries[j];
			}
		}
	} else {
		ColorKeyFrameValues = W3DNEWARRAY Vector3 [1];
		ColorKeyFrameValues[0] = src.ColorKeyFrameValues[0];
	}

	if (src.Alpha) {
		Alpha = NEW_REF( ShareBufferClass<float> , (MaxNum, "ParticleBufferClass::Alpha", 0) );

		AlphaKeyFrameTimes = W3DNEWARRAY unsigned int [NumAlphaKeyFrames];
		AlphaKeyFrameValues = W3DNEWARRAY float [NumAlphaKeyFrames];
		AlphaKeyFrameDeltas = W3DNEWARRAY float [NumAlphaKeyFrames];
		for (i = 0; i < NumAlphaKeyFrames; i++) {
			AlphaKeyFrameTimes[i] = src.AlphaKeyFrameTimes[i];
			AlphaKeyFrameValues[i] = src.AlphaKeyFrameValues[i];
			AlphaKeyFrameDeltas[i] = src.AlphaKeyFrameDeltas[i];
		}

		if (src.RandomAlphaEntries) {
			RandomAlphaEntries = W3DNEWARRAY float [NumRandomAlphaEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomAlphaEntriesMinus1; j++) {
				RandomAlphaEntries[j] = src.RandomAlphaEntries[j];
			}
		}
	} else {
		AlphaKeyFrameValues = W3DNEWARRAY float [1];
		AlphaKeyFrameValues[0] = src.AlphaKeyFrameValues[0];
	}

	if (src.Size) {
		Size = NEW_REF( ShareBufferClass<float> , (MaxNum, "ParticleBufferClass::Size", 0) );

		SizeKeyFrameTimes = W3DNEWARRAY unsigned int [NumSizeKeyFrames];
		SizeKeyFrameValues = W3DNEWARRAY float [NumSizeKeyFrames];
		SizeKeyFrameDeltas = W3DNEWARRAY float [NumSizeKeyFrames];
		for (i = 0; i < NumSizeKeyFrames; i++) {
			SizeKeyFrameTimes[i] = src.SizeKeyFrameTimes[i];
			SizeKeyFrameValues[i] = src.SizeKeyFrameValues[i];
			SizeKeyFrameDeltas[i] = src.SizeKeyFrameDeltas[i];
		}

		if (src.RandomSizeEntries) {
			RandomSizeEntries = W3DNEWARRAY float [NumRandomSizeEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomSizeEntriesMinus1; j++) {
				RandomSizeEntries[j] = src.RandomSizeEntries[j];
			}
		}
	} else {
		SizeKeyFrameValues = W3DNEWARRAY float [1];
		SizeKeyFrameValues[0] = src.SizeKeyFrameValues[0];
	}

	if (src.Orientation) {
		Orientation = NEW_REF( ShareBufferClass<uint8> , (MaxNum, "ParticleBufferClass::Orientation", 0) );

		RotationKeyFrameTimes = W3DNEWARRAY unsigned int [NumRotationKeyFrames];
		RotationKeyFrameValues = W3DNEWARRAY float [NumRotationKeyFrames];
		HalfRotationKeyFrameDeltas = W3DNEWARRAY float [NumRotationKeyFrames];
		OrientationKeyFrameValues = W3DNEWARRAY float [NumRotationKeyFrames];
		for (i = 0; i < NumRotationKeyFrames; i++) {
			RotationKeyFrameTimes[i] = src.RotationKeyFrameTimes[i];
			RotationKeyFrameValues[i] = src.RotationKeyFrameValues[i];
			HalfRotationKeyFrameDeltas[i] = src.HalfRotationKeyFrameDeltas[i];
			OrientationKeyFrameValues[i] = src.OrientationKeyFrameValues[i];
		}

		if (src.RandomRotationEntries) {
			RandomRotationEntries = W3DNEWARRAY float [NumRandomRotationEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomRotationEntriesMinus1; j++) {
				RandomRotationEntries[j] = src.RandomRotationEntries[j];
			}
		}

		if (src.RandomOrientationEntries) {
			RandomOrientationEntries = W3DNEWARRAY float [NumRandomOrientationEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomOrientationEntriesMinus1; j++) {
				RandomOrientationEntries[j] = src.RandomOrientationEntries[j];
			}
		}

	} else {
	}


	if (src.Frame || src.UCoord) {
		if (src.Frame) {
			Frame = NEW_REF( ShareBufferClass<uint8> , (MaxNum, "ParticleBufferClass::Frame", 0) );
		} else {
			UCoord = NEW_REF( ShareBufferClass<float>, (MaxNum, "ParticleBufferClass::UCoord", 0) );
		}

		FrameKeyFrameTimes = W3DNEWARRAY unsigned int [NumFrameKeyFrames];
		FrameKeyFrameValues = W3DNEWARRAY float [NumFrameKeyFrames];
		FrameKeyFrameDeltas = W3DNEWARRAY float [NumFrameKeyFrames];
		for (i = 0; i < NumFrameKeyFrames; i++) {
			FrameKeyFrameTimes[i] = src.FrameKeyFrameTimes[i];
			FrameKeyFrameValues[i] = src.FrameKeyFrameValues[i];
			FrameKeyFrameDeltas[i] = src.FrameKeyFrameDeltas[i];
		}

		if (src.RandomFrameEntries) {
			RandomFrameEntries = W3DNEWARRAY float [NumRandomFrameEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomFrameEntriesMinus1; j++) {
				RandomFrameEntries[j] = src.RandomFrameEntries[j];
			}
		}
	} else {
		FrameKeyFrameValues = W3DNEWARRAY float [1];
		FrameKeyFrameValues[0] = src.FrameKeyFrameValues[0];
	}

	if (NumBlurTimeKeyFrames > 0) {
		BlurTimeKeyFrameTimes = W3DNEWARRAY unsigned int [NumBlurTimeKeyFrames];
		BlurTimeKeyFrameValues = W3DNEWARRAY float [NumBlurTimeKeyFrames];
		BlurTimeKeyFrameDeltas = W3DNEWARRAY float [NumBlurTimeKeyFrames];
		for (i = 0; i < NumBlurTimeKeyFrames; i++) {
			BlurTimeKeyFrameTimes[i] = src.BlurTimeKeyFrameTimes[i];
			BlurTimeKeyFrameValues[i] = src.BlurTimeKeyFrameValues[i];
			BlurTimeKeyFrameDeltas[i] = src.BlurTimeKeyFrameDeltas[i];
		}

		if (src.RandomBlurTimeEntries) {
			RandomBlurTimeEntries = W3DNEWARRAY float [NumRandomBlurTimeEntriesMinus1 + 1];
			for (unsigned int j = 0; j <= NumRandomBlurTimeEntriesMinus1; j++) {
				RandomBlurTimeEntries[j] = src.RandomBlurTimeEntries[j];
			}
		}
	} else {
		BlurTimeKeyFrameValues = W3DNEWARRAY float [1];
		BlurTimeKeyFrameValues[0] = src.BlurTimeKeyFrameValues[0];
	}

	NewParticleQueue = W3DNEWARRAY NewParticleStruct[MaxNum];

	Accel = src.Accel;
	HasAccel = src.HasAccel;

	switch (RenderMode)
	{
	case W3D_EMITTER_RENDER_MODE_TRI_PARTICLES:
		{
			WWASSERT(src.PointGroup);
			PointGroup = W3DNEW PointGroupClass();
			PointGroup->Set_Flag(PointGroupClass::TRANSFORM, true);
			PointGroup->Set_Flag(PointGroupClass::BILLBOARD, true);
			PointGroup->Set_Texture(src.PointGroup->Peek_Texture());
			PointGroup->Set_Shader(src.PointGroup->Get_Shader());
			PointGroup->Set_Point_Mode(PointGroupClass::TRIS);
			PointGroup->Set_Frame_Row_Column_Count_Log2(src.PointGroup->Get_Frame_Row_Column_Count_Log2());
		}
		break;
	case W3D_EMITTER_RENDER_MODE_QUAD_PARTICLES:
		{
			WWASSERT(src.PointGroup);
			PointGroup = W3DNEW PointGroupClass();
			PointGroup->Set_Flag(PointGroupClass::TRANSFORM, true);
			PointGroup->Set_Flag(PointGroupClass::BILLBOARD, true);
			PointGroup->Set_Texture(src.PointGroup->Peek_Texture());
			PointGroup->Set_Shader(src.PointGroup->Get_Shader());
			PointGroup->Set_Point_Mode(PointGroupClass::QUADS);
			PointGroup->Set_Frame_Row_Column_Count_Log2(src.PointGroup->Get_Frame_Row_Column_Count_Log2());
		}
		break;
	case W3D_EMITTER_RENDER_MODE_LINE:
		{
			WWASSERT(src.LineRenderer);
			LineRenderer = W3DNEW SegLineRendererClass(*src.LineRenderer);
		}
		break;
	case W3D_EMITTER_RENDER_MODE_LINEGRP_TETRA:
		{
			WWASSERT(src.LineGroup);
			LineGroup = W3DNEW LineGroupClass();
			LineGroup->Set_Flag(LineGroupClass::TRANSFORM, true);
			LineGroup->Set_Texture(src.LineGroup->Peek_Texture());
			LineGroup->Set_Shader(src.LineGroup->Get_Shader());
			LineGroup->Set_Line_Mode(LineGroupClass::TETRAHEDRON);
			TailPosition = NEW_REF( ShareBufferClass<Vector3> , (MaxNum, "ParticleBufferClass::TailPosition", 0) );
			Set_Force_Visible(1);
		}
		break;
	case W3D_EMITTER_RENDER_MODE_LINEGRP_PRISM:
		{
			WWASSERT(src.LineGroup);
			LineGroup = W3DNEW LineGroupClass();
			LineGroup->Set_Flag(LineGroupClass::TRANSFORM, true);
			LineGroup->Set_Texture(src.LineGroup->Peek_Texture());
			LineGroup->Set_Shader(src.LineGroup->Get_Shader());
			LineGroup->Set_Line_Mode(LineGroupClass::PRISM);
			TailPosition = NEW_REF( ShareBufferClass<Vector3> , (MaxNum, "ParticleBufferClass::TailPosition", 0) );
			Set_Force_Visible(1);
		}
		break;
	default:
		WWASSERT(0);
		break;
	}

	Position[0] = NEW_REF( ShareBufferClass<Vector3> , (MaxNum, "ParticleBufferClass::Position", 0) );
	if (PingPongPosition) {
		Position[1] = NEW_REF( ShareBufferClass<Vector3> , (MaxNum, "ParticleBufferClass::Position", 0) );
	}
	APT = NEW_REF( ShareBufferClass<unsigned int> , (MaxNum, "ParticleBufferClass::APT", 0) );
	GroupID = NEW_REF( ShareBufferClass<unsigned char> , (MaxNum, "ParticleBufferClass::GroupID", 0) );
	Velocity = W3DNEWARRAY Vector3[MaxNum];
	TimeStamp = W3DNEWARRAY unsigned int[MaxNum];

	int minlod = Calculate_Cost_Value_Arrays(1.0f, Value, Cost);

	if (Get_LOD_Level() < minlod) Set_LOD_Level(minlod);

	TotalActiveCount++;
}

