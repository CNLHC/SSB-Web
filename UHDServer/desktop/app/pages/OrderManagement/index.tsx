import * as React from 'react';
import {connect} from "react-redux"
import {List} from "antd";
import {ICommodity, IRootStore} from "../../Typing";


type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>

interface IOwnProps {
}

type IPageProps = IStateProps & IDispatchProps & IOwnProps

export class UnconnectedPageCommodityCheck extends React.Component<IPageProps> {
    render() {
        return (
            <div>
                购买商品
                <List
                    size="small"
                    bordered
                    dataSource={this.props.commodityList}
                    renderItem={(item: ICommodity) => (<List.Item>{item.UHDTag}</List.Item>)}
                />
            </div>
        )
    }
}

const mapStateToProps = (state: IRootStore) => ({
    commodityList: state.mqtt.CommodityList
});
const mapDispatchToProps = (dispatch: any) => ({});
const PageCommodityCheck = connect(mapStateToProps, mapDispatchToProps)(UnconnectedPageCommodityCheck);

export default PageCommodityCheck
