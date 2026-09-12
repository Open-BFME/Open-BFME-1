#!/usr/bin/env python3
"""Build the BFME1 Astra frame-pacing patch outside the retail image.

This is deliberately a small raw-x86 overlay.  ``tools/cave.py`` owns PE
section creation, whole-instruction stealing/relocation, and the two rel32
detours; this file only assembles the two payloads and writes their state.
"""
from __future__ import annotations

import argparse
import hashlib
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from cave import PE  # noqa: E402


IMAGE_BASE = 0x00400000

# Retail RVAs.  Runtime absolute addresses below are VA values because this
# fixed-base image encodes global references as absolute 32-bit operands.
UPDATE_RVA = 0x0006E910
NETWORK_LOGIC_RVA = 0x0006BAE0
LIMITER_GATE_RVA = 0x0006BEF0
SET_FPS_RVA = 0x0006B6F0
TIME_GET_TIME_RVA = 0x007E4810
IS_PAUSED_RVA = 0x00022C96

# The retail import table already owns these APIs.  Calling the IAT entries
# directly keeps the cave independent of a new thunk and preserves the
# process's existing fixed-base import layout.
QPC_IAT_VA = 0x01358EB4
QPF_IAT_VA = 0x01358EB8
TIME_BEGIN_PERIOD_IAT_VA = 0x0135953C

THE_NETWORK_VA = 0x012F7714
THE_GAME_LOGIC_VA = 0x012F0898
THE_GAME_CLIENT_VA = 0x012F1464
# Retail TheGameEngine global.  It is used to rewind a denied phase so the
# existing GameEngine update path retries that exact phase.
THE_GAME_ENGINE_VA = 0x012ED524
SECONDS_PER_LOGICFRAME_VA = 0x012A86A8

ENGINE_FPS_FIELD = 0x08
GAME_MODE_FIELD = 0x10C
GAME_PAUSED_FIELD = 0x11C
GAME_CLIENT_ADVANCE_FIELD = 0xC4
GAME_ENGINE_PERIOD_FIELD = 0x30
RETRY_PERIOD = 7

RENDER_CAP = 60
RETAIL_CAP = 30
# The retail client executes six simulation phases for each 200 ms logic
# frame.  The runtime interval is QueryPerformanceFrequency / 30, computed
# once and cached in the cave state.
SUBSTEP_HZ = 30
LOGIC_FRAME_PHASES = 6
CAVE_SIZE = 0x1000
# The QPC state is larger than the former millisecond state and the logic
# payload is correspondingly longer; keep it clear of the code/trampoline.
STATE_OFFSET = 0x400

# State is laid out as ordinary 32-bit halves so this stays usable by the
# retail x86 process without introducing x87 or compiler-runtime code.
STATE_ACTIVE_OFFSET = 0x00
STATE_LAST_LOW_OFFSET = 0x04
STATE_LAST_HIGH_OFFSET = 0x08
STATE_ACCUM_LOW_OFFSET = 0x0C
STATE_ACCUM_HIGH_OFFSET = 0x10
STATE_FREQ_LOW_OFFSET = 0x14
STATE_FREQ_HIGH_OFFSET = 0x18
STATE_INTERVAL_LOW_OFFSET = 0x1C
STATE_INTERVAL_HIGH_OFFSET = 0x20
STATE_FREQ_READY_OFFSET = 0x24
STATE_TIMER_READY_OFFSET = 0x28
STATE_TEMP_LOW_OFFSET = 0x2C
STATE_TEMP_HIGH_OFFSET = 0x30
STATE_SIZE = 0x34


def p8(value: int) -> bytes:
    return struct.pack("<B", value)


def p32(value: int) -> bytes:
    return struct.pack("<I", value & 0xFFFFFFFF)


def p32s(value: int) -> bytes:
    return struct.pack("<i", value)


