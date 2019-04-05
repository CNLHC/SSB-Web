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
        void releaseLock(char * message);
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
    mBusy=true;
    Serial1.println("send command");
    Serial1.println(command);
    Serial3.println(command);
}

void BC26::releaseLock(char * message){
    Serial1.println(message);
    mMessage = message;
}
    
