{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {nixpkgs, ...}: let 
    system = "x86_64-linux";
    #       ↑ Swap it for your system if needed
    #       "aarch64-linux" / "x86_64-darwin" / "aarch64-darwin"
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {

      packages = [
        # --- Web Development --- #
        # standard toolkit
        pkgs.nodejs # nixpkgs provides a "nodejs" package that corresponds to the current LTS version of nodejs, but you can specify a version (i.e node_20) if necessary
        pkgs.yarn
        pkgs.nodePackages.pnpm # a faster alternative to npm and yarn, with a less adopted toolchain

        # optionally required by your code editor to lint and format your code
        pkgs.nodePackages.prettier # formatter
        pkgs.nodePackages.eslint # linter

        # example package to serve a static nextjs export
        pkgs.nodePackages.serve

        # --- C++ Development --- #
        # Debugging
        pkgs.gdb

        # Choose the build tools that you need
        pkgs.cmake
        pkgs.pkg-config
        pkgs.meson
        pkgs.ninja

        # Add some libraries
        pkgs.boost
        pkgs.cppzmq
        pkgs.fmt

        # --- Python Development --- #
        (pkgs.python3.withPackages (python-pkgs: [
          # --- API Development --- #
          python-pkgs.flask
          python-pkgs.flask-cors
          python-pkgs.nltk
          python-pkgs.pyzmq

          # --- AI Development --- #
          python-pkgs.numpy
          python-pkgs.pandas
          python-pkgs.scipy
          python-pkgs.matplotlib
          python-pkgs.requests
          python-pkgs.transformers
          python-pkgs.tensorflow
          python-pkgs.keras
        ]))
      ];

      # Workaround: make vscode's python extension read the .venv
      shellHook = ''
        venv="$(cd $(dirname $(which python)); cd ..; pwd)"
        ln -Tsf "$venv" .venv
      '';
    };
  };
}
