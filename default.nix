{ lib
, stdenv
, autoreconfHook
, pkgconf
, gnumake
, ncurses
, perl
, doxygen
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
  
  doCheck = true;

  passthru.tests = {
    distcheck = stdenv.mkDerivation {
      name = "izumi-distcheck";
      inherit src nativeBuildInputs buildInputs;
      
      doCheck = true;
      checkTarget = "distcheck";
    };
    
    distcheck-nodocs = stdenv.mkDerivation {
      name = "izumi-distcheck-nodocs";
      inherit src nativeBuildInputs buildInputs;
      
      configureFlags = [ "--disable-doxygen-doc" ];
      doCheck = true;
      checkTarget = "distcheck";
    };
  };
  
  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
