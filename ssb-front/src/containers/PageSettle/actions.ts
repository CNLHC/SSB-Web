import  axios from 'axios'
import APIList from "../../API";

export enum ActionsEnum {
    GetSessionInfo_Req="[Settle]GetSessionInfo_Req",
    GetSessionInfo_Suc="[Settle]GetSessionInfo_Suc",
    GetSessionInfo_Fai="[Settle]GetSessionInfo_Fai",
    DeleteItemByID_Req="[Settle]DeleteItemByID_Req",
    DeleteItemByID_Suc="[Settle]DeleteItemByID_Suc",
    DeleteItemByID_Fai="[Settle]DeleteItemByID_Fai",
    DealSession_Req = "[Settle]DealSession_Req",
    DealSession_Suc = "[Settle]DealSession_Suc",
    DealSession_Fai = "[Settle]DealSession_Fai",
    CloseSession_Req = "[Settle]CloseSession_Req",
    CloseSession_Suc = "[Settle]CloseSession_Suc",
    CloseSession_Fai = "[Settle]CloseSession_Fai",
    CreateSession_Req = "[Settle]CreateSession_Req",
    CreateSession_Suc = "[Settle]CreateSession_Suc",
    CreateSession_Fai = "[Settle]CreateSession_Fai",
    AddItemByBarCode_Req="[Settle]AddItemByBarCode_Req",
    AddItemByBarCode_Suc="[Settle]AddItemByBarCode_Suc",
    AddItemByBarCode_Fai="[Settle]AddItemByBarCode_Fai",

}

export const ThunkGetSessionInfo = (queryInfo:any,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActGetSessionInfoReq())
    return axios.get(APIList.GetSessionInfo(queryInfo.SessionID), {})
        .then((res: any) => {
            dispatch(ActGetSessionInfoSuc(res.data))
            if(onSuccess!==undefined)
                onSuccess();
        })
        .catch((err: any) => {
            dispatch(ActGetSessionInfoFai(err))
            if(onFail!==undefined)
                onFail();
        })
}


const ActGetSessionInfoReq=()=>({type:ActionsEnum.GetSessionInfo_Req})
const ActGetSessionInfoSuc=(data:any)=>({type:ActionsEnum.GetSessionInfo_Suc,data})
const ActGetSessionInfoFai=(err:any)=>({type:ActionsEnum.GetSessionInfo_Fai,err})

export interface IDeleteItemQuery {
        SessionID:number
        DeletePayload:{
            ItemID:number
        }
}
export const ThunkDeleteItemByID = (queryInfo:IDeleteItemQuery,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActDeleteItemByIDReq())
    return axios.post(APIList.DeleteItemByID(queryInfo.SessionID),queryInfo.DeletePayload)
        .then((res: any) => {
            dispatch(ActDeleteItemByIDSuc(res.data))
            if(onSuccess!==undefined)
                onSuccess();
            })
        .catch((err: any) => {
            dispatch(ActDeleteItemByIDFai(err))
            if(onFail!==undefined)
                onFail();
            })
}
const ActDeleteItemByIDReq=()=>({type:ActionsEnum.DeleteItemByID_Req})
const ActDeleteItemByIDSuc=(data:any)=>({type:ActionsEnum.DeleteItemByID_Suc,data})
const ActDeleteItemByIDFai=(err:any)=>({type:ActionsEnum.DeleteItemByID_Fai,err})

export const ThunkDealSession = (queryInfo: any, onSuccess?: () => any, onFail?: () => any) => (dispatch: any) => {
    console.log(queryInfo)
    dispatch(ActDealSessionReq())
    return axios.post(APIList.SessionDeal(queryInfo.SessionID), {})
        .then((res: any) => {
            dispatch(ActDealSessionSuc(res.data))
            if (onSuccess !== undefined)
                onSuccess();
        })
        .catch((err: any) => {
            dispatch(ActDealSessionFai(err))
            if (onFail !== undefined)
                onFail();
        })
}
const ActDealSessionReq = () => ({type: ActionsEnum.DealSession_Req})
const ActDealSessionSuc = (data: any) => ({type: ActionsEnum.DealSession_Suc, data})
const ActDealSessionFai = (err: any) => ({type: ActionsEnum.DealSession_Fai, err})


export const ThunkCloseSession = (queryInfo:any,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActCloseSessionReq())
    return axios.post(APIList.SessionClose(queryInfo.SessionID),{})
        .then((res: any) => {
            dispatch(ActCloseSessionSuc(res.data))
            if(onSuccess!==undefined)
                onSuccess();
            })
        .catch((err: any) => {
            dispatch(ActCloseSessionFai(err))
            if(onFail!==undefined)
                onFail();
            })
}

const ActCloseSessionReq=()=>({type:ActionsEnum.CloseSession_Req})
const ActCloseSessionSuc=(data:any)=>({type:ActionsEnum.CloseSession_Suc,data})
const ActCloseSessionFai=(err:any)=>({type:ActionsEnum.CloseSession_Fai,err})


export const ThunkCreateSession = (queryInfo:any,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActCreateSessionReq())
    return axios.post(APIList.SessionCreate,queryInfo,{})
        .then((res: any) => {
            dispatch(ActCreateSessionSuc(res.data))
            if(onSuccess!==undefined)
                onSuccess();
            })
        .catch((err: any) => {
            dispatch(ActCreateSessionFai(err))
            if(onFail!==undefined)
                onFail();
            })
}
const ActCreateSessionReq=()=>({type:ActionsEnum.CreateSession_Req})
const ActCreateSessionSuc=(data:any)=>({type:ActionsEnum.CreateSession_Suc,data})
const ActCreateSessionFai=(err:any)=>({type:ActionsEnum.CreateSession_Fai,err})



export const ThunkAddItemByBarCode = (queryInfo:any,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActAddItemByBarCodeReq())
    return axios.post(APIList.AddItemByBarCode(queryInfo.SessionID),queryInfo,{})
        .then((res: any) => {
            dispatch(ActAddItemByBarCodeSuc(res.data))
            if(onSuccess!==undefined)
                onSuccess();
            })
        .catch((err: any) => {
            dispatch(ActAddItemByBarCodeFai(err))
            if(onFail!==undefined)
                onFail();
            })
}
const ActAddItemByBarCodeReq=()=>({type:ActionsEnum.AddItemByBarCode_Req})
const ActAddItemByBarCodeSuc=(data:any)=>({type:ActionsEnum.AddItemByBarCode_Suc,data})
const ActAddItemByBarCodeFai=(err:any)=>({type:ActionsEnum.AddItemByBarCode_Fai,err})

export type ActionType = ReturnType<typeof ActGetSessionInfoReq>&
    ReturnType <typeof ActGetSessionInfoSuc> &
    ReturnType <typeof ActGetSessionInfoFai> & any
