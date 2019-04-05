import  axios from 'axios'
import APIList from "../../API";

export enum ActionsEnum {
    GetSessionInfo_Req="[Settle]GetSessionInfo_Req",
    GetSessionInfo_Suc="[Settle]GetSessionInfo_Suc",
    GetSessionInfo_Fai="[Settle]GetSessionInfo_Fai",
}

export const ThunkGetSessionInfo = (queryInfo:any,onSuccess?:()=>any,onFail?:()=>any) => (dispatch: any) => {
    dispatch(ActGetSessionInfoReq())
    return axios.get(APIList.GetSessionInfo(queryInfo.id),{})
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

export type ActionType = ReturnType<typeof ActGetSessionInfoReq>&
    ReturnType <typeof ActGetSessionInfoSuc> &
    ReturnType <typeof ActGetSessionInfoFai> & any
