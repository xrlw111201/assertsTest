//
//  ImgAsserts.h
//  assetsTest
//
//  Created by 刘晖 on 16/4/4.
//
//

#include "HelloWorldScene.h"
#include <time.h>
#include <stdlib.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    srand(time(NULL));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_width = visibleSize.width;
    m_height = visibleSize.height;
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true); // not need
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    Sprite* bg = Sprite::create("home_bg.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(HOMEBG);
    addChild(bg);
    
    Sprite* openImg = Sprite::create("openImg.png");
    openImg->setPosition(m_width*0.2531, m_height*0.3468);
    openImg->setTag(OPENIMG);
    addChild(openImg);
    
    Sprite* sendImg = Sprite::create("sendImg.png");
    sendImg->setPosition(m_width*0.7484, m_height*0.3468);
    sendImg->setTag(SENDIMG);
    addChild(sendImg);
    
    Label* lbl = Label::create();
    lbl->setTextColor(Color4B::WHITE);
    lbl->setSystemFontSize(50.00);
    lbl->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl->setString("0");
    lbl->setPosition(m_width*0.5000, m_height*0.1800);
    lbl->setTag(LBL);
    addChild(lbl);
    
    Sprite* pExit = Sprite::create("exits_b.png");
    pExit->setPosition(m_width*0.5000, m_height*0.1000);
    pExit->setTag(EXIT);
    addChild(pExit);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);
    
    if(getChildByTag(EXIT)->getBoundingBox().containsPoint(touchLocation)){
        Director::getInstance()->stopAnimation();
        Director::getInstance()->end();
        cleanTxture2d();
        exit(0);
    }
    if(getChildByTag(OPENIMG)->getBoundingBox().containsPoint(touchLocation)){
        getImgs();
    }
    if(getChildByTag(SENDIMG)->getBoundingBox().containsPoint(touchLocation)){
        sendImg();
    }
    return false;
}

void HelloWorld::getImgs(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    if(m_vector.size() > 0) return;

    ImgAsserts::getImgs(this);
    
#endif
}

void HelloWorld::sendImg(){

    unsigned long total = m_vector.size();

    if(0 == total){
        return;
    }

    //随机显示一张
    int index = rand()%(total);
    log("抽第%d张", index);
    Texture2D* result = m_vector.at(index);
    Sprite* sp = Sprite::createWithTexture(result);
    sp->setPosition(m_width*0.78484, m_height*0.4668);
    this->addChild(sp);
}

void HelloWorld::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    m_vector.push_back(result);
    
    char ch[30] = {0};
    sprintf(ch, "%lu", m_vector.size());
    std::string str = ch;
    Label* lbl = (Label*)getChildByTag(LBL);
    lbl->setString(str);
}

void HelloWorld::cleanTxture2d(){
    std::vector<Texture2D*>::iterator it;
    for(it=m_vector.begin(); it!=m_vector.end(); it++){
        (*it)->releaseGLTexture();
        (*it)->release();
        (*it) = NULL;
    }
    m_vector.clear();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
