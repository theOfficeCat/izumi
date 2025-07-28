{ lib
, stdenv
, autoreconfHook
, pkgconf
, gnumake
, ncurses
# FIXME: documentation tool
, runCommandCC
}:

stdenv.mkDerivation rec {
  pname = "izumi";
  version = lib.strings.trim (builtins.readFile ./.version);

  #outputs = [ "bin" "doc" "out" ];
  
  src = ./.;

  nativeBuildInputs = [
    autoreconfHook
    gnumake
    pkgconf
    # FIXME: documentation tool
  ];

  buildInputs = [
    ncurses
  ];

  passthru.tests = {
    libizumi_documented = runCommandCC "${pname}-libizumi-documented" {
        inherit src buildInputs;
        nativeBuildInputs = [
            # FIXME: additional packages?
        ] ++ nativeBuildInputs;
    } ''
        cd $src
        # TODO: Test if everything is documented
        touch $out
    '';
  };
  
  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
