import * as React from 'react';
import {connect} from "react-redux"
import {IRootStore} from "../../Typings/TypeRoot";



type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>
interface IOwnProps {
}
type IPageProps = IStateProps & IDispatchProps & IOwnProps

export class UnconnectedPagePay extends React.Component<IPageProps> {
    render(){
        return(
            <div>
                Pay Page
            </div>
        )
    }
}

const mapStateToProps = (state:IRootStore) =>({
});
const mapDispatchToProps =(dispatch:any)=>({
});
const PagePay = connect(mapStateToProps, mapDispatchToProps)(UnconnectedPagePay);

export default PagePay
