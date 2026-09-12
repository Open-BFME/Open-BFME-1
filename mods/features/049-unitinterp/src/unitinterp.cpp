// 049-unitinterp (revision 2) -- render-time interpolation for ordinary BFME
// model draws, paced on the same wall-clock grid the Astra sub-step admission
// cave uses.
//
// Installed around Display::drawViews (retail RVA 0x0040DA30) by
// build/astra_unitinterp_patch.py, on top of D:\BFME1\lotrbfme-astra.exe.
//
// WHAT WAS WRONG WITH REVISION 1
//   Revision 1 blended the last two authoritative transforms with
//   GameEngine::m_clientFrameRatio.  That ratio ramps 1/6 .. 6/6 across the
//   whole 200 ms logic frame, but the transforms it was blending change every
//   admitted sub-step (33.3 ms).  So the rendered position lagged by a
//   different fraction on each sub-step -- a six-step sawtooth on top of the
//   motion -- and the two 60 Hz renders of one sub-step got the same alpha, so
//   nothing was smoothed inside a step either.  The user's verdict was "worse".
//
// THE MODEL USED HERE
//   The Astra cave admits one simulation phase every QPF/30 counter ticks and
//   keeps its accumulator, last counter sample, and interval in the .bfmemod
//   state block (VA 0x01416400).  From that block a continuous sub-step time
//   is available at every draw:
//
//       tau = admittedSteps + (accumulated + (now - lastSample)) / interval
//
//   Each visible model transform is sampled whenever it changes and stamped
//   with the admitted-step count it appeared on.  The pass then renders every
//   moving model at tau - DISPLAY_DELAY_STEPS, blending between the two
//   samples that bracket that time.  A constant delay a little over one step
//   guarantees the bracketing samples already exist, so the displayed motion
//   is continuous across step boundaries instead of snapping to the newest
//   sample.  Cost: about 40 ms of visual latency on unit motion.
//
//   The animation clock (WW3D::SyncTime, advanced by [0x012BB1CC] ms once per
//   client frame) is steered to real time by a small deficit controller, so
//   animations neither run at 1.9x (the stock 33 ms constant on a 60 Hz loop)
//   nor depend on the exact frame rate (a fixed 17 ms constant would).
//
//   The payload never touches Thing/Drawable positions or the simulation.
//   W3DModelDraw is the only BFME DrawModule exposing the ObjectDrawInterface
//   used here; its secondary interface is at module+0x0C and its
//   RenderObjClass pointer is at interface+0x28 (equivalently module+0x34).
//   Rope, debris, laser and tree modules do not expose that interface and are
//   consequently not included by this pass.  Transforms are restored after the
//   complete view pass so nothing outside the render sees a blended matrix.
//
//   In any state where the pacing cave is inactive (menus, multiplayer,
//   mode 5) the pass does nothing and the animation constant is put back to
//   retail's 33.

typedef unsigned char Byte;
typedef unsigned short Half;
typedef unsigned int Unsigned;
typedef float Real;
typedef __int64 Int64;

// MSVC 7.1 emits this marker for x87 arithmetic.  There is no CRT behind an
// appended BFME code cave.
extern "C" const int _fltused = 0;

struct Matrix3D
{
    Real m[12];
};

struct TransformRecord
{
    void *renderObject;
    void *drawable;
    Matrix3D older;      // authoritative transform first seen on stepOlder
    Matrix3D previous;   // ... on stepPrevious
    Matrix3D current;    // ... on stepCurrent (what the render object holds now)
    int stepOlder;
    int stepPrevious;
    int stepCurrent;
    Unsigned seen;
    int valid;
    int snap;
    int applied;
};

struct IndexSlot
{
    Half record;       // pool index + 1, 0 = empty
    Half generation;   // slot is live only when equal to s_generation
};

enum
{
    POOL_SIZE = 8192,
    INDEX_SIZE = 16384,
    INDEX_MASK = INDEX_SIZE - 1,
    MAX_DRAWABLES = 16384,
    MAX_DRAW_MODULES = 64,
    REBUILD_EVERY = 512,
    RETAIL_ANIMATION_MS = 33
};

