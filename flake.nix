{
  description = "A multi-format instruction pipeline dump visualizer based on Konata";

  inputs = {
    self.submodules = true;
    
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    
    libizumi.url = "path:./libizumi";
    izumi_tui.url = "path:./izumi_tui";
    izumi_tui.inputs.libizumi.follows = "libizumi";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];
      perSystem = { self', pkgs, inputs', ... }: {
        packages.libizumi = inputs'.libizumi.packages.default;
        packages.izumi_tui = inputs'.izumi_tui.packages.default;
        
        packages.default = self'.packages.izumi_tui;
        
        checks = {
          distcheck_fullbuild = pkgs.callPackage ./default.nix { };
        }
            // self'.packages.libizumi.tests
            // self'.packages.izumi_tui.tests;
      };
    };
}
