use yew::prelude::*;

#[derive(Properties, Clone, PartialEq)]
pub struct GraphsPageProps { }

#[derive(Clone, PartialEq)]
pub enum GraphsPageMessage { }

#[derive(Clone)]
pub struct GraphsPage {
    props: GraphsPageProps,
    link: ComponentLink<Self>,
}

impl Component for GraphsPage {
    type Message = GraphsPageMessage;
    type Properties = GraphsPageProps;

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
        let style = format!("background: #F0F;");
        html! {
            <div style=style />
        }
    }
}
