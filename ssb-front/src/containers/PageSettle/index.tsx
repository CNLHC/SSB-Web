import * as React from 'react';
import {connect} from "react-redux"
import {IDeleteItemQuery, ThunkDealSession, ThunkDeleteItemByID, ThunkGetSessionInfo} from "./actions";
import CommodityList from "../../components/CommodityList";

import SessionInfo from "../../components/SessionInfo";
import {RouteComponentProps, withRouter} from "react-router";
import {Collapse, Icon, PageHeader} from "antd";
import './index.scss'


const Panel = Collapse.Panel

type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>

interface IOwnProps extends RouteComponentProps<{ CartId: string }> {


}

interface IPageState {
    payCompleteAnimation: boolean

}

type IPageProps = IStateProps & IDispatchProps & IOwnProps

export class UnconnectedPageSettle extends React.Component<IPageProps, IPageState> {
    state = {
        payCompleteAnimation: false
    }

    private getSessionID = () => parseInt(this.props.match.params.CartId)

    componentDidMount() {
        const payload = {SessionID: this.props.match.params.CartId}
        this.props.onGetSessionInfo(payload);
        //For DEMO
        // window.setInterval(()=>{
        //     this.props.onGetSessionInfo(payload)
        // },2000);
        // window.setInterval(()=>window.scrollTo(0,document.body.scrollHeight),1000);

    }

    render() {
        return (
            <div className={"ssb-settle-page"}>
                <PageHeader
                    title="易迈无人商店"
                    subTitle="结算页面"
                />
                {this.props.sessionInfo == undefined ?
                    <div className={"warning"}>
                        <div className={"content"}>
                            <Icon type="warning"/>
                            <div className={"text"}>访问的页面不存在</div>
                        </div>
                    </div> :
                    <Collapse defaultActiveKey={['sessionInfoContent', 'sessionItems']}
                              className={'settle-page-collapse'}>
                        <Panel key={'sessionInfoContent'} header={"订单信息"}>
                            <SessionInfo data={this.props.sessionInfo}
                                         onCompletePay={() => this.props.onDealSession(
                                             {SessionID: this.getSessionID()},
                                             () => this.props.onGetSessionInfo(
                                                 {SessionID: this.getSessionID()},
                                                 () => {
                                                     window.setTimeout(() => this.setState({
                                                         ...this.state,
                                                         payCompleteAnimation: false
                                                     }), 2000);
                                                     this.setState({...this.state, payCompleteAnimation: true});

                                                 }
                                             )
                                         )}
                                         payCompleteAnimation={this.state.payCompleteAnimation}
                            />
                        </Panel>
                        <Panel key={'sessionItems'} header={"商品详情"}>
                            <CommodityList
                                data={this.props.sessionInfo !== undefined ? this.props.sessionInfo.Items : undefined}
                                onClickDelete={(itemID: number) => {
                                    this.props.onDeleteItem({
                                        SessionID: this.getSessionID(),
                                        DeletePayload: {ItemID: itemID}
                                    }, () => this.props.onGetSessionInfo({SessionID: this.getSessionID()}))
                                }}
                            />
                        </Panel>
                    </Collapse>
                }
            </div>
        )
    }
}

const mapStateToProps = (state: any) => ({
    sessionInfo: state.settle.sessionInfo,
    loadingSessionInfo: state.settle.loadingSessionInfo
});

const mapDispatchToProps = (dispatch: any) => ({
    onGetSessionInfo: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkGetSessionInfo(payload, onSuc, onFai)),
    onDeleteItem: (payload: IDeleteItemQuery, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkDeleteItemByID(payload, onSuc, onFai)),
    onDealSession: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkDealSession(payload, onSuc, onFai))
});

const PageSettle = withRouter(connect(mapStateToProps, mapDispatchToProps)(UnconnectedPageSettle));

export default PageSettle
