#pragma once
class BC26{
    public:
        bool mIsNetworkAvailable;
        bool mIsSocketConnect;
        bool mBusy;
        bool mIsResponseSet;

        BC26*  mSingletonObj;
        BC26 * getInst();
        bool isBusy();
        void deferCommand(const char * command);
        char *releaseLock();
        void setResponse(char * message);
        BC26(): mIsNetworkAvailable(false),
                mIsSocketConnect(false),
                mBusy(false),
                mIsResponseSet(false){
        };
        char * mMessage;
    private:

        //私有化构造器以实现单例
};

bool BC26::isBusy(){
    return  mBusy;
} 

BC26 * BC26::getInst(){
        if(mSingletonObj==NULL)
            mSingletonObj=new BC26();
        return mSingletonObj;
};

void BC26::deferCommand(const char * command){
    if(!mBusy){
        Serial1.println("defer command");
        Serial1.println(command);
        Serial3.println(command);
        mBusy=true;
        mIsResponseSet = false;
    }
    else{
        Serial1.println("defer locked");
    }
}

void BC26::setResponse(char * message){
    if(mBusy){
        Serial1.println("set Response");
        // Serial1.println(message);
        mMessage = message;
        mIsResponseSet = true;
    }
}

char * BC26::releaseLock(){
        mBusy=false;
        mIsResponseSet = false;
        return mMessage;
}
    
