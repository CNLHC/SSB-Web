import * as React from 'react';
import {connect} from "react-redux"
import {
    IDeleteItemQuery,
    ThunkCloseSession,
    ThunkCreateSession,
    ThunkDealSession,
    ThunkDeleteItemByID,
    ThunkGetSessionInfo
} from "./actions";
import CommodityList from "../../components/CommodityList";

import SessionInfo from "../../components/SessionInfo";
import {RouteComponentProps, withRouter} from "react-router";
import {Button, Collapse, Icon, PageHeader} from "antd";
import './index.scss'
import {IAndroidInterface} from "../../App";

export declare var Android: IAndroidInterface;


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
        console.log(Android)
        if (Android !== undefined)
            Android.showToast("Start")
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
                            <Icon type="shopping-cart"
                                  onClick={() => this.props.onCreateSession({ShoppingCart: this.getSessionID()}, () => this.props.onGetSessionInfo({SessionID: this.getSessionID()}))}/>
                            <div className={"text"}>点击开始购物</div>
                        </div>
                    </div> :
                    <div>
                        <Collapse defaultActiveKey={['sessionInfoContent', 'sessionItems']}
                                  className={'settle-page-collapse'}

                        >
                            <Panel key={'sessionInfoContent'} header={
                                <div style={{
                                    display: 'flex',
                                    justifyContent: 'space-between'

                                }}>
                            <span>
                            订单信息
                            </span>

                                </div>}>
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
                                             onCloseSession={() => {
                                                 const payload = {SessionID: this.getSessionID()}
                                                 this.props.onCloseSession(payload, () => this.props.onGetSessionInfo(payload))
                                             }}
                                             payCompleteAnimation={this.state.payCompleteAnimation}
                                />
                            </Panel>

                            <Panel key={'sessionItems'}
                                   disabled
                                   header={
                                <div style={{
                                    display: 'flex',
                                    justifyContent: 'space-between'

                                }}>
                            <span>
                                商品详情
                            </span>
                                    <Button type="primary" shape="circle" icon="plus"
                                            onClick={() => Android.invokeQRScan()}/>
                                </div>


                                }>
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
                    </div>
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
    onDealSession: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkDealSession(payload, onSuc, onFai)),
    onCloseSession: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkCloseSession(payload, onSuc, onFai)),
    onCreateSession: (payload: any, onSuc?: () => any, onFai?: () => any) => dispatch(ThunkCreateSession(payload, onSuc, onFai)),
});

const PageSettle = withRouter(connect(mapStateToProps, mapDispatchToProps)(UnconnectedPageSettle));

export default PageSettle
