# 057-learned-horde-ai — learned horde tactics proof of concept

This experiment exists to answer one narrow question:

> Can a small learned policy control BFME hordes directly from game state, without an LLM, screen reading, or hand-authored case logic?

It is deliberately **not** a replacement for the full skirmish AI yet. The stock AI still handles economy, production, teams, pathfinding, formations, weapon logic, and low-level movement. This feature only takes over a small tactical decision layer for computer-controlled hordes in **offline skirmish**.

## What the policy controls

Every six logic frames (about 5 Hz on the stock 30 Hz simulation), each computer-controlled horde gets one observation and one decision.

The five actions are:

1. `HOLD`
2. `ATTACK_NEAREST` visible enemy horde
3. `ATTACK_WEAKEST` visible enemy horde
4. `ATTACK_STRUCTURE` — nearest visible enemy structure
5. `RETREAT` — move away from the nearest visible enemy horde

The runtime does **not** implement pathfinding. It calls BFME's existing `AICommandInterface` methods and lets the game handle movement/combat normally.

## No cheating / fog of war

Enemy objects are candidates only when BFME's own shroud manager reports their position as `CELLSHROUD_CLEAR` for the AI player's index.

The policy never receives hidden unit positions. The relevant retail paths used by the experiment are already reconstructed in this repository:

- `HordeAIUpdate::update` — RVA `0x002C4790`
- `Thing::isKindOf` — body RVA `0x000A2CF0`
- `Object::getControllingPlayer` — ILT `0x00020824`
- `Object::getRelationship` — ILT `0x0004A719`
- `PartitionManager::getShroudStatusForPlayer` — RVA `0x008F7430`
- `AICommandInterface::aiMoveToPosition` — RVA `0x000D86C0`
- `AICommandInterface::aiIdle` — RVA `0x000D87E0`
- `AICommandInterface::aiAttackObject` — RVA `0x001535A0`

## Policy

The checked-in policy is intentionally tiny:

```
16 observations -> 8 ReLU units -> 5 actions
```

That is only **181 trainable parameters**. A 300k-parameter model is therefore not a requirement for the proof; it is merely a very generous future budget.

The observation vector contains:

- own horde average health and member-count-derived power
- nearest visible enemy horde health / distance / member-count-derived threat
- weakest visible enemy horde health / distance / threat
- nearest visible enemy structure health / distance / coarse threat
- visible enemy horde and structure counts
- presence flags / bias

Invalid actions are masked. For example, `ATTACK_STRUCTURE` cannot be selected when no visible enemy structure exists, and with no visible enemies the only valid tactical action is `HOLD`.

## Training

`train.py` trains from rewards over randomized tactical situations. It does not use replay labels or an expert action table. The reward function scores the consequences of attacking, finishing a weak target, taking structural value, exposing a wounded horde to danger, retreating, and idling with no visible threat.

The training distribution deliberately balances five situation families so every action is exercised. The generated weights are written directly into the CRT-free C++ runtime.

Run:

```sh
python3 mods/features/057-learned-horde-ai/train.py
```

It prints held-out action accuracy against the best reward outcome and rewrites:

```
mods/features/057-learned-horde-ai/src/policy_weights.inc
```

PyTorch is required for training only. **The game runtime has no PyTorch dependency.**

## Build

This is intentionally not registered in the normal mod bundle. Build it alone:

```sh
python3 mods/features/057-learned-horde-ai/build.py -o build/learned-horde-ai.exe
```

The builder uses the repository's existing cave / MSVC 7.1 mod infrastructure and patches the workshop vanilla 1.03 baseline.

## What this proves — and what it does not

A successful in-game test proves the architectural claim: a very small policy network can sit inside BFME's simulation, receive legal game-state observations, and issue horde-level actions cheaply.

It does **not** yet prove that this particular pretrained tactical policy beats the stock AI. The checked-in weights are bootstrap weights trained in the included tactical simulator. The next test is to record real BFME transitions/rewards and train/fine-tune on those.

The intended progression is:

```
simulator bootstrap
        |
        v
BFME offline skirmish telemetry
        |
        v
self-play / accelerated matches
        |
        v
target selection + retreat benchmark
        |
        v
larger tactical policy (heroes, powers, scouting, memory)
```

The important boundary remains the same: learned policy chooses **what to do**; BFME continues to implement **how the units physically do it**.

## Safety / multiplayer scope

This PoC is hard-gated to `GAME_SKIRMISH == 2`. Do not use it as a multiplayer client mod. A learned tactical controller in multiplayer would be gameplay automation and, if only one peer ran it, would also create fairness/compatibility problems.
