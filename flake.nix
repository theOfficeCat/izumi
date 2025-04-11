{
  description = "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];
      perSystem = { self', pkgs, ... }: {
        packages.izumi = pkgs.callPackage ./default.nix { };
        packages.default = self'.packages.izumi;
        
        checks = self'.packages.default.tests;
      };
    };
}
