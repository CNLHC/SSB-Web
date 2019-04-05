import {ICommodity} from "./TypeCommodityList";

export interface ISessionInfo{
    id:number
    ShoppingCart:number
    State: "SHOPPING"|"PAYING"|"CLOSE"
    StartTime:string
    EndTime?:string
    Items:Array<ISessionItem>
}

export interface ISessionItem{
    id:number
    Session:number
    Numbers:number
    Item:number
    ItemDetail:ICommodity
}