class Asm:
    """Tiny label-aware encoder for the handful of x86 forms used here."""

    def __init__(self, start_rva: int):
        self.start_rva = start_rva
        self.code = bytearray()
        self.labels: dict[str, int] = {}
        self.fixups: list[tuple[int, int, int, str]] = []

    def emit(self, *parts: bytes) -> None:
        for part in parts:
            self.code.extend(part)

    def label(self, name: str) -> None:
        if name in self.labels:
            raise ValueError(f"duplicate label {name}")
        self.labels[name] = len(self.code)

    def rel8(self, opcode: int, label: str) -> None:
        self.code.append(opcode)
        self.fixups.append((len(self.code), 1, 2, label))
        self.code.append(0)

    def rel32(self, opcode: int, label: str) -> None:
        self.code.append(opcode)
        self.fixups.append((len(self.code), 4, 5, label))
        self.code.extend(b"\0\0\0\0")

    def jcc32(self, condition: int, label: str) -> None:
        self.code.extend((0x0F, condition))
        self.fixups.append((len(self.code), 4, 6, label))
        self.code.extend(b"\0\0\0\0")

    def resolve(self) -> bytes:
        out = bytearray(self.code)
        for pos, width, instruction_size, label in self.fixups:
            if label not in self.labels:
                raise ValueError(f"unknown label {label}")
            target = self.start_rva + self.labels[label]
            source_after = self.start_rva + pos + width
            displacement = target - source_after
            if width == 1:
                if not -128 <= displacement <= 127:
                    raise ValueError(
                        f"short branch to {label} is out of range: {displacement}")
                out[pos] = displacement & 0xFF
            else:
                out[pos:pos + width] = p32s(displacement)
        return bytes(out)


def abs_mov_eax(address: int) -> bytes:
    return b"\xA1" + p32(address)


def abs_mov_ecx(address: int) -> bytes:
    return b"\x8B\x0D" + p32(address)


def abs_mov_edx(address: int) -> bytes:
    return b"\x8B\x15" + p32(address)


def abs_store_eax(address: int) -> bytes:
    return b"\xA3" + p32(address)


def abs_store_edx(address: int) -> bytes:
    return b"\x89\x15" + p32(address)


def abs_add_edx(address: int) -> bytes:
    return b"\x03\x15" + p32(address)


def abs_store_imm(address: int, value: int) -> bytes:
    return b"\xC7\x05" + p32(address) + p32(value)


def abs_call_iat(address: int) -> bytes:
    """call dword ptr [absolute IAT address]"""
    return b"\xFF\x15" + p32(address)


def build_render_payload(start_rva: int) -> bytes:
    """Set GameEngine::m_maxFPS before replaying the stolen entry prologue.

    The high cap is limited to active network games or BFME single-player
    modes 0/2/7.  Replay and shell retain the installed retail cap.
    """
    a = Asm(start_rva)
    a.emit(abs_mov_eax(THE_NETWORK_VA), b"\x85\xC0")
    a.jcc32(0x85, "fast")  # jne
    a.emit(abs_mov_eax(THE_GAME_LOGIC_VA), b"\x85\xC0")
    a.jcc32(0x84, "retail")  # je: no logic object yet
    a.emit(b"\x8B\x90" + p32(GAME_MODE_FIELD))  # mov edx,[eax+0x10c]
    for mode in (0, 2, 7):
        a.emit(b"\x83\xFA" + p8(mode))
        a.jcc32(0x84, "fast")  # je
    a.label("retail")
    a.emit(b"\xC7\x41" + p8(ENGINE_FPS_FIELD) + p32(RETAIL_CAP))
    a.rel32(0xE9, "done")
    a.label("fast")
    a.emit(b"\xC7\x41" + p8(ENGINE_FPS_FIELD) + p32(RENDER_CAP))
    a.label("done")
    return a.resolve()