// Rendered time sits this many sub-steps behind the newest admitted step.
// A sample for step k is first observable at tau in [k, k+0.55] (the next
// draw after the admit, or one draw later on a frame whose animation delta
// was zero), so anything above ~1.05 is continuous; 1.25 keeps a margin.
#define DISPLAY_DELAY_STEPS 1.25f

// Largest animation-time deficit the controller will pay back in one client
// frame.  Bounds the jump after a pause or a stall.
#define MAX_ANIMATION_CATCHUP_MS 40.0f

// The cave section is zero-filled by the extender, so these require no CRT
// startup or static constructor.
static TransformRecord s_pool[POOL_SIZE];
static IndexSlot s_index[INDEX_SIZE];
static Half s_free[POOL_SIZE];
static int s_freeCount;
static Half s_applied[POOL_SIZE];
static int s_appliedCount;
static Half s_generation;
static int s_initialized;
static Unsigned s_stamp;
static Unsigned s_depth;

// sub-step grid tracking
static Int64 s_previousAccumulated;
static int s_haveAccumulated;
static int s_previousPeriod;
static int s_havePeriod;
static int s_step;

// animation clock control
static Int64 s_lastDrawTicks;
static int s_haveDrawTicks;
static Real s_desiredMs;
static Real s_actualMs;
static Unsigned s_lastSyncTime;
static int s_haveSyncTime;

#define TheGameClient (*(void **)0x012F1464)
#define TheGameEngine (*(void **)0x012ED524)
#define TheAnimationMsPerStep (*(int *)0x012BB1CC)
#define WW3DSyncTime (*(Unsigned *)0x0133F420)

// Astra pacing cave state block (see D:\BFME1\lotrbfme-astra-notes.txt).
#define PaceActive (*(int *)0x01416400)
#define PaceLastCounter (*(Int64 *)0x01416404)
#define PaceAccumulated (*(Int64 *)0x0141640C)
#define PaceFrequency (*(Int64 *)0x01416414)
#define PaceInterval (*(Int64 *)0x0141641C)
#define PaceFrequencyReady (*(int *)0x01416424)

// kernel32!QueryPerformanceCounter through the game's own import slot.
typedef int (__stdcall *CounterFn)(Int64 *);
#define QueryPerformanceCounterSlot (*(CounterFn *)0x01358EB4)

enum
{
    GAMECLIENT_DRAWABLE_LIST = 0x10,
    DRAWABLE_NEXT = 0x104,
    DRAWABLE_MODULES = 0x150,
    DRAWMODULE_GET_OBJECT_INTERFACE = 0x9C,
    MODEL_INTERFACE_RENDER_OBJECT = 0x28,
    RENDER_OBJECT_TRANSFORM = 0x18,
    RENDER_OBJECT_SET_TRANSFORM = 0x54,
    ENGINE_CLIENT_FRAME_PERIOD = 0x30
};

typedef void *(__fastcall *GetObjectInterface)(void *self, void *edx);
typedef void (__fastcall *SetTransform)(void *self, void *edx,
                                         const Matrix3D *transform);

static int in_image(const void *value)
{
    Unsigned address = (Unsigned)value;
    // BFME is a fixed-base image.  This rejects a bogus field read before it
    // is used as either a vtable or a function pointer.
    return address >= 0x00400000u && address < 0x01400000u;
}

static Real to_real(int value)
{
    return (Real)value;
}

// Round-to-nearest without _ftol: adding 1.5 * 2^23 leaves the integer in
// the low mantissa bits of the single-precision store.  Valid for |v| < 2^22
// and independent of the x87 precision-control setting the game applies.
static int round_real(Real value)
{
    union Bits
    {
        Real real;
        int bits;
    } u;
    u.real = value + 12582912.0f;
    return u.bits - 0x4B400000;
}

