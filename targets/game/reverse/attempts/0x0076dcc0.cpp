// ?d_0076dcc0@@YAXXZ
// partial score=0.1 date=2026-09-23
// cl: /MD /EHsc /Ireference/shims/stringinline
// stlport

#include "StringInline.h"
#include <map>

typedef unsigned int NameKeyType;
typedef bool Bool;

struct Rva0076DCC0Matrix
{
	float value[12];
	void Make_Identity(void);
	void Scale(float scale);
};

struct Rva0076DCC0PristineBoneInfo
{
	Rva0076DCC0Matrix matrix;
	int boneIndex;
};

typedef std::map<NameKeyType, Rva0076DCC0PristineBoneInfo> Rva0076DCC0BoneMap;

class Gen_00762380
{
public:
	AsciiString method(int index) const;
};

struct Rva0076DCC0AnimationInfo
{
	char bytes[0x1c];
};

struct Rva0076DCC0State
{
	char pad00[0x2c];
	Rva0076DCC0AnimationInfo *animationsBegin;
	Rva0076DCC0AnimationInfo *animationsEnd;
	char pad34[0x3c];
	Rva0076DCC0BoneMap pristineBones;
	char cachedBoneVectors[0x30];
	unsigned char validFlags;
};

struct Rva0076DCC0Owner
{
	void validate(void *first, void *second, Rva0076DCC0State *state, float scale);
	char pad00[0x28];
	AsciiString *modelNamesBegin;
	AsciiString *modelNamesEnd;
	char pad30[0x10];
	AsciiString *publicBonesBegin;
	AsciiString *publicBonesEnd;
};

struct Rva0076DCC0RenderObject;

extern void setFPMode(void);
extern Rva0076DCC0RenderObject *Create_Render_Obj(const char *name, float scale, int color);
extern Bool doSingleBoneName(Rva0076DCC0RenderObject *object,
	const AsciiString &boneName, Rva0076DCC0BoneMap &map);
extern void rva0076dcc0_render_class_id(Rva0076DCC0RenderObject *object, int *result);
extern void rva0076dcc0_render_get_transform(Rva0076DCC0RenderObject *object,
	Rva0076DCC0Matrix *result);
extern void rva0076dcc0_render_set_transform(Rva0076DCC0RenderObject *object,
	const Rva0076DCC0Matrix *transform);
extern void rva0076dcc0_render_set_animation(Rva0076DCC0RenderObject *object,
	void *animation, float frame, int mode);
extern void rva0076dcc0_render_release(Rva0076DCC0RenderObject *object);
extern void *rva0076dcc0_peek_animation(Rva0076DCC0RenderObject *object,
	float *frame, int *frames, int *mode, float *multiplier);
extern void *rva0076dcc0_first_animation(Rva0076DCC0AnimationInfo *animation);

void Rva0076DCC0Owner::validate(void *, void *, Rva0076DCC0State *state, float scale)
{
	if (state == 0 || (state->validFlags & 1) != 0)
		return;

	setFPMode();
	state->pristineBones.clear();
	state->validFlags |= 1;

	AsciiString model = reinterpret_cast<const Gen_00762380 *>(this)->method(0);
	Rva0076DCC0RenderObject *object = 0;
	Bool releaseObject = false;
	if (!model.isEmpty())
	{
		object = Create_Render_Obj(model.str(), scale, 0);
		releaseObject = object != 0;
	}
	if (object == 0)
		return;

	Rva0076DCC0Matrix original;
	rva0076dcc0_render_get_transform(object, &original);
	float frame = 0.0f;
	int frameCount = 0;
	int mode = 0;
	float multiplier = 1.0f;
	void *currentAnimation = rva0076dcc0_peek_animation(object, &frame, &frameCount,
		&mode, &multiplier);
	void *animation = 0;
	if (state->animationsBegin != state->animationsEnd)
		animation = rva0076dcc0_first_animation(state->animationsBegin);
	else
		animation = currentAnimation;
	if (animation != 0)
	{
		rva0076dcc0_render_set_animation(object, animation, 0.0f, 2);
	}

	Rva0076DCC0Matrix identity;
	identity.Make_Identity();
	identity.Scale(scale);
	rva0076dcc0_render_set_transform(object, &identity);

	for (AsciiString *it = publicBonesBegin; it != publicBonesEnd; ++it)
		doSingleBoneName(object, *it, state->pristineBones);

	rva0076dcc0_render_set_transform(object, &original);
	if (currentAnimation != 0)
		rva0076dcc0_render_set_animation(object, currentAnimation, frame, mode);
	if (releaseObject)
		rva0076dcc0_render_release(object);
}
