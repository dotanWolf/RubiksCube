#include <napi.h>
#include "App.h"
#include "Cube.h"
#include "AStarSolver.h"

static Cube* globalCube = nullptr;
static AStarSolver* globalSolver = nullptr;
static App* globalApp = nullptr;

void EnsureInitialized() {
    if (!globalApp) {
        globalCube = new Cube(3); 
        globalSolver = new AStarSolver();
        globalApp = new App(globalSolver, globalCube);
    }
}

// addon.cpp
Napi::String ScrambleWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EnsureInitialized(); 

    std::string scrambleMoves = globalApp->scramble();
    return Napi::String::New(env, scrambleMoves);
}

Napi::String SolveWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EnsureInitialized();

    std::string solutionMoves = globalApp->solve();
    return Napi::String::New(env, solutionMoves);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "scramble"), Napi::Function::New(env, ScrambleWrapped));
    exports.Set(Napi::String::New(env, "solve"), Napi::Function::New(env, SolveWrapped));
    return exports;
}

NODE_API_MODULE(rubiks_addon, Init)