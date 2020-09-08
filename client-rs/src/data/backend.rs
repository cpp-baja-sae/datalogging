use std::collections::HashSet;
use yew::agent::*;
use yew::prelude::*;
use yew::services::websocket::*;

fn url(endpoint: &str) -> String {
    format!("http://raspberrypi.local{}", endpoint)
}

fn ws_url(endpoint: &str) -> String {
    format!("ws://raspberrypi.local{}", endpoint)
}

pub struct RealtimeDataPacket {}

pub struct RealtimeDataAgent {
    link: AgentLink<Self>,
    connection: WebSocketTask,
    bridges: HashSet<HandlerId>,
}

impl Agent for RealtimeDataAgent {
    type Reach = Context<Self>;
    type Message = ();
    type Input = ();
    type Output = RealtimeDataPacket;

    fn create(link: AgentLink<Self>) -> Self {
        let endpoint_url = ws_url("");
        let callback = link.callback(|data: Result<Vec<u8>, _>| {});
        let status_callback = Callback::from(|status: WebSocketStatus| {
            if status == WebSocketStatus::Opened {
                log::info!("Web socket opened.");
            }
        });
        let connection =
            WebSocketService::connect_binary(&endpoint_url, callback, status_callback).unwrap();
        Self {
            link,
            connection,
            bridges: HashSet::new(),
        }
    }

    fn update(&mut self, msg: Self::Message) {}

    fn handle_input(&mut self, _msg: Self::Input, _id: HandlerId) {}

    fn connected(&mut self, id: HandlerId) {
        self.bridges.insert(id);
    }

    fn disconnected(&mut self, id: HandlerId) {
        self.bridges.remove(&id);
    }
}
