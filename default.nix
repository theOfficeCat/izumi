{ lib
, stdenv
, cmake
, ncurses
, doxygen
, runCommandCC
}:

stdenv.mkDerivation rec {
  pname = "izumi";
  version = lib.strings.trim (builtins.readFile ./.version);

  outputs = [ "bin" "doc" "out" ];
  
  src = ./.;

  nativeBuildInputs = [
    cmake
    doxygen
  ];

  buildInputs = [
    ncurses
  ];

  preBuild = ''
    du /build
  '';

  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}

