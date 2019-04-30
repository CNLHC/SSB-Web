import {NodeWorker} from "inspector";


export const BASE_URL=process.env.node_env=='production'?"http://ssb.cnworkshop.xyz:4450":"http://ssb.cnworkshop.xyz:4450";


const APIList={
    GetSessionInfo:(id:number)=>`${BASE_URL}/api/session/${id}/`,
    DeleteItemByID: (SessionID: number) => `${BASE_URL}/api/session/${SessionID}/removeByID/`,
    SessionDeal: (SessionID: number) => `${BASE_URL}/api/session/${SessionID}/deal/`,
    SessionClose:(SessionID: number) => `${BASE_URL}/api/session/${SessionID}/pay/`,
    SessionCreate: `${BASE_URL}/api/session/`,
    AddItemByBarCode:(SessionID:number)=>`${BASE_URL}/api/session/${SessionID}/barCodeAdd/`,

}

export default APIList