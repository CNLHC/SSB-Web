import {IMqttReduxDaemonReducer} from "./components/mqtt/reducers";

export interface ICommodity {
        UHDTag :string
}

export  interface IRootStore {
    mqtt:IMqttReduxDaemonReducer



}