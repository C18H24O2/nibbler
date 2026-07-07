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
    bear

  ];
  C_INCLUDE_PATH="${pkgs.SDL2.dev}/include/SDL2";
}
