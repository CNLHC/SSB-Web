import { combineReducers } from 'redux';
import { connectRouter } from 'connected-react-router'
import MqttReduxDaemonReducers from "../components/mqtt/reducers";

const CreateRootReducer =(history:any)=>combineReducers({
    router: connectRouter(history),
    mqtt: MqttReduxDaemonReducers
});

export interface IState {
}

export default CreateRootReducer;
