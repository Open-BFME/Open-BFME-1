# Link queue #4: `?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z` (s526, a1)

Census bb53b24f2b: wrong_selected, 1,123 B in 4 files (TunnelContain,
WorkerAIUpdate_internalCancelTask, SlavedUpdate_doRepairLogic,
WoundArrowUpdateUpdate).

## Wrong emitter (measured)

Masked compare of every `build/match` object defining the symbol against
retail 0x000D86C0 (219 B): MovementOrders, AIGroupScatter,
SiegeDeploySpecialPowerInitiate, SlavedUpdate_doAttackLogic and
SlavedUpdate_doScoutLogic emit the retail bytes. Only `ScriptActions.obj`
emits a wrong copy (142 B; 159 B with `/D_STLP_USE_STATIC_LIB`). Its source
is the inline body in `inputs/reference/shims/aicommandoutofline/GameLogic/AI.h`,
kept visible for `ScriptActions::doNamedMoveToWaypoint` (0x00300610).
ScriptActions' `AICommandParms` is 8 bytes smaller than retail's
(frame `sub esp,0x94` vs retail 0x9c), so no flag makes its copy retail-equal.

## Tried: declare it out of line in the shim (removes the emitter)

doNamedMoveToWaypoint then mismatches. Best shape (2 bytes off, 125/127):
`build/a1`-style source below, the waypoint copy read through
`const volatile UnsignedInt *src` into x, y, the AI pointer read as
`*(AIUpdateInterface * const volatile *)&obj->m_ai` between y and z, then the
three stores. Remaining: retail `lea ecx,[esp+0xc]; push ecx` for the
position argument, ours `lea eax,[esp+0xc]; push eax` (+0x6A/+0x6E).

Inert on that 2-byte residue: declaration placement, no `location` local,
`CommandSourceType` local, nested `if (aiUpdate)`, `way == NULL` form, store
through a `UnsignedInt *d`, `reinterpret_cast<&destination>`, `Coord3D`
destination with int stores, separate `const Coord3D *dest` local,
`AICommandInterface *commands` local (worse), file-static forceinline
forwarding helper (worse). Non-volatile x or z reorders loads (worse).

Next: test the shim change with a probe of rotation upstream (the two
by-value AsciiString calls), or give ScriptActions a retail-sized
AICommandParms view so its inline copy becomes retail-equal.

Best body (replace lines from `const Coord3D *location` to before `if (!aiUpdate)`):

    const Coord3D *location = way->getLocation();
    const volatile UnsignedInt *src = (const volatile UnsignedInt *)location;
    UnsignedInt x = src[0];
    UnsignedInt y = src[1];
    AIUpdateInterface *aiUpdate =
        *(AIUpdateInterface * const volatile *)&((BfmeObjectModules *)theObj)->m_ai;
    UnsignedInt z = src[2];
    UnsignedInt destination[3];
    destination[0] = x;
    destination[1] = y;
    destination[2] = z;

Shim edit: replace the inline `aiMoveToPosition` body in the class with
`void aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource );`.
