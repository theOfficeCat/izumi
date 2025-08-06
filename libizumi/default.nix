{ lib
, stdenv
, autoreconfHook
, pkgconf
, gnumake
, perl
, doxygen
}:

stdenv.mkDerivation rec {
  pname = "libizumi";
  version = lib.strings.trim (builtins.readFile ./.version);
  
  src = ./.;

  nativeBuildInputs = [
    autoreconfHook
    gnumake
    pkgconf
    perl
    doxygen
  ];
  
  doCheck = true;

  passthru.tests = {
    distcheck = stdenv.mkDerivation {
      name = "libizumi-distcheck";
      inherit src nativeBuildInputs;
      
      doCheck = true;
      checkTarget = "distcheck";
    };
    
    distcheck-nodocs = stdenv.mkDerivation {
      name = "libizumi-distcheck-nodocs";
      inherit src nativeBuildInputs;
      
      configureFlags = [ "--disable-doxygen-doc" ];
      doCheck = true;
      checkTarget = "distcheck";
    };
  };
  
  meta = with lib; {
    description = "A multi-format instruction pipeline dump parser";
    homepage = "https://github.com/Izumi-visualizer/libizumi";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
