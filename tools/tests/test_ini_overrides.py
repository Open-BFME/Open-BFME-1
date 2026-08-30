#!/usr/bin/env python3
"""A compiled `imm32` is not what the game runs on. Pin both columns.

378 GlobalData fields are INI-parseable, and `_patch222.big` overrides `ini.big`
field by field, so a constant read correctly out of the disassembly can still be
wrong about behaviour. Six of the nine network fields differ from their compiled
defaults, the largest by 120x.

This cost real published numbers twice: "voted out after 60 seconds" (shipped
value 100000 ms, so wrong by forty) and a disconnect-risk percentage divided by
the compiled 5000 ms rather than the shipped 15000 ms, overstating it threefold.
Neither was visible from the image and neither needed a running game to avoid.

Two independent halves, which fail independently:
  the COMPILED column, asserted against the retail binary -- this is what
    identifies the fields, and it must match Zero Hour's declaration order
  the SHIPPED column, asserted against the archives via tools/ini_value.py --
    this is what the game does, and it is the column to quote
"""
import struct
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
FINDINGS = ROOT / "reverse/network_delay/FINDINGS.md"

# offset -> (field, compiled imm32, shipped value)
FIELDS = {
    0xCA4: ("NetworkFPSHistoryLength", 30, 38),
    0xCA8: ("NetworkLatencyHistoryLength", 200, 200),
    0xCAC: ("NetworkRunAheadMetricsTime", 500, 60000),
    0xCB0: ("NetworkCushionHistoryLength", 10, 120),
    0xCB4: ("NetworkRunAheadSlack", 10, 10),
    0xCB8: ("NetworkKeepAliveDelay", 20, 360),
    0xCBC: ("NetworkDisconnectTime", 5000, 15000),
    0xCC0: ("NetworkPlayerTimeoutTime", 60000, 100000),
    0xCC4: ("NetworkDisconnectScreenNotifyTime", 15000, 30000),
}

# The defaults block. Stores are a mix of `mov [esi+disp], imm32` and
# `mov [esi+disp], eax` after a `mov eax, imm32`, so the compiled column is
# asserted by reading the block rather than by pattern-matching one encoding.
DEFAULTS_BLOCK = 0x00085234          # file offset, covers +0xCA4 .. +0xCC4


@pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")
def test_compiled_defaults_are_where_the_identification_says():
    """The left column, straight out of the image.

    If this fails the field identification is wrong, which is a much bigger
    problem than a stale value: every offset in the network work is pinned to
    this block matching Zero Hour's declaration order.
    """
    image = EXE.read_bytes()
    seen = {}
    at = DEFAULTS_BLOCK
    eax = None
    while at < DEFAULTS_BLOCK + 0x90:
        if image[at] == 0xB8:                                   # mov eax, imm32
            eax = struct.unpack_from("<I", image, at + 1)[0]
            at += 5
        elif image[at:at + 2] == bytes([0xC7, 0x86]):            # mov [esi+d32], imm32
            disp = struct.unpack_from("<I", image, at + 2)[0]
            seen[disp] = struct.unpack_from("<I", image, at + 6)[0]
            at += 10
        elif image[at:at + 2] == bytes([0x89, 0x86]):            # mov [esi+d32], eax
            disp = struct.unpack_from("<I", image, at + 2)[0]
            if eax is not None:
                seen[disp] = eax
            at += 6
        else:
            at += 1
    for offset, (name, compiled, _shipped) in FIELDS.items():
        assert offset in seen, f"{name} (+{offset:#x}) has no store in the defaults block"
        assert seen[offset] == compiled, (
            f"{name} (+{offset:#x}) compiles in {seen[offset]}, table says {compiled}")


def test_shipped_values_match_the_archives():
    """The right column, straight out of ini.big + _patch222.big.

    Skipped where no install is present, because the archives are the game's
    and not the repository's. That is the honest failure mode: this check is
    unavailable rather than passing vacuously.
    """
    import ini_value
    try:
        root = ini_value.game_dir()
    except SystemExit as why:
        pytest.skip(str(why).splitlines()[0])
    merged = ini_value.resolve(root)
    for _offset, (name, _compiled, shipped) in FIELDS.items():
        assert name in merged, f"{name} is not set by any shipped archive"
        value, archive = merged[name]
        assert int(value) == shipped, (
            f"{name} ships as {value} (from {archive}), table says {shipped}")


def test_findings_quotes_the_shipped_column():
    """The doc must carry the shipped values, not the compiled ones.

    The table is the thing anyone reads before quoting a timeout, so a drifted
    row there is how the next wrong number gets published.
    """
    text = FINDINGS.read_text(encoding="utf-8")
    # Scope to the override table. These field names appear in several tables --
    # a function inventory quotes them too -- and matching the first row that
    # mentions one tests the wrong table.
    header = "| Offset | Field | Compiled `imm32` |"
    assert header in text, "the compiled-vs-shipped table is gone from FINDINGS"
    body = text[text.index(header):]
    body = body[:body.index("\n\n")]
    for _offset, (name, compiled, shipped) in FIELDS.items():
        row = next((l for l in body.splitlines()
                    if l.startswith("|") and f"`{name}`" in l), None)
        assert row, f"{name} has no row in the FINDINGS override table"
        assert f"**{shipped}**" in row or f" {shipped} " in row, (
            f"{name} row does not carry its shipped value {shipped}: {row.strip()}")
        if compiled != shipped:
            # both columns must be present, so the reader can see the gap
            assert str(compiled) in row, (
                f"{name} row dropped the compiled value {compiled}, which is what "
                f"identifies the field: {row.strip()}")


def test_the_tool_runs_and_reports_its_source():
    """A value with no provenance is how this went wrong the first time."""
    import ini_value
    try:
        ini_value.game_dir()
    except SystemExit as why:
        pytest.skip(str(why).splitlines()[0])
    out = subprocess.run([sys.executable, str(ROOT / "tools/ini_value.py"),
                          "--all-network"], capture_output=True, text=True, check=True).stdout
    assert "NetworkRunAheadSlack" in out
    assert ".big" in out, "the tool must name which archive supplied each value"
