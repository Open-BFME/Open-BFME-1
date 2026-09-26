#!/usr/bin/env python3
"""A class introduced by a local typedef cannot be mangled from the source.

TeamFactory_M_insert.cpp explicitly instantiates `BfmeTeamPrototypeTree::_M_insert`,
where BfmeTeamPrototypeTree is a typedef for an _STL::_Rb_tree specialisation. The
ledger's name is the expanded ?_M_insert@?$_Rb_tree@..., so the needle the tool
builds -- ?_M_insert@BfmeTeamPrototypeTree@ -- can never appear in it. The file HAS
matched rows for that instantiation; the tool could not see them and reported the
definition as unclaimed, which blocked every commit touching the file. A merge lane
lost a completed piece of work to it and correctly refused to whitelist around it.
"""
import importlib.util
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

_spec = importlib.util.spec_from_file_location(
    "fdu_under_test", TOOLS / "find_declared_unmatched.py")
fdu = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(fdu)


def test_typedef_aliases_are_recognised():
    text = """
typedef _STL::pair<int, int> BfmeTeamPrototypeKey;
typedef _STL::_Rb_tree<BfmeTeamPrototypeKey,
\tBfmeTeamPrototypePair> BfmeTeamPrototypeTree;
"""
    aliases = set(fdu.TYPEDEF_RE.findall(text))
    assert "BfmeTeamPrototypeTree" in aliases
    assert "BfmeTeamPrototypeKey" in aliases


def test_a_plain_class_is_not_mistaken_for_a_typedef():
    """The fallback must not widen to ordinary classes, or it would excuse a
    genuinely unclaimed definition on any file that happens to use a typedef."""
    aliases = set(fdu.TYPEDEF_RE.findall("class TeamPrototype;\nstruct Foo { int x; };\n"))
    assert aliases == set()


def test_the_real_file_no_longer_reports_unclaimed():
    """The end-to-end condition: this file blocked commits fleet-wide."""
    import subprocess
    result = subprocess.run(
        [sys.executable, str(TOOLS / "find_declared_unmatched.py"), "--fail",
         "game/GameEngine/Source/Common/RTS/TeamFactory_M_insert.cpp"],
        cwd=str(TOOLS.parent), capture_output=True, text=True)
    assert result.returncode == 0, result.stdout + result.stderr
    assert "_M_insert" not in result.stdout