static void copy_matrix(Matrix3D *destination, const Matrix3D *source)
{
    for (int i = 0; i < 12; ++i)
        destination->m[i] = source->m[i];
}

static int same_matrix(const Matrix3D *a, const Matrix3D *b)
{
    for (int i = 0; i < 12; ++i)
        if (a->m[i] != b->m[i])
            return 0;
    return 1;
}

// One Newton refinement of the classic inverse-square-root estimate keeps
// basis rows normalized without importing sqrt from the CRT.
static Real inverse_sqrt(Real value)
{
    union Bits
    {
        Real real;
        Unsigned bits;
    } estimate;

    if (value <= 0.0000000001f)
        return 1.0f;
    estimate.real = value;
    estimate.bits = 0x5F3759DFu - (estimate.bits >> 1);
    estimate.real = estimate.real *
        (1.5f - 0.5f * value * estimate.real * estimate.real);
    return estimate.real;
}

static Real row_length(const Matrix3D *matrix, int row)
{
    int base = row * 4;
    Real squared = matrix->m[base] * matrix->m[base] +
                   matrix->m[base + 1] * matrix->m[base + 1] +
                   matrix->m[base + 2] * matrix->m[base + 2];
    return squared * inverse_sqrt(squared);
}

static void blend_matrix(const Matrix3D *previous, const Matrix3D *current,
                         Real factor, Matrix3D *result)
{
    Real opposite = 1.0f - factor;

    for (int row = 0; row < 3; ++row)
    {
        int base = row * 4;
        Real x = previous->m[base] * opposite + current->m[base] * factor;
        Real y = previous->m[base + 1] * opposite + current->m[base + 1] * factor;
        Real z = previous->m[base + 2] * opposite + current->m[base + 2] * factor;
        Real lengthSquared = x * x + y * y + z * z;

        // Preserve any model scale while correcting the small shrink caused
        // by a linear rotation blend.  Translation is elements 3, 7 and 11.
        if (lengthSquared > 0.0000000001f)
        {
            Real scale = row_length(previous, row) * opposite +
                         row_length(current, row) * factor;
            Real multiplier = scale * inverse_sqrt(lengthSquared);
            result->m[base] = x * multiplier;
            result->m[base + 1] = y * multiplier;
            result->m[base + 2] = z * multiplier;
        }
        else
        {
            result->m[base] = current->m[base];
            result->m[base + 1] = current->m[base + 1];
            result->m[base + 2] = current->m[base + 2];
        }
    }

    result->m[3] = previous->m[3] * opposite + current->m[3] * factor;
    result->m[7] = previous->m[7] * opposite + current->m[7] * factor;
    result->m[11] = previous->m[11] * opposite + current->m[11] * factor;
}

static int is_snap(const Matrix3D *previous, const Matrix3D *current)
{
    Real dx = current->m[3] - previous->m[3];
    Real dy = current->m[7] - previous->m[7];
    Real dz = current->m[11] - previous->m[11];

    // Ordinary BFME movement is far below this 50-world-unit jump per step;
    // a teleport/model replacement should appear immediately.
    if (dx * dx + dy * dy + dz * dz > 2500.0f)
        return 1;

    // Avoid the zero-vector midpoint of a 180-degree basis reversal.
    for (int row = 0; row < 3; ++row)
    {
        int base = row * 4;
        Real dot = previous->m[base] * current->m[base] +
                   previous->m[base + 1] * current->m[base + 1] +
                   previous->m[base + 2] * current->m[base + 2];
        if (dot < -0.25f)
            return 1;
    }
    return 0;
}

// ---- record table ---------------------------------------------------------
// Open-addressed index over a fixed record pool.  The index is invalidated
// wholesale by bumping the generation, then rebuilt from the records that
// were seen on the last two draws, so no CRT memset is needed and a lookup
// never walks a table full of dead lifetimes.

static Unsigned hash_pointer(const void *pointer)
{
    Unsigned h = ((Unsigned)pointer >> 4) * 2654435761u;
    return (h >> 18) & INDEX_MASK;
}

