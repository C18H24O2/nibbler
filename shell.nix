{
  pkgs ? import <nixpkgs> { }
}:

let
  stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.llvmPackages_22.stdenv;
in
(pkgs.mkShell.override { inherit stdenv; }) {
  nativeBuildInputs = with pkgs; [
    nasm
    valgrind
    gdb
  
    clang-tools
    ncurses
    bear

    sdl3.lib
    sdl3.dev
    glfw
    libXinerama.dev
    libXi.dev
    catch2_3
  ];
}
