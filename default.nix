{ lib
, stdenv
, autoreconfHook
, pkgconf
, gnumake
, ncurses
, perl
, doxygen
, runCommandCC
}:

stdenv.mkDerivation rec {
  pname = "izumi";
  version = lib.strings.trim (builtins.readFile ./.version);
  
  src = ./.;

  nativeBuildInputs = [
    autoreconfHook
    gnumake
    pkgconf
    perl
    doxygen
  ];

  buildInputs = [
    ncurses
  ];

  passthru.tests = {
    # TODO: does the build step run 'make check'?
  };
  
  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
