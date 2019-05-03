import * as React from 'react';
import { Switch, Route } from 'react-router';
import QYProductList from "./pages/ProductList";
import PageCommodityCheck from "./pages/OrderManagement";

export default () => (
    <Switch>
      <Route exact path="/" component={PageCommodityCheck} />
      <Route exact path="/test" component={QYProductList} />
    </Switch>
);
