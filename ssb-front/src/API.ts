

export const BASE_URL=process.env.node_env=='production'?"http://ssb.cnworkshop.xyz:4449":"http://localhost:8000";


const APIList={
    GetSessionInfo:(id:number)=>`${BASE_URL}/api/session/${id}/`,
    DeleteItemByID:(SessionID:number)=>`${BASE_URL}/api/session/${SessionID}/removeByID/`
}

export default APIList