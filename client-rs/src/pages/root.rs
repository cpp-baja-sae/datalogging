use yew::prelude::*;
use yew_router::{router::Router, Switch};

#[derive(Clone, Switch)]
enum AppRoute {
    #[to = "/graphs"]
    Graphs,
    #[to = "/channels"]
    Channels,
    #[to = "/pickDataSource"]
    PickDataSource,
    #[to = "/"]
    Index,
}

#[derive(Clone)]
pub struct AppRoot {
    props: (),
    link: ComponentLink<Self>,
}

impl Component for AppRoot {
    type Message = ();
    type Properties = ();

    fn create(props: Self::Properties, link: ComponentLink<Self>) -> Self {
        Self { props, link }
    }

    fn change(&mut self, props: Self::Properties) -> ShouldRender {
        if self.props == props {
            false
        } else {
            self.props = props;
            true
        }
    }

    fn update(&mut self, _msg: Self::Message) -> ShouldRender {
        false
    }

    fn view(&self) -> Html {
        let render = Router::render(|switch: AppRoute| match switch {
            AppRoute::Graphs => html! { <super::graphs::GraphsPage /> },
            AppRoute::Channels => unimplemented!(),
            AppRoute::PickDataSource => unimplemented!(),
            AppRoute::Index => html! { <super::graphs::GraphsPage /> },
        });
        html! {
            <Router<AppRoute, ()> render=render />
        }
    }
}
