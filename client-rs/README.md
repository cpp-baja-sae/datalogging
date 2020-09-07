# Rust Client Prototype

## Developer notes
This project requires Rust, which can be installed from https://rustup.rs. 
It requires some additional tools which can be installed with
`cargo install wasm-pack`. This step may take a while as `cargo install` is
designed to compile everything from scratch, including dependencies. 
`./build.sh` will compile the project into the `target-web` folder. This will
take a while the first time due to dependencies, but subsequent builds will be 
much faster. `./run.sh` will start up a development server on port 8000 which 
currently does not do any hot-reloading and must be manually restarted after 
rebuilding the project.
