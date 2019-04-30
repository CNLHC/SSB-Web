import {store} from "../App";

export enum ActionsEnum {
    SetBarCode="[ANDROID]SETBARCode"
}

export const ActSetBarCode= (BarCode:string) => ( {type:ActionsEnum.SetBarCode, BarCode });


export type ActionType =ReturnType<typeof  ActSetBarCode>

