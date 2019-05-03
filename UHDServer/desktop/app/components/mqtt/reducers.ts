import {ActionsEnum,ActionType} from './actions'
import produce from "immer"
import {ICommodity} from "../../Typing";


export interface IMqttReduxDaemonReducer {
    CommodityList ?: ICommodity[]

}


const InitState: IMqttReduxDaemonReducer = {
};


const MqttReduxDaemonReducers = (state: IMqttReduxDaemonReducer = InitState, action: ActionType) => produce<IMqttReduxDaemonReducer>(state, draft => {
    switch (action.type) {
        case ActionsEnum.UpdateCommodityList:
            draft.CommodityList = [... action.data];
            break;
    }
})

export default MqttReduxDaemonReducers;
