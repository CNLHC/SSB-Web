import * as React from 'react';
import {Button, Tag, Modal} from "antd";
import {ISessionInfo} from "../../Typings/TypeSessionInfo";
import './index.scss'
import animation from './checkmarkanimation.json'

const Lottie = require('lottie-react-web').default;
console.log(Lottie)


export interface ISessionInfoProps {
    data?: ISessionInfo
    onCompletePay?: () => void
    payCompleteAnimation?: boolean
}

export interface ISessionInfoState {
    payModalOpen: boolean


}


export class SessionInfo extends React.Component<ISessionInfoProps, ISessionInfoState> {
    state = {
        payModalOpen: false
    }
    public getTotalPrice = () => this.props.data !== undefined ? this.props.data.Items.reduce((cu, it) => cu + it.Numbers * it.ItemDetail.Price, 0) : 0;
    public getTotalNumbers = () => this.props.data !== undefined ? this.props.data.Items.reduce((cu, it) => cu + it.Numbers, 0) : 0;
    public getState = () => {
        const data = this.props.data
        if (data !== undefined) {
            return data.State === "SHOPPING" ? <Tag color={"red"}>等待结算</Tag> : <Tag color={"Green"}>已付款</Tag>
        }
        else
            return;

    }

    render() {
        const {data} = this.props
        return (
            <div className={"ssb-session-info"}>
                {this.props.payCompleteAnimation !== true ? null :
                    <div className={"animation"}>
                        <Lottie

                            isStopped={true}
                            options={{
                                animationData: animation,
                                loop: false
                            }}
                        />
                    </div>
                }
                <ul className={"info-list"}>
                    <li>订单 ID:{data !== undefined ? data.id : undefined}</li>
                    <li>购物车 ID:{data !== undefined ? data.ShoppingCart : undefined}</li>
                    <li>创建时间:{data !== undefined ? data.StartTime.split(".")[0].replace('T', ' ') : undefined}</li>
                    <li>状态:{this.getState()}</li>
                </ul>
                <div className={"session-summary"}>
                    共
                    {this.getTotalNumbers()}
                    件商品, 合计
                    <span className={"money-span"}>{this.getTotalPrice()}</span>
                    元
                </div>
                <div className={"action-bar"}>
                    <Button htmlType={'button'} icon={"pay-circle"} block
                            onClick={() => this.setState({...this.state, payModalOpen: true})}>立即付款</Button>
                </div>
                <Modal
                    title="付款"
                    visible={this.state.payModalOpen}
                    onOk={() => {
                        if (this.props.onCompletePay !== undefined)
                            this.props.onCompletePay();
                        this.setState({...this.state, payModalOpen: false})
                    }}
                    onCancel={() => this.setState({...this.state, payModalOpen: false})}
                    okText={"已经完成付款"}
                    cancelText={"返回继续购物"}
                >
                    订单共计{this.getTotalPrice()}元,请在外部页面完成付款
                </Modal>
            </div>
        )
    }
}

export default SessionInfo