def build_logic_bytes(start_rva: int, state_vas: tuple[int, int, int]) -> bytes:
    """Build the SP per-sub-step gate using cached QPC frequency.

    Retail's network gate admits phase 1 at the logical-frame boundary, while
    phases 2..6 are ordinary engine iterations.  Astra keeps the same phase
    order but paces every phase at QueryPerformanceFrequency / 30 ticks.  A
    denied phase 2..6 rewinds the engine period so the same phase is retried; a
    denied phase 1 uses the existing period-greater-than-six retry path.
    """
    active_va, last_low_va, accum_low_va = state_vas
    last_high_va = last_low_va + (STATE_LAST_HIGH_OFFSET - STATE_LAST_LOW_OFFSET)
    accum_high_va = accum_low_va + (STATE_ACCUM_HIGH_OFFSET - STATE_ACCUM_LOW_OFFSET)
    freq_low_va = accum_low_va + (STATE_FREQ_LOW_OFFSET - STATE_ACCUM_LOW_OFFSET)
    freq_high_va = accum_low_va + (STATE_FREQ_HIGH_OFFSET - STATE_ACCUM_LOW_OFFSET)
    interval_low_va = accum_low_va + (STATE_INTERVAL_LOW_OFFSET - STATE_ACCUM_LOW_OFFSET)
    interval_high_va = accum_low_va + (STATE_INTERVAL_HIGH_OFFSET - STATE_ACCUM_LOW_OFFSET)
    freq_ready_va = accum_low_va + (STATE_FREQ_READY_OFFSET - STATE_ACCUM_LOW_OFFSET)
    timer_ready_va = accum_low_va + (STATE_TIMER_READY_OFFSET - STATE_ACCUM_LOW_OFFSET)
    temp_low_va = accum_low_va + (STATE_TEMP_LOW_OFFSET - STATE_ACCUM_LOW_OFFSET)
    temp_high_va = accum_low_va + (STATE_TEMP_HIGH_OFFSET - STATE_ACCUM_LOW_OFFSET)
    a = Asm(start_rva)

    # This hook is at a virtual-function entry.  Preserve the complete
    # integer/flags contract while the guard calls Win32 timing APIs and uses
    # ECX, EDX and EAX as scratch.  No x87 instruction is emitted or
    # introduced.
    a.emit(b"\x60\x9C\xFC")                         # pushad; pushfd; cld

    # timeBeginPeriod(1) is a belt-and-suspenders process-lifetime request for
    # any other loop code that still uses a waitable millisecond timer.  QPC is
    # the actual pacing clock below.  Set the flag after the call so the API is
    # invoked at most once even if the first call happens in MP or the shell.
    a.emit(b"\x83\x3D" + p32(timer_ready_va) + p8(0))
    a.jcc32(0x85, "timer_ready")
    a.emit(b"\x6A\x01", abs_call_iat(TIME_BEGIN_PERIOD_IAT_VA),
           abs_store_imm(timer_ready_va, 1))
    a.label("timer_ready")

    # At this point the hooked function's first argument is entry_esp+4, or
    # current esp+36+4 after pushad/pushfd.  Only the six retail phases are
    # paced; unexpected callers retain the original path.
    a.emit(b"\x83\x7C\x24" + p8(36 + 4) + p8(1))
    a.jcc32(0x82, "restore")  # jb: phase < 1
    a.emit(b"\x83\x7C\x24" + p8(36 + 4) + p8(6))
    a.jcc32(0x87, "restore")  # ja: phase > 6
    a.emit(abs_mov_eax(THE_NETWORK_VA), b"\x85\xC0")
    a.jcc32(0x85, "reset_restore")
    a.emit(abs_mov_edx(THE_GAME_LOGIC_VA), b"\x85\xD2")
    a.jcc32(0x84, "reset_restore")
    a.emit(b"\x8B\x82" + p32(GAME_MODE_FIELD))
    a.emit(b"\x83\xF8" + p8(5))
    a.jcc32(0x84, "reset_restore")
    for mode in (0, 2, 7):
        a.emit(b"\x83\xF8" + p8(mode))
        a.jcc32(0x84, "candidate")
    a.rel32(0xE9, "reset_restore")

    a.label("candidate")
    # isGamePaused is a phase-1-only stock gate.  Do not make phases 2..6
    # observe a new pause policy; GameEngine's freeze path owns that contract.
    a.emit(b"\x83\x7C\x24" + p8(36 + 4) + p8(1))
    a.jcc32(0x85, "clock")
    a.emit(b"\x80\xBA" + p32(GAME_PAUSED_FIELD) + p8(0))
    a.jcc32(0x85, "reset_restore")

    a.label("clock")

    # Cache QueryPerformanceFrequency / 30.  The two divisions implement a
    # 64-bit frequency divided by a 32-bit constant without a helper call:
    # first divide the high half, then divide (remainder:low) for the low
    # quotient.  A zero interval means the API returned an unusable value.
    a.emit(b"\x83\x3D" + p32(freq_ready_va) + p8(0))
    a.jcc32(0x85, "qpc_clock")
    a.emit(b"\x68" + p32(freq_low_va), abs_call_iat(QPF_IAT_VA),
           b"\x85\xC0")
    a.jcc32(0x84, "reset_restore")
    a.emit(b"\xB9" + p32(SUBSTEP_HZ))          # ecx = 30
    a.emit(b"\x8B\x05" + p32(freq_high_va), b"\x31\xD2", b"\xF7\xF1")
    a.emit(abs_store_eax(interval_high_va))     # eax = high quotient
    a.emit(b"\x8B\x05" + p32(freq_low_va), b"\xF7\xF1")
    a.emit(abs_store_eax(interval_low_va))      # eax = low quotient
    a.emit(b"\x83\x3D" + p32(interval_high_va) + p8(0))
    a.jcc32(0x85, "interval_valid")
    a.emit(b"\x83\x3D" + p32(interval_low_va) + p8(0))
    a.jcc32(0x84, "reset_restore")
    a.label("interval_valid")
    a.emit(abs_store_imm(freq_ready_va, 1))

    a.label("qpc_clock")

    # An inactive epoch admits its first phase immediately, but seeds the
    # last-counter value from QPC rather than from a millisecond clock.
    a.emit(b"\x83\x3D" + p32(active_va) + p8(0))
    a.jcc32(0x85, "have_active")
    a.emit(b"\x68" + p32(last_low_va), abs_call_iat(QPC_IAT_VA),
           b"\x85\xC0")
    a.jcc32(0x84, "reset_restore")
    a.emit(abs_store_imm(accum_low_va, 0),
           abs_store_imm(accum_high_va, 0),
           abs_store_imm(active_va, 1))
    a.rel32(0xE9, "restore")

    a.label("have_active")
    # Save the previous 64-bit timestamp, let QPC write the current value
    # directly into last_low/high, then subtract the saved value.
    a.emit(abs_mov_eax(last_low_va), abs_store_eax(temp_low_va),
           abs_mov_eax(last_high_va), abs_store_eax(temp_high_va))
    a.emit(b"\x68" + p32(last_low_va), abs_call_iat(QPC_IAT_VA),
           b"\x85\xC0")
    a.jcc32(0x84, "reset_restore")

    # QPC is a 64-bit monotonic counter on supported Windows systems.  Still
    # reject a backwards sample (including a theoretical 64-bit wrap) and
    # rebase through the retail path instead of manufacturing a huge delta.
    a.emit(b"\x8B\x05" + p32(last_high_va),
           b"\x3B\x05" + p32(temp_high_va))
    a.jcc32(0x82, "reset_restore")       # current high < previous high
    a.jcc32(0x85, "qpc_delta")           # current high > previous high
    a.emit(b"\x8B\x05" + p32(last_low_va),
           b"\x3B\x05" + p32(temp_low_va))
    a.jcc32(0x82, "reset_restore")       # equal high, current low < old low

    a.label("qpc_delta")
    a.emit(abs_mov_eax(last_low_va), abs_mov_ecx(temp_low_va), b"\x29\xC8",
            abs_mov_edx(last_high_va), abs_mov_ecx(temp_high_va), b"\x1B\xD1")

    # Clamp a stalled/invalidly large sample to one interval.  Since the
    # accumulator is always kept below one interval after an admission, this
    # guarantees at most one pending sub-step and prevents a pause or counter
    # anomaly from producing a catch-up burst.
    a.emit(b"\x3B\x15" + p32(interval_high_va))
    a.jcc32(0x87, "clamp_delta")
    a.jcc32(0x82, "add_delta")
    a.emit(b"\x3B\x05" + p32(interval_low_va))
    a.jcc32(0x87, "clamp_delta")
    a.rel32(0xE9, "add_delta")
    a.label("clamp_delta")
    a.emit(abs_mov_eax(interval_low_va), abs_mov_edx(interval_high_va))

    a.label("add_delta")
    a.emit(b"\x03\x05" + p32(accum_low_va),
           b"\x13\x15" + p32(accum_high_va))

    # Compare the 64-bit accumulated QPC ticks with the cached interval.
    a.emit(b"\x3B\x15" + p32(interval_high_va))
    a.jcc32(0x87, "admit")
    a.jcc32(0x82, "deny")
    a.emit(b"\x3B\x05" + p32(interval_low_va))
    a.jcc32(0x82, "deny")
    a.label("admit")
    a.emit(b"\x2B\x05" + p32(interval_low_va),
           b"\x1B\x15" + p32(interval_high_va),
           abs_store_eax(accum_low_va), abs_store_edx(accum_high_va))
    a.rel32(0xE9, "restore")

    # Not enough QPC ticks for the next phase yet.
    a.label("deny")
    a.emit(abs_store_eax(accum_low_va), abs_store_edx(accum_high_va))
    a.rel32(0xE9, "skip")

    # Any bypass resets the accumulator epoch.  On resume/new SP game the
    # first admitted phase is immediate, with no paused/menu time catch-up.
    # The same reset is used for a transient null during load/teardown.
    a.label("reset_restore")
    a.emit(abs_store_imm(active_va, 0),
           abs_store_imm(accum_low_va, 0),
           abs_store_imm(accum_high_va, 0))
    a.rel32(0xE9, "restore")

    a.label("skip")
    # These globals are live during a skirmish.  During load/teardown, fail
    # back to retail instead of dereferencing a transient null pointer.
    a.emit(abs_mov_edx(THE_GAME_ENGINE_VA), b"\x85\xD2")
    a.jcc32(0x84, "reset_restore")
    # Phase 1 is special: GameEngine only retries it through its existing
    # newPeriod>6 branch when m_advanceFrame is cleared.  Phases 2..6 are on
    # the ordinary path, so rewind to phase-1 and let the next update retry
    # that exact phase without disturbing the client-frame flag.
    a.emit(b"\x83\x7C\x24" + p8(36 + 4) + p8(1))
    a.jcc32(0x84, "skip_phase1")
    a.emit(b"\x8B\x44\x24" + p8(36 + 4))  # eax = requested phase
    a.emit(b"\x48")                           # --eax
    a.emit(b"\x89\x42" + p8(GAME_ENGINE_PERIOD_FIELD))
    a.rel32(0xE9, "restore")

    a.label("skip_phase1")
    a.emit(abs_mov_ecx(THE_GAME_CLIENT_VA), b"\x85\xC9")
    a.jcc32(0x84, "reset_restore")
    # This period value is also safe when the call came from the ordinary
    # initial phase-1 path; the next engine update enters the same retry arm.
    a.emit(b"\xC7\x42" + p8(GAME_ENGINE_PERIOD_FIELD) + p32(RETRY_PERIOD))
    a.emit(b"\xC6\x81" + p32(GAME_CLIENT_ADVANCE_FIELD) + p8(0))
    a.emit(b"\x9D\x61\xC2\x04\x00")       # popfd; popad; ret 4

    a.label("restore")
    a.emit(b"\x9D\x61")                         # popfd; popad
    a.label("fallthrough")
    return a.resolve()


