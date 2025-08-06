{ lib
, stdenv
, autoreconfHook
, pkgconf
, gnumake
, libizumi
, ncurses
}:

stdenv.mkDerivation rec {
  pname = "izumi_tui";
  version = lib.strings.trim (builtins.readFile ./.version);
  
  src = ./.;

  nativeBuildInputs = [
    autoreconfHook
    gnumake
    pkgconf
  ];

  buildInputs = [
    libizumi
    ncurses
  ];
  
  doCheck = true;

  passthru.tests = {
    distcheck = stdenv.mkDerivation {
      name = "libizumi-distcheck";
      inherit src nativeBuildInputs buildInputs;
      
      doCheck = true;
      checkTarget = "distcheck";
    };
  };
  
  meta = with lib; {
    description = "A multi-format instruction pipeline dump visualizer based on Konata";
    homepage = "https://github.com/Izumi-visualizer/izumi_tui/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
