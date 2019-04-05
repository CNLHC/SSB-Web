export interface ICommodity{
    id:number
    Name:  string
    Price: number
    Thumbnail:string
}

export  interface ICommodityList{
    results:Array<ICommodity>
}