def expect(pe: PE, rva: int, expected: bytes, label: str) -> None:
    actual = pe.read(rva, len(expected))
    if actual != expected:
        raise SystemExit(
            f"{label} at RVA 0x{rva:08X}: expected {expected.hex(' ')}, "
            f"found {actual.hex(' ')}")


def validate_retail(pe: PE) -> None:
    if pe.image_base != IMAGE_BASE:
        raise SystemExit(f"unexpected image base 0x{pe.image_base:08X}")
    # Hook points and their whole-instruction prefixes.
    expect(pe, NETWORK_LOGIC_RVA,
           bytes.fromhex("8b 0d 98 08 2f 01 56"), "network/logic entry")
    expect(pe, UPDATE_RVA,
           bytes.fromhex("51 53 56 8b f1"), "GameEngine::update entry")
    expect(pe, LIMITER_GATE_RVA, bytes.fromhex("74 bb"), "outer limiter gate")
    expect(pe, SET_FPS_RVA,
           bytes.fromhex("8b 44 24 04 89 41 08 c2 04 00"),
           "setFramesPerSecondLimit")
    expect(pe, TIME_GET_TIME_RVA,
           bytes.fromhex("ff 25 44 95 35 01"), "timeGetTime import thunk")
    expect(pe, IS_PAUSED_RVA,
           bytes.fromhex("e9 e5 07 36 00"), "isGamePaused import thunk")

    seconds_rva = SECONDS_PER_LOGICFRAME_VA - pe.image_base
    seconds = struct.unpack("<f", pe.read(seconds_rva, 4))[0]
    if abs(seconds - 0.2) > 0.00001:
        raise SystemExit(
            f"SECONDS_PER_LOGICFRAME at VA 0x{SECONDS_PER_LOGICFRAME_VA:08X} "
            f"is {seconds!r}, not 0.2")


