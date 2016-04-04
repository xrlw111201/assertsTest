//
//  _ImgAsserts.cpp
//  assetsTest
//
//  Created by 刘晖 on 16/4/4.
//
//

#include "_ImgAsserts.h"
#include "ImgAsserts.h"
//#include "cocos2d.h"

using namespace cocos2d;

@implementation _ImgAsserts

+(void)takeImgs{

    NSLog(@"开始枚举资源库");

    NSMutableArray* imageArray = [[NSMutableArray alloc] initWithCapacity:1];
    ALAssetsLibrary *assetsLibrary;
    NSMutableArray *groupArray;
    assetsLibrary = [[ALAssetsLibrary alloc] init];
    groupArray=[[NSMutableArray alloc] initWithCapacity:1];
    [assetsLibrary enumerateGroupsWithTypes:ALAssetsGroupAll usingBlock:^(ALAssetsGroup *group, BOOL *stop) {
        if (group) {
            [groupArray addObject:group];
            
            //输出相册信息
            //例如 Name:柚子相机, Type:Album, Assets count:1
            NSLog(@"%@",group);
        }else {
            
            //枚举结束，这时group等于空
            NSUInteger nCountAlbum = [groupArray count];
            if (nCountAlbum > 0) {
                
                //把所有的相册储存完毕，可以展示相册列表
                NSLog(@"本地有 %d 个相册", nCountAlbum);
                
                for(ALAssetsGroup* _group in groupArray){
                    [_group enumerateAssetsUsingBlock:^(ALAsset *result, NSUInteger index, BOOL *stop) {
                        if (result) {
                            [imageArray addObject:result];
                            NSLog(@"result -- %@",result);
                            
                            Image* image = new Image();
                            
                            UIImage* img = [UIImage imageWithCGImage: result.thumbnail];
                            NSData *imgData = UIImageJPEGRepresentation(img, 1.0);  //第二个参数为压缩比例 compression is 0(most)..1(least)
                            NSUInteger len = [imgData length];
                            
                            Byte* byteData = (Byte*)malloc(len);
                            memcpy(byteData, [imgData bytes], len);
                            
                            image->initWithImageData(byteData, len);
                            
                            free(byteData);
                            
                            Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
                                
                                Texture2D* texture = new Texture2D();
                                texture->initWithImage(image);
//                                texture->autorelease();
                                
                                image->release();
                                
                                //调用代理类，将照片纹理交给cocos2dx处理
                                ImgAsserts::finishImage(texture);
                            });

                        }
                    }];
                }
            } else {
                //没有任何有资源的相册，输出提示
                NSLog(@"no albums.");
            }
        }
    } failureBlock:^(NSError *error) {
        //获取资源库失败
        NSLog(@"Group not found!\n");
    }];
}



@end