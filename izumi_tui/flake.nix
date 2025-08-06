{
  description = "A multi-format instruction pipeline dump visualizer based on Konata";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    
    libizumi.url = "path:../libizumi";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];
      perSystem = { self', pkgs, inputs', ... }: {
        packages.izumi_tui = pkgs.callPackage ./default.nix {
          libizumi = inputs'.libizumi.packages.default;
        };
        packages.default = self'.packages.izumi_tui;
        
        checks = self'.packages.default.tests;
      };
    };
}
