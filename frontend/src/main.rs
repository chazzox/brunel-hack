use yew::prelude::*;
use yew::{function_component, html};

#[function_component(Heart)]
fn heart_asset() -> Html {
    html! { 
        <svg
            fill="#E53838"
            x="0px"
            y="0px"
            viewBox="0 0 512 512"
            xmlSpace="preserve"
            class="h-4 w-4 inline-block"
        >
            <path
                d="M256,483.5c-7.3,0-14.3-2.6-19.8-7.4C215.5,458,195.6,441,178,426l-0.1-0.1C126.3,382,81.8,344,50.8,306.6
                C16.1,264.8,0,225.2,0,181.9C0,139.8,14.4,101,40.6,72.6C67.1,43.8,103.5,28,143,28c29.6,0,56.6,9.3,80.4,27.8
                c12,9.3,22.9,20.7,32.5,34c9.6-13.3,20.5-24.7,32.5-34C312.4,37.3,339.4,28,369,28c39.5,0,75.9,15.8,102.4,44.6
                C497.6,101,512,139.8,512,181.9c0,43.3-16.1,82.9-50.8,124.7c-31,37.4-75.5,75.4-127.1,119.3c-17.6,15-37.6,32-58.3,50.2
                C270.3,480.9,263.3,483.5,256,483.5z M143,58C112,58,83.4,70.4,62.7,92.9c-21.1,22.9-32.7,54.4-32.7,89c0,36.4,13.5,69,43.9,105.6
                c29.3,35.4,73,72.6,123.5,115.6l0.1,0.1c17.7,15.1,37.7,32.1,58.5,50.3c21-18.3,41-35.3,58.7-50.4c50.5-43.1,94.1-80.2,123.5-115.6
                c30.3-36.6,43.9-69.2,43.9-105.6c0-34.5-11.6-66.1-32.7-89C428.6,70.4,400,58,369,58c-22.8,0-43.7,7.2-62.1,21.5 
                c-16.4,12.7-27.9,28.8-34.6,40c-3.5,5.8-9.5,9.2-16.3,9.2s-12.8-3.5-16.3-9.2c-6.7-11.3-18.2-27.3-34.6-40 
                C186.7,65.2,165.8,58,143,58z"
            />
        </svg> }
}

struct Model {
    value: String,
    inputValue: String,
}


impl Component for Model {
    type Message = ();
    type Properties = ();

    fn create(_ctx: &Context<Self>) -> Self {
        Self {
            value: String::from("test value"),
            inputValue: String::from(""),
        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        html! {
            <root class="min-h-screen flex items-center justify-center flex-col p-4 gap-4">

                <div class="bg-red-400 w-full rounded-2xl shadow-2xl flex-1 text-black">
                    <h1> { self.value.clone() } </h1> 
                </div>

                <input class="input bg-red-400 w-full text-center text-black" />

                <span class="text-normal">
                    {"Made with "}
                    <Heart/>
                    {" by shitposting LTD"}
                </span>
            </root>
        }
    }
}

fn main() {
    yew::start_app::<Model>();
}
