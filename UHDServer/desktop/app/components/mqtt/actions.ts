import {ICommodity} from "../../Typing";

export enum ActionsEnum {
    UpdateCommodityList = "[mqttDaemon]UpdateList",
}

export const ActUpdateCommodityList = (payload:ICommodity[]) => ({
    type: ActionsEnum.UpdateCommodityList,
    data: payload
})

export type ActionType = ReturnType <typeof ActUpdateCommodityList>

