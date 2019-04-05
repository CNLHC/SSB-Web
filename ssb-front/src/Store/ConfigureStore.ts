import { createStore, applyMiddleware, compose } from 'redux';
import thunk from 'redux-thunk';
import { createLogger } from 'redux-logger';
import RootReducers from "../Reducers";
import {IRootStore} from "../Typings/TypeRoot";


declare const window: Window & {
    __REDUX_DEVTOOLS_EXTENSION_COMPOSE__?(a: any): void;
};

declare const module: NodeModule & {
    hot?: {
        accept(...args: any[]): any;
    }
};


const logger = (<any>createLogger)({
    level: 'info',
    collapsed: true
});


const composeEnhancers: typeof compose = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ ?
    window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__({
    }) as any : compose;

const enhancer = composeEnhancers(
    applyMiddleware(thunk, logger)
);

const configureStore=() => {
    return createStore(RootReducers,enhancer);
}

export  default configureStore

