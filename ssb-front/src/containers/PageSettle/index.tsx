import * as React from 'react';
import {connect} from "react-redux"
import {ThunkGetSessionInfo} from "./actions";
import CommodityList from "../../components/CommodityList";

import SessionInfo from "../../components/SessionInfo";
import {RouteComponentProps, withRouter} from "react-router";
import {Collapse, PageHeader} from "antd";
import './index.scss'


const Panel = Collapse.Panel

type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>

interface IOwnProps extends RouteComponentProps<{ CartId: string }> {


}

type IPageProps = IStateProps & IDispatchProps & IOwnProps

export class UnconnectedPageSettle extends React.Component<IPageProps> {
    componentDidMount() {
        const payload = {id: this.props.match.params.CartId}
        this.props.onGetSessionInfo(payload);
    }

    render() {
        return (
            <div className={"ssb-settle-page"}>
                <PageHeader
                    title="易迈无人商店"
                    subTitle="结算页面"
                />
                <Collapse defaultActiveKey={['sessionInfoContent','sessionItems']} className={'settle-page-collapse'}>
                    <Panel key={'sessionInfoContent'} header={"订单信息"}>
                        <SessionInfo data={this.props.sessionInfo}/>
                    </Panel>
                    <Panel key={'sessionItems'} header={"商品详情"}>
                        <CommodityList
                            data={this.props.sessionInfo !== undefined ? this.props.sessionInfo.Items : undefined}/>
                    </Panel>
                </Collapse>
            </div>
        )
    }
}

const mapStateToProps = (state: any) => ({
    sessionInfo: state.settle.sessionInfo,
    loadingSessionInfo: state.settle.loadingSessionInfo
});

const mapDispatchToProps = (dispatch: any) => ({
    onGetSessionInfo: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkGetSessionInfo(payload, onSuc, onFai))
});

const PageSettle = withRouter(connect(mapStateToProps, mapDispatchToProps)(UnconnectedPageSettle));

export default PageSettle
