import {IPageSettleReducer} from "../containers/PageSettle/reducer";
import {IAndroidReducer} from "../Android/reducers";

export interface IRootStore {
    settle:IPageSettleReducer
    Android:IAndroidReducer
}