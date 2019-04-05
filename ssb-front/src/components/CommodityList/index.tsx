import * as React from 'react';
import {List} from 'antd'
import {ISessionItem} from "../../Typings/TypeSessionInfo";

export interface ICommodityListProps {
    data?:Array<ISessionItem>
}

export class CommodityList extends React.Component<ICommodityListProps> {
    render(){
        return(
            <div>
                <List
                    dataSource={this.props.data}
                    renderItem={(item:ISessionItem)=>(
                        <div>
                            {item.ItemDetail.Name}
                            {item.ItemDetail.Price}
                        </div>
                    )}
                />
            </div>
        )
    }
}

export default CommodityList