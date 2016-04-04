//
//  ImgAsserts.h
//  assetsTest
//
//  Created by 刘晖 on 16/4/4.
//
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define HOMEBG  1000
#define OPENIMG 1001
#define SENDIMG 1002
#define EXIT    1003
#define LBL     1004

#include "cocos2d.h"
#include <vector>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ImgAsserts.h"
#endif

class HelloWorld : public cocos2d::Layer

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
, public ImgAssertsDelegate
#endif

{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void didFinishPickingWithResult(cocos2d::Texture2D* result);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
    void cleanTxture2d();
    void getImgs();
    void sendImg();
    
    float m_width;
    float m_height;
    std::vector<cocos2d::Texture2D*> m_vector;
};

#endif // __HELLOWORLD_SCENE_H__