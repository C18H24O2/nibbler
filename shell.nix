{
  pkgs ? import <nixpkgs> { }
}:

let
  stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.llvmPackages_22.stdenv;
in
(pkgs.mkShell.override { inherit stdenv; }) {
  nativeBuildInputs = with pkgs; [
    ripgrep
    fd

    nasm
    valgrind
    gdb
  
    clang-tools
    ncurses
    bear

    # graphics
    glfw
    libXinerama.dev
    libXi.dev
    sdl3.lib
    sdl3.dev
    # libui depends on sdl2-compat
    SDL2
    SDL2.dev
    SDL2_ttf
    SDL2_image
  ];

  C_INCLUDE_PATH="${pkgs.SDL2.dev}/include/SDL2";
}
