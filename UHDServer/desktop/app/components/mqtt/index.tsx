import * as React from 'react';
import {ReactNode} from 'react';

import {connect} from "react-redux"
import {ActUpdateCommodityList} from "./actions";
import {ICommodity} from "../../Typing";


type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>

interface IOwnProps {
    children: ReactNode
}

type IPageProps = IStateProps & IDispatchProps & IOwnProps


const mapStateToProps = (state: any) => ({});
const mapDispatchToProps = (dispatch: any) => ({
    onDataUpdate: (CommodityList:ICommodity[]) => dispatch(ActUpdateCommodityList(CommodityList))
});


export class mqttReduxDaemon extends React.Component<IPageProps> {
    public client: any

    constructor(props: IPageProps) {
        super(props);
    }

    shouldComponentUpdate() {
        return false
    }


    render() {
        return (
            <div>
                {this.props.children}
            </div>
        )
    }
}

const MqttReduxDaemon = connect(mapStateToProps, mapDispatchToProps)(mqttReduxDaemon);

export default MqttReduxDaemon
