import {ActionsEnum, ActionType} from './actions'
import produce from "immer"
import {ISessionInfo, ISessionItem} from "../../Typings/TypeSessionInfo";


export interface IPageSettleReducer {
    loadingSessionInfo:boolean
    loadingDeleteItem:boolean
    loadingDealSession: boolean
    sessionInfo?:ISessionInfo
    loadingCloseSession:boolean
    loadingCreateSession:boolean
}


const InitState: IPageSettleReducer = {
    loadingSessionInfo:false,
    loadingDeleteItem: false,
    loadingDealSession: false,
    loadingCloseSession:false,
    loadingCreateSession:false
};


const PageSettleReducers=(state: IPageSettleReducer = InitState, action: ActionType) =>produce<IPageSettleReducer>(state,draft => {
    switch (action.type) {
        case ActionsEnum.GetSessionInfo_Req:
            draft.loadingSessionInfo = true;
            return
        case ActionsEnum.GetSessionInfo_Fai:
            draft.sessionInfo=undefined
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
        case ActionsEnum.DealSession_Req:
            draft.loadingDealSession = true;
            return
        case ActionsEnum.DealSession_Suc:
            draft.loadingDealSession = false;
            return
        case ActionsEnum.DealSession_Fai:
            draft.loadingDealSession = false;
            return
        case ActionsEnum.CloseSession_Req:
            draft.loadingCloseSession = true;
            return
        case ActionsEnum.CloseSession_Suc:
            draft.loadingCloseSession = false;
            return
        case ActionsEnum.CloseSession_Fai:
            draft.loadingCloseSession = false;
            return
        case ActionsEnum.CreateSession_Req:
            draft.loadingCreateSession = true;
            return
        case ActionsEnum.CreateSession_Suc:
            draft.loadingCreateSession = false;
            return
        case ActionsEnum.CreateSession_Fai:
            draft.loadingCreateSession = false;
            return
    }
})

export default PageSettleReducers;
