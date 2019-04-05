import * as React from 'react';
import {Button, Collapse, Tag} from "antd";
import {ISessionInfo} from "../../Typings/TypeSessionInfo";
import './index.scss'

export interface ISessionInfoProps {
    data?:ISessionInfo
}

export class SessionInfo extends React.Component<ISessionInfoProps> {
    public getTotalPrice=()=> this.props.data!==undefined?this.props.data.Items.reduce((cu,it)=>cu+it.Numbers*it.ItemDetail.Price,0):0;
    public getTotalNumbers=()=> this.props.data!==undefined?this.props.data.Items.reduce((cu,it)=>cu+it.Numbers,0):0;
    public getState=()=>{
        const data = this.props.data
        if(data!==undefined){
            return data.State==="SHOPPING"?<Tag color={"red"}>等待结算</Tag>:<Tag color={"yellow"}>正在付款 </Tag>
        }
        else
            return ;

    }
    render(){
        const {data} = this.props
        return(
            <div className={"ssb-session-info"}>
                <ul className={"info-list"}>
                    <li>订单 ID:{data!==undefined?data.id:undefined}</li>
                    <li>购物车 ID:{data!==undefined?data.ShoppingCart:undefined}</li>
                    <li>创建时间:{data!==undefined?data.StartTime.split(".")[0].replace('T',' '):undefined}</li>
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
                <Button htmlType={'button'}  icon={"pay-circle"} block>立即付款</Button>
                </div>
            </div>
        )
    }
}

export default SessionInfo