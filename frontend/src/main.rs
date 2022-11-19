use yew::prelude::*;
use yew::{html};

enum Msg {
    AddOne,
}

struct Model {
    value: i64,
}

impl Component for Model {
    type Message = Msg;
    type Properties = ();

    fn create(_ctx: &Context<Self>) -> Self {
        Self {
            value: 0,
        }
    }

    fn update(&mut self, _ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::AddOne => {
                self.value += 1;
                true
            }

        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        // This gives us a component's "`Scope`" which allows us to send messages, etc to the component.
        let link = ctx.link();
        html! {
            <root class="min-h-screen flex items-center justify-center">
                <div class="bg-red-100 w-96 rounded-2xl shadow-2xl p-10">
                    <button class="btn-sky-600 btn" onclick={link.callback(|_| Msg::AddOne)}>{ "+1" }</button>
                    <p>{ self.value }</p>
                </div>
            </root>
        }
    }
}

fn main() {
    yew::start_app::<Model>();
}
