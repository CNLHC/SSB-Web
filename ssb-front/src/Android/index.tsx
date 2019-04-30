import * as React from 'react';
import {connect} from "react-redux"
import {IRootStore} from "../Typings/TypeRoot";



type IStateProps = ReturnType<typeof mapStateToProps>
type IDispatchProps = ReturnType<typeof mapDispatchToProps>
interface IOwnProps {
}
type IPageProps = IStateProps & IDispatchProps & IOwnProps

export class UnconnectedPage extends React.Component<IPageProps> {
    render(){
        return(
            <div>
                 Page 
            </div>
        )
    }
}

const mapStateToProps = (state:IRootStore) =>({

});
const mapDispatchToProps =(dispatch:any)=>({

});
const Page = connect(mapStateToProps, mapDispatchToProps)(UnconnectedPage);

export default Page
