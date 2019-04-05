import * as React from 'react';
import {Button, Collapse} from "antd";
import {ISessionInfo} from "../../Typings/TypeSessionInfo";
import {number} from "prop-types";
const  Panel = Collapse.Panel

export interface ISessionInfoProps {
    data?:ISessionInfo
}

export class SessionInfo extends React.Component<ISessionInfoProps> {
    public getTotalPrice=()=> this.props.data!==undefined?this.props.data.Items.reduce((cu,it)=>cu+it.Numbers*it.ItemDetail.Price,0):0;
    render(){
        const {data} = this.props
        return(
            <div>
                <Collapse defaultActiveKey={['sessionInfoContent']}>
                    <Panel key={'sessionInfoContent'} header={"订单信息"}>
                        <div>
                        商品总价:{this.getTotalPrice()}
                        订单ID:{data!==undefined?data.id:undefined}
                        </div>
                        <Button htmlType={'button'} type={'primary'} icon={"pay-circle"} block>立即付款</Button>
                    </Panel>

                </Collapse>
            </div>
        )
    }
}

export default SessionInfo