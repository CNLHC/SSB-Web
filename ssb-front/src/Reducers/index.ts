

import { combineReducers } from 'redux';
import { connectRouter } from 'connected-react-router'
import PageSettleReducers from "../containers/PageSettle/reducer";

const RootReducers =combineReducers({
    settle: PageSettleReducers,
});

export default RootReducers ;