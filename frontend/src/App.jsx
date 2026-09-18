import { useState, useRef } from "react";
import { Canvas } from "@react-three/fiber";
import { OrbitControls } from "@react-three/drei";
import RubiksCube from "./components/Cube/Cube";
import "./App.css";

const API_BASE = "http://localhost:3001";

export default function App() {
  const controlsRef = useRef();
  const [busy, setBusy] = useState(false);
  const cubeRef = useRef();

  const resetCamera = () => {
    if (controlsRef.current) {
      controlsRef.current.reset();
    }
  };

  const playMoves = (moves) => {
    return new Promise((resolve) => {
      let i = 0;

      const step = () => {
        if (i >= moves.length) {
          resolve();
          return;
        }
        const move = moves[i];
        cubeRef.current.triggerTurn(move);
        i += 1;

        const waitUntilDone = () => {
          if (cubeRef.current.isAnimating()) {
            requestAnimationFrame(waitUntilDone);
          } else {
            step();
          }
        };
        requestAnimationFrame(waitUntilDone);
      };

      step();
    });
  };

  const handleScramble = async () => {
    if (busy) return;
    setBusy(true);
    try {
      const res = await fetch(`${API_BASE}/api/scramble`);
      if (!res.ok) throw new Error(`Scramble failed: ${res.status}`);
      const data = await res.json();
      await playMoves(data.moves);
    } catch (err) {
      console.error(err);
    } finally {
      setBusy(false);
    }
  };

  const handleSolve = async () => {
    if (busy) return;
    setBusy(true);
    try {
      const res = await fetch(`${API_BASE}/api/solve`, { method: "POST" });
      if (!res.ok) throw new Error(`Solve failed: ${res.status}`);
      const data = await res.json();
      await playMoves(data.moves);
    } catch (err) {
      console.error(err);
    } finally {
      setBusy(false);
    }
  };

  return (
    <div className="app-container">
      <div className="controls-panel">
        <button type="button" className="btn btn-primary" onClick={handleScramble} disabled={busy}>
          Scramble
        </button>
        <button type="button" className="btn btn-primary" onClick={handleSolve} disabled={busy}>
          Solve
        </button>
        <button type="button" className="btn" onClick={resetCamera}>
          Reset Camera
        </button>
      </div>

      <div className="status-text">{busy ? "Animating..." : "Ready"}</div>

      <div className="canvas-wrapper">
        <Canvas camera={{ position: [8, 6, 8], fov: 45 }}>
          <OrbitControls ref={controlsRef} />
          <ambientLight intensity={0.8} />
          <directionalLight position={[10, 10, 5]} intensity={1.2} />
          <RubiksCube dims={[1, 1, 1]} ref={cubeRef} />
        </Canvas>
      </div>
    </div>
  );
}