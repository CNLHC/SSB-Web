import produce from "immer"
import {ActionsEnum, ActionType} from "./actions";


export interface IAndroidReducer {
    BarCode?:string
    timestamp?:string
}


const InitState: IAndroidReducer = {

};


function AndroidReducers(state: IAndroidReducer = InitState, action: ActionType) {
    switch (action.type) {
        case ActionsEnum.SetBarCode:
            return produce<IAndroidReducer>(state,draft => {
                draft.BarCode=action.BarCode
                draft.timestamp = new Date().getTime().toString()
            })
        default:
            return state;
    }
}

export default AndroidReducers;
