import * as React from 'react';
import {Icon, List} from 'antd'
import {ISessionItem} from "../../Typings/TypeSessionInfo";
import {BASE_URL} from "../../API";
import  './index.scss'

export interface ICommodityListProps {
    data?:Array<ISessionItem>
    onClickDelete?:(itemID:number)=>void
}

export class CommodityList extends React.Component<ICommodityListProps> {
    render(){
        return(
            <div >
                <List
                    dataSource={this.props.data}
                    split={true}
                    renderItem={(item:ISessionItem)=>(
                        <div className={"ssb-commodity-card"}>
                            <div className={"thumbnail-box"}>
                                <img src={`${BASE_URL}${item.ItemDetail.Thumbnail}`}/>
                            </div>
                            <div className={"info-box"}>
                                <div className={"commodity-name"}>
                                    <div className={"commodityTitle"}>{item.ItemDetail.Name}</div>
                                    <div className={"deleteIcon"}><Icon  type={"delete"} onClick={()=>{
                                        if(this.props.onClickDelete!==undefined)
                                            this.props.onClickDelete(item.ItemDetail.id);
                                    }} /></div>
                                </div>
                                <div className={"number-info-box"}>
                                    <div className={"commodity-price"}>{item.ItemDetail.Price}</div>
                                    <div className={"commodity-number"}>{item.Numbers}</div>
                                </div>
                            </div>
                        </div>
                    )}
                />
            </div>
        )
    }
}

export default CommodityList