static void ensure_initialized()
{
    if (s_initialized)
        return;
    for (int i = 0; i < POOL_SIZE; ++i)
        s_free[i] = (Half)(POOL_SIZE - 1 - i);
    s_freeCount = POOL_SIZE;
    s_generation = 1;
    s_initialized = 1;
}

static void index_insert(int poolIndex)
{
    Unsigned slot = hash_pointer(s_pool[poolIndex].renderObject);
    for (int probe = 0; probe < INDEX_SIZE; ++probe)
    {
        IndexSlot *entry = &s_index[slot];
        if (entry->generation != s_generation || entry->record == 0)
        {
            entry->record = (Half)(poolIndex + 1);
            entry->generation = s_generation;
            return;
        }
        slot = (slot + 1) & INDEX_MASK;
    }
}

static void rebuild_index()
{
    ++s_generation;
    if (s_generation == 0)
        s_generation = 1;

    s_freeCount = 0;
    for (int i = 0; i < POOL_SIZE; ++i)
    {
        TransformRecord *record = &s_pool[i];
        if (record->renderObject != 0 && record->seen + 1 >= s_stamp)
        {
            index_insert(i);
        }
        else
        {
            record->renderObject = 0;
            record->applied = 0;
            s_free[s_freeCount++] = (Half)i;
        }
    }
}

static TransformRecord *find_record(void *drawable, void *renderObject)
{
    Unsigned slot = hash_pointer(renderObject);
    for (int probe = 0; probe < INDEX_SIZE; ++probe)
    {
        IndexSlot *entry = &s_index[slot];
        if (entry->generation != s_generation || entry->record == 0)
        {
            if (s_freeCount == 0)
                return 0;
            int poolIndex = s_free[--s_freeCount];
            TransformRecord *record = &s_pool[poolIndex];
            record->renderObject = renderObject;
            record->drawable = drawable;
            record->valid = 0;
            record->applied = 0;
            record->seen = 0;
            entry->record = (Half)(poolIndex + 1);
            entry->generation = s_generation;
            return record;
        }

        TransformRecord *record = &s_pool[entry->record - 1];
        if (record->renderObject == renderObject &&
            record->drawable == drawable)
            return record;
        slot = (slot + 1) & INDEX_MASK;
    }
    return 0;
}

// ---- render object access -------------------------------------------------

static void set_render_transform(void *renderObject, const Matrix3D *matrix)
{
    if (renderObject == 0)
        return;

    void **vtable = *(void ***)renderObject;
    if (!in_image(vtable))
        return;

    void *function = vtable[RENDER_OBJECT_SET_TRANSFORM / 4];
    if (!in_image(function))
        return;

    ((SetTransform)function)(renderObject, 0, matrix);
}

