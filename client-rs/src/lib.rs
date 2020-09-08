use wasm_bindgen::prelude::*;
use yew::prelude::*;

mod data;
mod pages;

#[wasm_bindgen(start)]
pub fn run_app() {
    wasm_logger::init(wasm_logger::Config::default());
    // This way we get full Rust stack traces on panics.
    console_error_panic_hook::set_once();
    App::<pages::AppRoot>::new().mount_to_body();
}
