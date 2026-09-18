{
  "targets": [
    {
      "target_name": "rubiks_addon",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "Cpp/addon.cpp",
        "Cpp/App.cpp",
        "Cpp/Cube.cpp",
        "Cpp/CubieCube.cpp",
        "Cpp/Corner.cpp",
        "Cpp/Edge.cpp",
        "Cpp/Piece.cpp",
        "Cpp/Move.cpp",
        "Cpp/MoveFactory.cpp",
        "Cpp/SearchNode.cpp",
        "Cpp/AStarSolver.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "Headers",
        "Cpp"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      }
    }
  ]
}