def patch(original: Path, output: Path) -> dict[str, object]:
    if original.resolve() == output.resolve():
        raise SystemExit("refusing to use the retail path as output")
    if not original.exists():
        raise SystemExit(f"missing retail executable: {original}")

    pe = PE(original)
    validate_retail(pe)
    before_hash = hashlib.sha256(bytes(pe.data)).hexdigest()
    before_size = len(pe.data)

    cave_rva = pe.add_cave(CAVE_SIZE)
    state_base_rva = cave_rva + STATE_OFFSET
    state_vas = tuple(
        IMAGE_BASE + state_base_rva + n
        for n in (STATE_ACTIVE_OFFSET, STATE_LAST_LOW_OFFSET,
                  STATE_ACCUM_LOW_OFFSET))

    render_start = pe.next_rva()
    render_payload = build_render_payload(render_start)
    render_code_rva = pe.detour(UPDATE_RVA, payload=render_payload)

    logic_start = pe.next_rva()
    logic_payload = build_logic_bytes(logic_start, state_vas)
    logic_code_rva = pe.detour(NETWORK_LOGIC_RVA, payload=logic_payload)

    # The cave section is zero-filled by add_cave; write explicit state bytes
    # so the initial conditions are part of the resulting artifact's proof.
    pe.write(state_base_rva, b"\0" * STATE_SIZE)
    pe.save(output)

    if len(pe.data) <= before_size:
        raise SystemExit("patched image did not grow")
    return {
        "before_hash": before_hash,
        "before_size": before_size,
        "after_hash": hashlib.sha256(bytes(pe.data)).hexdigest(),
        "after_size": len(pe.data),
        "cave_rva": cave_rva,
        "cave_size": pe.cave_size,
        "cave_used": pe.cave_used,
        "state_base_rva": state_base_rva,
        "render_start_rva": render_code_rva,
        "render_payload": render_payload.hex(" "),
        "logic_start_rva": logic_code_rva,
        "logic_payload": logic_payload.hex(" "),
        "update_detour": pe.read(UPDATE_RVA, 5).hex(" "),
        "logic_detour": pe.read(NETWORK_LOGIC_RVA, 5).hex(" "),
        "limiter_gate": pe.read(LIMITER_GATE_RVA, 2).hex(" "),
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--original", type=Path,
                    default=Path(r"D:\BFME1\lotrbfme.exe"))
    ap.add_argument("--output", type=Path,
                    default=Path(r"D:\BFME1\lotrbfme-astra.exe"))
    args = ap.parse_args()
    info = patch(args.original, args.output)
    for key, value in info.items():
        print(f"{key}={value}")
    print(f"wrote {args.output} ({info['after_size']:,} bytes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
