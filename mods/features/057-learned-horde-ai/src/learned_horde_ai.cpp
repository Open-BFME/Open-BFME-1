// Learned horde tactics proof of concept.
//
// This payload is intentionally narrow:
//   * offline skirmish only;
//   * computer-controlled HORDE objects only;
//   * one tiny shared policy for every horde;
//   * BFME still owns pathfinding, formation movement, attacks and combat.
//
// Hook: HordeAIUpdate::update, retail RVA 0x002C4790.
// The incoming ECX is the AIUpdateInterface subobject. Retail's own first bytes
// prove the horde Object* is at [ECX-8] (mov edi,[ebx-8]).
//
// No CRT, no loader, no dynamic allocation. tools/modbuild.py checks that this
// translation unit leaves no unresolved external.

extern "C" const int _fltused = 0;

#include "policy_weights.inc"

typedef unsigned int UInt;

struct Coord3D {
    float x, y, z;
};

enum {
    GAME_SKIRMISH = 2,
    PLAYER_COMPUTER = 1,
    RELATIONSHIP_ENEMIES = 0,
    CELLSHROUD_CLEAR = 0,
    CMD_FROM_AI = 2,

    KINDOF_STRUCTURE = 7,
    KINDOF_HORDE = 0x6C,

    GL_FRAME = 0x3C,
    GL_FIRST_OBJECT = 0xA8,
    GL_MODE = 0x10C,

    PLAYER_INDEX = 0x24,
    PLAYER_TYPE = 0x2C,

    OBJECT_POSITION = 0x38,
    OBJECT_NEXT = 0x88,
    OBJECT_BODY = 0x200,
    OBJECT_OUTER = 0x214,

    AI_COMMAND_INTERFACE = 0x20,

    POLICY_PERIOD_FRAMES = 6,
    NO_MAX_SHOTS_LIMIT = 0x7fffffff
};

enum PolicyAction {
    ACTION_HOLD = 0,
    ACTION_ATTACK_NEAREST = 1,
    ACTION_ATTACK_WEAKEST = 2,
    ACTION_ATTACK_STRUCTURE = 3,
    ACTION_RETREAT = 4
};

#define TheGameLogic (*(void **)0x012F0898)
#define TheShroudManager (*(void **)0x012ED5BC)

// Existing retail entry points.
//
// MSVC 7.1 does not support spelling __thiscall in the payload sources used by
// this repository. __fastcall with an unused EDX gives the same register/stack
// shape for these calls: ECX=this, EDX=dummy, remaining args on the stack.
typedef int (__fastcall *IsKindOf)(void *, void *, int);
typedef void *(__fastcall *GetControllingPlayer)(void *, void *);
typedef int (__fastcall *GetRelationship)(void *, void *, const void *);
typedef int (__fastcall *GetShroudStatus)(void *, void *, int, const Coord3D *);
typedef void (__fastcall *AIAttackObject)(void *, void *, void *, int, int);
typedef void (__fastcall *AIMoveToPosition)(void *, void *, const Coord3D *, int);
typedef void (__fastcall *AIIdle)(void *, void *, int);
typedef float (__fastcall *BodyFloat)(void *, void *);

#define c_is_kind_of ((IsKindOf)0x004A2CF0)
#define c_get_controlling_player ((GetControllingPlayer)0x00420824)
#define c_get_relationship ((GetRelationship)0x0044A719)
#define c_get_shroud_status ((GetShroudStatus)0x00CF7430)
#define c_ai_attack_object ((AIAttackObject)0x005535A0)
#define c_ai_move_to_position ((AIMoveToPosition)0x004D86C0)
#define c_ai_idle ((AIIdle)0x004D87E0)

static void *ptr_at(void *base, int offset) {
    return *(void **)((unsigned char *)base + offset);
}

static const Coord3D *position_of(const void *object) {
    return (const Coord3D *)((const unsigned char *)object + OBJECT_POSITION);
}

static void *next_object(void *object) {
    return ptr_at(object, OBJECT_NEXT);
}

