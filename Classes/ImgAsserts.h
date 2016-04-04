//
//  ImgAsserts.h
//  assetsTest
//
//  Created by 刘晖 on 16/4/4.
//
//

#ifndef __assetsTest__ImgAsserts__
#define __assetsTest__ImgAsserts__

class ImgAssertsDelegate {
public:
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result) = 0;
    virtual ~ImgAssertsDelegate() {};
};

class ImgAsserts{
public:
    static void getImgs(ImgAssertsDelegate*);
    static void finishImage(cocos2d::Texture2D*);
    
public:
    static ImgAssertsDelegate* _delegate;
};

#endif /* defined(__assetsTest__ImgAsserts__) */
