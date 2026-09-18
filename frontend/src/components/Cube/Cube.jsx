// Cube.jsx
import { useRef, useState, forwardRef, useImperativeHandle } from 'react';
import { useFrame } from '@react-three/fiber';
import * as THREE from 'three';
import Cubie from '../Cubie/Cubie';

// Base angle = a single clockwise quarter-turn for that face, viewed from outside.
const FaceTable = {
  U: { axis: 1, direction: 1,  vec: [0, 1, 0], angle: -Math.PI / 2 },
  D: { axis: 1, direction: -1, vec: [0, 1, 0], angle: Math.PI / 2 },
  L: { axis: 0, direction: -1, vec: [1, 0, 0], angle: Math.PI / 2 },
  R: { axis: 0, direction: 1,  vec: [1, 0, 0], angle: -Math.PI / 2 },
  F: { axis: 2, direction: 1,  vec: [0, 0, 1], angle: -Math.PI / 2 },
  B: { axis: 2, direction: -1, vec: [0, 0, 1], angle: Math.PI / 2 },
};

// "U" -> { face: "U", modifier: "" }, "U'" -> modifier "'", "U2" -> modifier "2"
function parseMove(move) {
  const face = move[0];
  const modifier = move.slice(1);
  return { face, modifier };
}

const RubiksCube = forwardRef(function RubiksCube({ dims = [1, 1, 1] }, ref) {
  const [cubies, setCubies] = useState(() => {
    const coords = [-1, 0, 1];
    const initial = [];
    coords.forEach((x) => coords.forEach((y) => coords.forEach((z) => {
      initial.push({ id: `${x},${y},${z}`, pos: [x, y, z], quaternion: new THREE.Quaternion() });
    })));
    return initial;
  });

  const groupRefs = useRef(new Map());
  const turnRef = useRef(null); // { axis, direction, vec, angle, progress }

  useImperativeHandle(ref, () => ({
    triggerTurn(move) {
      if (turnRef.current) return;

      const { face, modifier } = parseMove(move);
      const base = FaceTable[face];
      if (!base) {
        return;
      }

      let angle = base.angle;
      if (modifier === "'") {
        angle = -base.angle;
      } else if (modifier === "2") {
        angle = base.angle * 2;
      } else if (modifier !== "") {
        return;
      }

      turnRef.current = {
        axis: base.axis,
        direction: base.direction,
        vec: base.vec,
        angle,
        progress: 0,
      };
    },
    isAnimating() {
      return turnRef.current !== null;
    },
  }));

  useFrame((_, delta) => {
    const turn = turnRef.current;
    if (!turn) return;

    turn.progress = THREE.MathUtils.damp(turn.progress, turn.angle, 12, delta);
    const done = Math.abs(turn.angle - turn.progress) < 0.005;
    const liveAngle = done ? turn.angle : turn.progress;

    const axisVec = new THREE.Vector3(...turn.vec);
    const stepQuat = new THREE.Quaternion().setFromAxisAngle(axisVec, liveAngle);

    cubies.forEach((cubie) => {
      if (cubie.pos[turn.axis] !== turn.direction) return;
      const obj = groupRefs.current.get(cubie.id);
      if (!obj) return;

      const livePos = new THREE.Vector3(...cubie.pos).applyQuaternion(stepQuat);
      obj.position.copy(livePos);
      obj.quaternion.copy(stepQuat.clone().multiply(cubie.quaternion));
    });

    if (done) {
      setCubies((prev) =>
        prev.map((cubie) => {
          if (cubie.pos[turn.axis] !== turn.direction) return cubie;
          const finalPos = new THREE.Vector3(...cubie.pos).applyQuaternion(stepQuat);
          return {
            ...cubie,
            pos: [Math.round(finalPos.x), Math.round(finalPos.y), Math.round(finalPos.z)],
            quaternion: stepQuat.clone().multiply(cubie.quaternion),
          };
        })
      );
      turnRef.current = null;
    }
  });

  return (
    <>
      {cubies.map((cubie) => (
        <group
          key={cubie.id}
          ref={(el) => {
            if (el) groupRefs.current.set(cubie.id, el);
            else groupRefs.current.delete(cubie.id);
          }}
          position={cubie.pos}
          quaternion={cubie.quaternion}
        >
          <Cubie args={dims} />
        </group>
      ))}
    </>
  );
});

export default RubiksCube;