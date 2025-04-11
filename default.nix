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
        undocumented=$(ninja -C $out libizumi_undocumented --quiet | tail -n +6)
        
        if [[ -n $undocumented ]]; then
            echo "UNDOCUMENTED ITEMS"
            echo "------------------"
            ninja -C $out libizumi_undocumented --quiet | tail -n +6 # Reprint
            false
        fi
    '';
  };
  
  meta = with lib; {
    description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";
    homepage = "https://github.com/theOfficeCat/Izumi/";
    license = licenses.gpl3Plus;
    platforms = platforms.all;
  };
}
