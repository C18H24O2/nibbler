{
  pkgs ? import <nixpkgs> { }
}:

let
  stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.llvmPackages_21.stdenv;
in
(pkgs.mkShell.override { inherit stdenv; }) {
  nativeBuildInputs = with pkgs; [
    nasm
    valgrind
    gdb
  
    clang-tools
    bear
    xmake

    sdl3.lib
    sdl3.dev
    glfw
    xorg.libXinerama.dev
    xorg.libXi.dev
  ];
}
