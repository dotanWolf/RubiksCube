import { useMemo } from "react";

export default function Cubie({ args = [1, 1, 1] }) {
  const colors = ["red", "orange", "white", "yellow", "green", "blue"];
  const stickers = useMemo(() => {
    const stickerArr = [];
    const epsilon = 0.02;
    const zeros = [0, 0, 0];
    const stickerDims = [0.85, 0.85, 0.85];

    for (let i = 0; i < 3; i++) {
      const faceOffset = args[i] / 2 + epsilon / 2;
      stickerArr.push({ offset: zeros.with(i, faceOffset), dims: stickerDims.with(i, epsilon), color: colors[2 * i] });
      stickerArr.push({ offset: zeros.with(i, -faceOffset), dims: stickerDims.with(i, epsilon), color: colors[2 * i + 1] });
    }
    return stickerArr;
  }, [args]);

  return (
    <>
      <mesh>
        <boxGeometry args={args} />
        <meshStandardMaterial color="#111111" roughness={0.4} />
      </mesh>
      {stickers.map((sticker, idx) => (
        <mesh key={idx} position={sticker.offset}>
          <boxGeometry args={sticker.dims} />
          <meshStandardMaterial color={sticker.color} roughness={0.2} />
        </mesh>
      ))}
    </>
  );
}