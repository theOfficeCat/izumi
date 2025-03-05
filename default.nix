{ lib
, stdenv
, meson
, ninja
, ncurses
}:

stdenv.mkDerivation {
  pname = "izumi";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
  ];

  buildInputs = [
    ncurses
  ];

  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
