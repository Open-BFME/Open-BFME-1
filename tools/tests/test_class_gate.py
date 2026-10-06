"""class_gate: a registered class gets no NEW private copy; existing copies and allowed views pass."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_gate  # noqa: E402

CANON = {"Coord3D": "game/Libraries/Include/Lib/Coord3D.h"}
VIEW = "struct Coord3D { float x, y, z; };\nvoid f(Coord3D *) {}\n"


def run(monkeypatch, before, now):
    monkeypatch.setattr(class_gate, "git_text", lambda spec: before if spec.startswith("HEAD:") else None)
    return class_gate.introduced("game/X.cpp", now, CANON)


def test_new_private_copy_is_refused(monkeypatch):
    assert run(monkeypatch, None, VIEW) == ["Coord3D"]                 # positive control: new unit
    assert run(monkeypatch, "void f() {}\n", VIEW) == ["Coord3D"]      # edit that adds the copy


def test_existing_copy_and_header_users_pass(monkeypatch):
    assert run(monkeypatch, VIEW, VIEW + "int g;\n") == []              # backlog, untouched
    assert run(monkeypatch, None, '#include "Coord3D.h"\nvoid f(Coord3D *) {}\n') == []
    assert run(monkeypatch, None, "// class-gate: allow Coord3D proved codegen view\n" + VIEW) == []
    assert run(monkeypatch, None, "struct Coord2D { float x, y; };\n") == []  # unregistered
