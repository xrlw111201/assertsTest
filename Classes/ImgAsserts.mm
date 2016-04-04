//
//  ImgAsserts.h
//  assetsTest
//
//  Created by 刘晖 on 16/4/4.
//
//

#include "ImgAsserts.h"
#include "_ImgAsserts.h"

ImgAssertsDelegate* ImgAsserts::_delegate = NULL;

void ImgAsserts::getImgs(ImgAssertsDelegate* d){

    _delegate = d;
    [_ImgAsserts takeImgs];
}

void ImgAsserts::finishImage(cocos2d::Texture2D* img){
    if(NULL != _delegate && NULL != img){
        _delegate->didFinishPickingWithResult(img);
    }
}