static void visit(void *drawable, void *renderObject, int interpolate, Real tau)
{
    if (renderObject == 0)
        return;

    void **renderVtable = *(void ***)renderObject;
    if (!in_image(renderVtable))
        return;
    if (!in_image(renderVtable[RENDER_OBJECT_SET_TRANSFORM / 4]))
        return;

    const Matrix3D *authoritative =
        (const Matrix3D *)((const Byte *)renderObject + RENDER_OBJECT_TRANSFORM);
    TransformRecord *record = find_record(drawable, renderObject);
    if (record == 0)
        return;

    // A drawable that disappeared and later reappeared may reuse the same
    // address.  Treat that as a new visual object so spawn/death/removal
    // cannot interpolate from an old lifetime.
    if (record->seen + 1 != s_stamp)
        record->valid = 0;

    if (!record->valid)
    {
        copy_matrix(&record->older, authoritative);
        copy_matrix(&record->previous, authoritative);
        copy_matrix(&record->current, authoritative);
        record->stepOlder = s_step;
        record->stepPrevious = s_step;
        record->stepCurrent = s_step;
        record->valid = 1;
        record->snap = 1; // spawn/first observation: never smear it in
    }
    else if (!same_matrix(&record->current, authoritative))
    {
        copy_matrix(&record->older, &record->previous);
        record->stepOlder = record->stepPrevious;
        copy_matrix(&record->previous, &record->current);
        record->stepPrevious = record->stepCurrent;
        copy_matrix(&record->current, authoritative);
        record->stepCurrent = s_step;
        record->snap = is_snap(&record->previous, &record->current);
    }
    record->seen = s_stamp;

    if (!interpolate || record->snap || record->applied)
        return;

    // Two samples on the same admitted step means the transform is driven
    // by the client every frame (not by the simulation); leave it alone.
    if (record->stepCurrent == record->stepPrevious)
        return;

    Real stepCurrent = to_real(record->stepCurrent);
    if (tau >= stepCurrent)
        return; // rendered time has caught up: the authoritative matrix is right

    Matrix3D output;
    Real stepPrevious = to_real(record->stepPrevious);
    if (tau >= stepPrevious)
    {
        Real span = stepCurrent - stepPrevious;
        blend_matrix(&record->previous, &record->current,
                     (tau - stepPrevious) / span, &output);
    }
    else
    {
        Real stepOlder = to_real(record->stepOlder);
        Real span = stepPrevious - stepOlder;
        if (span <= 0.0f || tau <= stepOlder)
            copy_matrix(&output, &record->older);
        else
            blend_matrix(&record->older, &record->previous,
                         (tau - stepOlder) / span, &output);
    }

    if (s_appliedCount >= POOL_SIZE)
        return;
    set_render_transform(renderObject, &output);
    record->applied = 1;
    s_applied[s_appliedCount++] = (Half)(record - s_pool);
}

// ---- animation clock ------------------------------------------------------
// Steers [0x012BB1CC] so that WW3D::SyncTime advances at real time however
// many client frames per second the loop runs, and however many of them the
// pacing cave marks as not advancing the client frame.

static void steer_animation_clock(int paceOn, Int64 now)
{
    if (!paceOn)
    {
        TheAnimationMsPerStep = RETAIL_ANIMATION_MS;
        s_haveDrawTicks = 0;
        s_haveSyncTime = 0;
        return;
    }

    Int64 frequency = PaceFrequency;
    Int64 elapsedTicks = 0;
    if (s_haveDrawTicks)
    {
        elapsedTicks = now - s_lastDrawTicks;
        if (elapsedTicks < 0)
            elapsedTicks = 0;
        if (elapsedTicks > frequency)
            elapsedTicks = frequency;
    }
    s_lastDrawTicks = now;
    s_haveDrawTicks = 1;

    Real elapsedMs = (Real)elapsedTicks * 1000.0f / (Real)frequency;

    Unsigned sync = WW3DSyncTime;
    if (!s_haveSyncTime || sync < s_lastSyncTime || sync - s_lastSyncTime > 1000u)
    {
        s_desiredMs = 0.0f;
        s_actualMs = 0.0f;
        s_haveSyncTime = 1;
    }
    else
    {
        s_actualMs += to_real((int)(sync - s_lastSyncTime));
        s_desiredMs += elapsedMs;
    }
    s_lastSyncTime = sync;

    Real deficit = s_desiredMs - s_actualMs;
    if (deficit > MAX_ANIMATION_CATCHUP_MS)
    {
        s_desiredMs = s_actualMs + MAX_ANIMATION_CATCHUP_MS;
        deficit = MAX_ANIMATION_CATCHUP_MS;
    }
    if (deficit < 1.0f)
        deficit = 1.0f;

    if (s_actualMs > 1000000.0f)
    {
        s_actualMs -= 1000000.0f;
        s_desiredMs -= 1000000.0f;
    }

    TheAnimationMsPerStep = round_real(deficit);
}

// ---- entry points ---------------------------------------------------------

