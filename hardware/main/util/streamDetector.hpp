/*!
to dectect specific string pattern from char stream with O(n) space.
*/

class streamPatternDetector{
    public:
        streamPatternDetector(const char *);
        ~streamPatternDetector();
        void reset();
        void feed(char);
        int getHitTimes(){ return mHitTimes; };

    private:
        char *mPatternBuffer;
        int mPatternLength;
        int mInnerFSM;
        int mHitTimes;
};

streamPatternDetector::streamPatternDetector(const char* pattern):mInnerFSM(0),mHitTimes(0)
{
    int i;
    int len =  strlen(pattern);
    mPatternBuffer = new char[len];
    mPatternLength = len;
    for (i=0;i<len;i++)
        mPatternBuffer[i] = pattern[i];
}

streamPatternDetector::~streamPatternDetector(){
    delete [] mPatternBuffer;
}

void streamPatternDetector::reset(){
    mInnerFSM = 0 ;
    mHitTimes = 0 ;
}
void streamPatternDetector::feed(char ch){
    if(ch == mPatternBuffer[mInnerFSM])
        mInnerFSM++;

    if (mInnerFSM == mPatternLength){
        mInnerFSM=0;
        mHitTimes++;
    }
}















