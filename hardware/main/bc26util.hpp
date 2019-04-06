#pragma once
class BC26{
    public:
        char mIsNetworkAvailable;
        char mIsSocketConnect;
        char mBusy;
        BC26*  mSingletonObj;
        BC26 * getInst();
        bool isBusy();
        void deferCommand(const char * command);
        char *releaseLock(char *message);
        void setResponse(char * message);
        BC26():mIsNetworkAvailable(false),mIsSocketConnect(false),mBusy(false){
            mSingletonObj = this;
        };

    private:
        char * mMessage;
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
    }
    else{
        Serial1.println("defer locked");
    }
}

void BC26::setResponse(char * message){
    if(mBusy){
        Serial1.println("set Response");
        Serial1.println(message);
        mMessage = message;
        mBusy=false;
    }
}

char * BC26::releaseLock(char *message){
        mBusy=false;
        return mMessage;
}
    
