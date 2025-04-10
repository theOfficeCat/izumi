{ lib
, stdenv
, meson
, ninja
, ncurses
, hotdoc
}:

stdenv.mkDerivation {
  pname = "izumi";
  version = lib.strings.trim (builtins.readFile ./.version);

  outputs = [ "bin" "doc" "out" ];
  
  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
    hotdoc
  ];

  buildInputs = [
    ncurses
  ];

  mesonBuildType = "release";

  mesonFlags = [
    (lib.strings.mesonOption "b_sanitize" "none")
  ];
  
  mesonInstallTags = [ "runtime" ];
  
  postInstall = ''
    pushd src/libizumi/docs/libizumi-doc/html
    find -type f -exec install -Dm 755 "{}" "$out/share/doc/libizumi/html/{}" \;
    popd
  '';

  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
