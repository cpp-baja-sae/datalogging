use wasm_bindgen::prelude::*;
use yew::prelude::*;

mod pages;

#[wasm_bindgen(start)]
pub fn run_app() {
    // This way we get full Rust stack traces on panics.
    console_error_panic_hook::set_once();
    App::<pages::AppRoot>::new().mount_to_body();
}
