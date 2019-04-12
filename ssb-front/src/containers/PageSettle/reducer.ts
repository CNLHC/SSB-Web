import {ActionsEnum, ActionType} from './actions'
import produce from "immer"
import {ISessionInfo, ISessionItem} from "../../Typings/TypeSessionInfo";


export interface IPageSettleReducer {
    loadingSessionInfo:boolean
    loadingDeleteItem:boolean
    sessionInfo?:ISessionInfo
}


const InitState: IPageSettleReducer = {
    loadingSessionInfo:false,
    loadingDeleteItem:false
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
            draft.loadingSessionInfo =false;
            draft.sessionInfo = action.data;
            return
        case ActionsEnum.DeleteItemByID_Req:
            draft.loadingSessionInfo=true;
            return
        case ActionsEnum.DeleteItemByID_Suc:
            draft.loadingSessionInfo=false;
            return
        case ActionsEnum.DeleteItemByID_Fai:
            draft.loadingSessionInfo=false;
            return
    }
})

export default PageSettleReducers;