static float clamp01(float v) {
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

static float clamp_power(float v) {
    if (v < 0.0f) return 0.0f;
    if (v > 1.5f) return 1.5f;
    return v;
}

static float distance_squared(const Coord3D *a, const Coord3D *b) {
    const float dx = a->x - b->x;
    const float dy = a->y - b->y;
    return dx * dx + dy * dy;
}

// The policy was trained with a [0,1] distance feature. Avoid sqrt/CRT in the
// game payload: squared distance is monotonic, so map d^2 onto the same range.
static float normalised_distance(float d2) {
    const float scale2 = 2250000.0f; // 1500 game units squared
    return clamp01(d2 / scale2);
}

static float health_ratio(void *object) {
    if (!object) return 0.0f;
    void *body = ptr_at(object, OBJECT_BODY);
    if (!body) return 1.0f;

    void **vtable = *(void ***)body;
    // BFME BodyModuleInterface: getHealth +0x10, getMaxHealth +0x18.
    const float health = ((BodyFloat)vtable[4])(body, 0);
    const float maximum = ((BodyFloat)vtable[6])(body, 0);
    if (maximum <= 0.001f) return 1.0f;
    return clamp01(health / maximum);
}

static int visible_to_player(void *object, int player_index) {
    void *shroud = TheShroudManager;
    if (!object || !shroud) return 0;
    return c_get_shroud_status(
        shroud, 0, player_index, position_of(object)) == CELLSHROUD_CLEAR;
}

struct HordeStats {
    float health;
    float power;
    int members;
};

enum {
    MAX_CACHED_HORDES = 256,
    MAX_CACHED_TARGETS = 512,
    TARGET_IS_HORDE = 1,
    TARGET_IS_STRUCTURE = 2
};

struct HordeCacheEntry {
    void *horde;
    float total_health;
    int members;
};

struct TargetCacheEntry {
    void *object;
    float health;
    unsigned char kind;
};

static UInt s_cache_frame = 0xffffffffu;
static void *s_cache_first_object;
static HordeCacheEntry s_horde_cache[MAX_CACHED_HORDES];
static TargetCacheEntry s_target_cache[MAX_CACHED_TARGETS];
static int s_horde_cache_count;
static int s_target_cache_count;

static HordeCacheEntry *find_horde_cache(void *horde) {
    for (int i = 0; i < s_horde_cache_count; ++i) {
        if (s_horde_cache[i].horde == horde)
            return &s_horde_cache[i];
    }
    return 0;
}

static HordeCacheEntry *find_or_add_horde_cache(void *horde) {
    HordeCacheEntry *entry = find_horde_cache(horde);
    if (entry)
        return entry;
    if (s_horde_cache_count >= MAX_CACHED_HORDES)
        return 0;

    entry = &s_horde_cache[s_horde_cache_count++];
    entry->horde = horde;
    entry->total_health = 0.0f;
    entry->members = 0;
    return entry;
}

// Build once per learned-policy tick, regardless of how many hordes are
// updated. This is the important scaling boundary: inference is per horde,
// full-world classification is not.
static void build_tactical_cache(void *first, UInt frame) {
    if (s_cache_frame == frame && s_cache_first_object == first)
        return;

    s_cache_frame = frame;
    s_cache_first_object = first;
    s_horde_cache_count = 0;
    s_target_cache_count = 0;

    for (void *object = first; object; object = next_object(object)) {
        const int is_horde =
            c_is_kind_of(object, 0, KINDOF_HORDE) != 0;
        const int is_structure =
            c_is_kind_of(object, 0, KINDOF_STRUCTURE) != 0;

        if ((is_horde || is_structure) &&
            s_target_cache_count < MAX_CACHED_TARGETS)
        {
            TargetCacheEntry *target =
                &s_target_cache[s_target_cache_count++];
            target->object = object;
            target->kind = (unsigned char)(
                (is_horde ? TARGET_IS_HORDE : 0) |
                (is_structure ? TARGET_IS_STRUCTURE : 0));
            target->health = is_structure ? health_ratio(object) : 0.0f;
        }

        void *outer = ptr_at(object, OBJECT_OUTER);
        if (!outer || outer == object)
            continue;
        if (!c_is_kind_of(outer, 0, KINDOF_HORDE))
            continue;

        const float hp = health_ratio(object);
        if (hp <= 0.001f)
            continue;

        HordeCacheEntry *entry = find_or_add_horde_cache(outer);
        if (!entry)
            continue;
        entry->total_health += hp;
        ++entry->members;
    }
}

static HordeStats horde_stats(void *horde) {
    HordeStats out;
    HordeCacheEntry *entry = find_horde_cache(horde);

    if (entry && entry->members > 0) {
        out.health = entry->total_health / (float)entry->members;
        out.power = clamp_power((float)entry->members * 0.10f);
        out.members = entry->members;
        return out;
    }

    // Fallback for unusual horde implementations where member->outer is not
    // available through the standard Object field.
    out.health = health_ratio(horde);
    out.power = 0.10f;
    out.members = out.health > 0.001f ? 1 : 0;
    return out;
}

struct TacticalTargets {
    void *nearest;
    float nearest_hp;
    float nearest_distance;
    float nearest_threat;

    void *weakest;
    float weakest_hp;
    float weakest_distance;
    float weakest_threat;

    void *structure;
    float structure_hp;
    float structure_distance;
    float structure_threat;

    int visible_hordes;
    int visible_structures;
};

static TacticalTargets find_targets(
    void *own_horde, int player_index)
{
    TacticalTargets out;
    out.nearest = 0;
    out.nearest_hp = 0.0f;
    out.nearest_distance = 1.0f;
    out.nearest_threat = 0.0f;
    out.weakest = 0;
    out.weakest_hp = 0.0f;
    out.weakest_distance = 1.0f;
    out.weakest_threat = 0.0f;
    out.structure = 0;
    out.structure_hp = 0.0f;
    out.structure_distance = 1.0f;
    out.structure_threat = 0.0f;
    out.visible_hordes = 0;
    out.visible_structures = 0;

    const Coord3D *origin = position_of(own_horde);
    float nearest_d2 = 0.0f;
    float weakest_d2 = 0.0f;
    float structure_d2 = 0.0f;

    for (int i = 0; i < s_target_cache_count; ++i) {
        TargetCacheEntry *cached = &s_target_cache[i];
        void *object = cached->object;

        if (object == own_horde)
            continue;
        if (c_get_relationship(own_horde, 0, object) != RELATIONSHIP_ENEMIES)
            continue;
        if (!visible_to_player(object, player_index))
            continue;

        const float d2 = distance_squared(origin, position_of(object));

        if (cached->kind & TARGET_IS_HORDE) {
            HordeStats enemy = horde_stats(object);
            if (enemy.members > 0 && enemy.health > 0.001f) {
                ++out.visible_hordes;

                if (!out.nearest || d2 < nearest_d2) {
                    out.nearest = object;
                    nearest_d2 = d2;
                    out.nearest_hp = enemy.health;
                    out.nearest_distance = normalised_distance(d2);
                    out.nearest_threat = enemy.power;
                }

                if (!out.weakest ||
                    enemy.health < out.weakest_hp ||
                    (enemy.health == out.weakest_hp && d2 < weakest_d2))
                {
                    out.weakest = object;
                    weakest_d2 = d2;
                    out.weakest_hp = enemy.health;
                    out.weakest_distance = normalised_distance(d2);
                    out.weakest_threat = enemy.power;
                }
            }
        }

        if (cached->kind & TARGET_IS_STRUCTURE) {
            const float hp = cached->health;
            if (hp <= 0.001f)
                continue;

            ++out.visible_structures;
            if (!out.structure || d2 < structure_d2) {
                out.structure = object;
                structure_d2 = d2;
                out.structure_hp = hp;
                out.structure_distance = normalised_distance(d2);

                // Coarse bootstrap proxy. BFME telemetry should replace this
                // with actual weapons/defence observations.
                out.structure_threat = 0.35f + hp * 0.45f;
            }
        }
    }

    return out;
}

static float count_feature(int count, float divisor) {
    return clamp01((float)count / divisor);
}

static int policy_action(const float *obs, const TacticalTargets *targets) {
    float hidden[POLICY_HIDDEN];
    float logits[POLICY_ACTIONS];

    for (int j = 0; j < POLICY_HIDDEN; ++j) {
        float value = POLICY_B1[j];
        const int row = j * POLICY_OBS;
        for (int i = 0; i < POLICY_OBS; ++i)
            value += POLICY_W1[row + i] * obs[i];
        hidden[j] = value > 0.0f ? value : 0.0f;
    }

    for (int action = 0; action < POLICY_ACTIONS; ++action) {
        float value = POLICY_B2[action];
        const int row = action * POLICY_HIDDEN;
        for (int j = 0; j < POLICY_HIDDEN; ++j)
            value += POLICY_W2[row + j] * hidden[j];
        logits[action] = value;
    }

    // Action masking is a game rule, not learned behaviour: the network may
    // never select a target that does not exist in its observation.
    if (!targets->nearest) {
        logits[ACTION_ATTACK_NEAREST] = -1000000.0f;
        logits[ACTION_RETREAT] = -1000000.0f;
    }
    if (!targets->weakest)
        logits[ACTION_ATTACK_WEAKEST] = -1000000.0f;
    if (!targets->structure)
        logits[ACTION_ATTACK_STRUCTURE] = -1000000.0f;

    int best = ACTION_HOLD;
    float best_value = logits[ACTION_HOLD];
    for (int action = 1; action < POLICY_ACTIONS; ++action) {
        if (logits[action] > best_value) {
            best = action;
            best_value = logits[action];
        }
    }
    return best;
}

static void issue_action(
    void *ai_update, void *horde, int action, const TacticalTargets *targets)
{
    void *commands =
        (unsigned char *)ai_update + AI_COMMAND_INTERFACE;

    switch (action) {
    case ACTION_ATTACK_NEAREST:
        if (targets->nearest)
            c_ai_attack_object(
                commands, 0, targets->nearest,
                NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
        break;

    case ACTION_ATTACK_WEAKEST:
        if (targets->weakest)
            c_ai_attack_object(
                commands, 0, targets->weakest,
                NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
        break;

    case ACTION_ATTACK_STRUCTURE:
        if (targets->structure)
            c_ai_attack_object(
                commands, 0, targets->structure,
                NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
        break;

    case ACTION_RETREAT:
        if (targets->nearest) {
            const Coord3D *me = position_of(horde);
            const Coord3D *enemy = position_of(targets->nearest);
            Coord3D destination;

            float dx = me->x - enemy->x;
            float dy = me->y - enemy->y;
            if (dx > -1.0f && dx < 1.0f &&
                dy > -1.0f && dy < 1.0f)
            {
                dx = 200.0f;
            }

            // Mirror away from the threat. BFME's own movement/pathfinding
            // layer decides the legal route and final reachable point.
            destination.x = me->x + dx;
            destination.y = me->y + dy;
            destination.z = me->z;
            c_ai_move_to_position(
                commands, 0, &destination, CMD_FROM_AI);
        }
        break;

    case ACTION_HOLD:
    default:
        c_ai_idle(commands, 0, CMD_FROM_AI);
        break;
    }
}

extern "C" __declspec(dllexport) void __cdecl learned_horde_ai_tick(
    void *ai_update)
{
    void *logic = TheGameLogic;
    if (!logic || !ai_update) return;

    unsigned char *gl = (unsigned char *)logic;
    if (*(int *)(gl + GL_MODE) != GAME_SKIRMISH)
        return;

    const UInt frame = *(UInt *)(gl + GL_FRAME);
    if ((frame % POLICY_PERIOD_FRAMES) != 0)
        return;

    // HordeAIUpdate::update is reached through the AIUpdateInterface subobject
    // at complete-object +0x10. Retail begins with mov edi,[this-8].
    void *horde =
        *(void **)((unsigned char *)ai_update - 8);
    if (!horde) return;
    if (!c_is_kind_of(horde, 0, KINDOF_HORDE))
        return;

    void *player = c_get_controlling_player(horde, 0);
    if (!player) return;
    if (*(int *)((unsigned char *)player + PLAYER_TYPE) != PLAYER_COMPUTER)
        return;

    const int player_index =
        *(int *)((unsigned char *)player + PLAYER_INDEX);

    void *first = ptr_at(logic, GL_FIRST_OBJECT);
    if (!first) return;

    build_tactical_cache(first, frame);

    HordeStats own = horde_stats(horde);
    if (own.members <= 0) return;

    TacticalTargets targets =
        find_targets(horde, player_index);

    float obs[POLICY_OBS];
    obs[0] = own.health;
    obs[1] = own.power;

    obs[2] = targets.nearest_hp;
    obs[3] = targets.nearest_distance;
    obs[4] = targets.nearest_threat;

    obs[5] = targets.weakest_hp;
    obs[6] = targets.weakest_distance;
    obs[7] = targets.weakest_threat;

    obs[8] = targets.structure_hp;
    obs[9] = targets.structure_distance;
    obs[10] = targets.structure_threat;
    obs[11] = targets.structure ? 1.0f : 0.0f;

    obs[12] = count_feature(targets.visible_hordes, 6.0f);
    obs[13] = count_feature(targets.visible_structures, 5.0f);

    // Reserved for temporal memory in the next iteration.
    obs[14] = 0.0f;
    obs[15] = 1.0f;

    const int action = policy_action(obs, &targets);
    issue_action(ai_update, horde, action, &targets);
}
