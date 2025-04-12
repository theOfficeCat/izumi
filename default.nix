{ lib
, stdenv
, meson
, ninja
, ncurses
, hotdoc
, runCommandCC
, gtk-doc
}:

stdenv.mkDerivation rec {
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
    (lib.strings.mesonEnable "doc_tests" false)
  ];
  
  mesonInstallTags = [ "runtime" ];
  
  postInstall = ''
    pushd src/libizumi/docs/libizumi-doc/html
    find -type f -exec install -Dm 755 "{}" "$out/share/doc/libizumi/html/{}" \;
    popd
  '';

  passthru.tests = {
    libizumi_documented = runCommandCC "${pname}-libizumi-documented" {
        inherit src buildInputs;
        nativeBuildInputs = [
            gtk-doc
        ] ++ nativeBuildInputs;
    } ''
        cd $src
        meson setup $out
        meson test -C $out libizumi_undocumented --print-errorlogs
    '';
  };
  
  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
