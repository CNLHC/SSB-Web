import React, {Component} from 'react';
import './App.css';
import {Provider} from "react-redux";
import PageSettleRoute from "./Routes/MainRoute";
import {BrowserRouter} from "react-router-dom";
import {applyMiddleware, createStore} from "redux";
import RootReducers from "./Reducers";
import thunk from "redux-thunk";
import logger from "redux-logger";
import {composeWithDevTools} from 'redux-devtools-extension';

import {ThunkAddItemByBarCode, ThunkGetSessionInfo} from "./containers/PageSettle/actions";
import {message} from "antd";

export interface IAndroidInterface {
    showToast: (s: string) => void
    invokeQRScan: () => void
    refresh: () => void
}

export declare var Android: IAndroidInterface;

export const store = createStore(RootReducers, composeWithDevTools(applyMiddleware(thunk, logger)));

window.SetBarCode = function (BarCode: string) {
    let urlSeg = location.href.split('/')
    let SessionID = parseInt(urlSeg[urlSeg.length - 1])
    store.dispatch(ThunkAddItemByBarCode({
            SessionID,
            barCode: BarCode
        }, () => store.dispatch(ThunkGetSessionInfo({SessionID},()=>window.scroll(0, 1000))as any)
        , () => message.error("无法获得商品信息")
    )as any)
}



class App extends Component {
    render() {
        return (
            <Provider store={store}>
                <BrowserRouter>
                    <PageSettleRoute/>
                </BrowserRouter>
            </Provider>
        );
    }
}

export default App;
