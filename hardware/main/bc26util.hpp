class BC26{
    public:
        boolean mIsNetworkAvailable;
        boolean mIsSocketConnect;
        static BC26 * getInst();
        boolean isBusy();
        void deferCommand(const char * command);

        void releaseLock(char * message);

    private:
        static  BC26*  mSingletonObj;
        boolean mBusy;
        char * mMessage;
        //私有化构造器以实现单例
        BC26():mIsNetworkAvailable(false),mIsSocketConnect(false){
        };
};

boolean  BC26::isBusy(){
    return  mBusy;
} 

BC26 * BC26::getInst(){
        if(mSingletonObj==NULL)
            mSingletonObj=new BC26();
        return mSingletonObj;
};

void BC26::deferCommand(const char * command){
    if(!mBusy){
        Serial1.println("send command");
        Serial1.println(command);
        Serial3.println(command);  
        mBusy=true;
    }
}

void BC26::releaseLock(char * message){
    if(mMessage!=NULL)
        delete [] mMessage;
    mMessage = message;
    mBusy =  false;
}

