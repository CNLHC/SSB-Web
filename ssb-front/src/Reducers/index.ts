

import { combineReducers } from 'redux';
import PageSettleReducers from "../containers/PageSettle/reducer";
import AndroidReducers from "../Android/reducers";
import {IRootStore} from "../Typings/TypeRoot";

const RootReducers=combineReducers({
    settle: PageSettleReducers,
    Android: AndroidReducers
} as any);

export default RootReducers ;