//
//  FlashTool.h
//  NoOneDies
//
//  Created by plter on 14-5-29.
//
//

#ifndef __FLASH_TOOL_H__
#define __FLASH_TOOL_H__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class FlashTool {
    
public:
    static Animate* readJsonSpriteSheet(std::string jsonFile,float delayPerUnit);
};


#endif // __FLASH_TOOL_H__
