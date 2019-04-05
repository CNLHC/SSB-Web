import * as React from 'react';
import { Switch, Route } from 'react-router';
import PageSettle from "../containers/PageSettle";
import {Page} from "csstype";

const PageSettleRoute=() => (
    <Switch>
        <Route exact path="/session/:CartId" render={()=><PageSettle/>} />
    </Switch>
);

export default PageSettleRoute;