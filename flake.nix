{
  description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let pkgs = nixpkgs.legacyPackages.${system}; in
        {
          packages.default = pkgs.callPackage ./default.nix { };
        }
      );
}