extern "C" __declspec(dllexport) void __cdecl unitinterp_begin(void *display)
{
    (void)display;
    if (s_depth != 0)
    {
        ++s_depth;
        return;
    }
    s_depth = 1;

    ensure_initialized();
    ++s_stamp;
    if (s_stamp == 0)
        ++s_stamp;
    if ((s_stamp % (Unsigned)REBUILD_EVERY) == 0)
        rebuild_index();

    Int64 now = 0;
    int haveNow = 0;
    CounterFn counter = QueryPerformanceCounterSlot;
    if (counter != 0 && counter(&now) != 0)
        haveNow = 1;

    int paceOn = 0;
    if (haveNow && PaceActive != 0 && PaceFrequencyReady != 0 &&
        PaceInterval > 0 && PaceFrequency > 0)
        paceOn = 1;

    int interpolate = 0;
    Real tau = 0.0f;
    if (paceOn)
    {
        // One simulation phase is admitted per loop iteration at most, and
        // there is one draw per iteration, so an admit since the previous
        // draw shows as either the client-frame period moving on (any value
        // but the phase-1 retry marker 7) or the cave accumulator dropping.
        int admitted = 0;
        Byte *engine = (Byte *)TheGameEngine;
        if (engine != 0)
        {
            int period = *(int *)(engine + ENGINE_CLIENT_FRAME_PERIOD);
            if (s_havePeriod && period != s_previousPeriod && period != 7)
                admitted = 1;
            s_previousPeriod = period;
            s_havePeriod = 1;
        }
        Int64 accumulated = PaceAccumulated;
        if (s_haveAccumulated && accumulated < s_previousAccumulated)
            admitted = 1;
        s_previousAccumulated = accumulated;
        s_haveAccumulated = 1;
        if (admitted)
            ++s_step;

        Int64 interval = PaceInterval;
        Int64 since = now - PaceLastCounter;
        if (since < 0)
            since = 0;
        if (since > interval)
            since = interval;
        Real fraction = (Real)(accumulated + since) / (Real)interval;
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 2.0f)
            fraction = 2.0f;
        tau = to_real(s_step) + fraction - DISPLAY_DELAY_STEPS;
        interpolate = 1;
    }
    else
    {
        s_haveAccumulated = 0;
        s_havePeriod = 0;
    }

    steer_animation_clock(paceOn, now);

    void *client = TheGameClient;
    if (client == 0)
        return;

    void *drawable = *(void **)((Byte *)client + GAMECLIENT_DRAWABLE_LIST);
    int walked = 0;
    while (drawable != 0 && walked++ < MAX_DRAWABLES)
    {
        void **modules = *(void ***)((Byte *)drawable + DRAWABLE_MODULES);
        if (modules != 0)
        {
            int moduleCount = 0;
            while (moduleCount < MAX_DRAW_MODULES && modules[moduleCount] != 0)
            {
                void *module = modules[moduleCount++];
                void **moduleVtable = *(void ***)module;
                if (!in_image(moduleVtable))
                    continue;

                void *interfaceObject = ((GetObjectInterface)
                    moduleVtable[DRAWMODULE_GET_OBJECT_INTERFACE / 4])(module, 0);
                if (interfaceObject == 0)
                    continue; // ropes/debris/trees/lasers do not take this path

                void **interfaceVtable = *(void ***)interfaceObject;
                if (!in_image(interfaceVtable))
                    continue;

                void *renderObject = *(void **)((Byte *)interfaceObject +
                                                MODEL_INTERFACE_RENDER_OBJECT);
                visit(drawable, renderObject, interpolate, tau);
            }
        }
        drawable = *(void **)((Byte *)drawable + DRAWABLE_NEXT);
    }
}

extern "C" __declspec(dllexport) void __cdecl unitinterp_restore()
{
    if (s_depth == 0)
        return;
    if (s_depth > 1)
    {
        --s_depth;
        return;
    }

    for (int i = 0; i < s_appliedCount; ++i)
    {
        TransformRecord *record = &s_pool[s_applied[i]];
        if (record->applied && record->renderObject != 0)
            set_render_transform(record->renderObject, &record->current);
        record->applied = 0;
    }
    s_appliedCount = 0;
    s_depth = 0;
}
