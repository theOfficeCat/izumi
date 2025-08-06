{
  description = "A multi-format instruction pipeline dump parser";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];
      perSystem = { self', pkgs, ... }: {
        packages.libizumi = pkgs.callPackage ./default.nix { };
        packages.default = self'.packages.libizumi;
        
        checks = self'.packages.default.tests;
      };
    };
}
