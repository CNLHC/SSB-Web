import {ActionsEnum, ActionType} from './actions'
import produce from "immer"
import {ISessionInfo, ISessionItem} from "../../Typings/TypeSessionInfo";


export interface IPageSettleReducer {
    loadingSessionInfo:boolean
    sessionInfo?:ISessionInfo
}


const InitState: IPageSettleReducer = {
    loadingSessionInfo:false
};


const PageSettleReducers=(state: IPageSettleReducer = InitState, action: ActionType) =>produce<IPageSettleReducer>(state,draft => {
    switch (action.type) {
        case ActionsEnum.GetSessionInfo_Req:
            draft.loadingSessionInfo = true;
            return
        case ActionsEnum.GetSessionInfo_Fai:
            draft.loadingSessionInfo = false;
            return
        case ActionsEnum.GetSessionInfo_Suc:
            draft.loadingSessionInfo =true;
            draft.sessionInfo = action.data;
            return
    }
})

export default PageSettleReducers;
