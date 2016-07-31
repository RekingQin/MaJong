//
//  LoginScene.h
//
//  ��¼����
//  
//

#pragma once

#ifndef yuri_LoginScene_h
#define yuri_LoginScene_h

#include "cocos2d.h"
//CCEditBox,�����ͷ�ļ���Ҫ��Ӷ�Ӧ�������ռ䣬c++���鷳
//ͬʱ����Ҫ�̳�CCEditBoxDelegate
#include "cocos-ext.h"

#include "../Layer/RegisterLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene : public CCLayer, public CCEditBoxDelegate
{
	RegisterLayer * registerLayer;

private:
	//������������һ���˺�һ����������
	CCEditBox * ebUserName;
	CCEditBox * ebPassword;
	//��������    
	void addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword);

public:
	LoginScene(void);
	virtual ~LoginScene(void);

	virtual bool init();
	virtual void onExit();

	static CCScene* scene();

	virtual void onMenuLoginCallback(CCObject* pSender);
	virtual void onMenuRegisterCallback(CCObject* pSender);
	virtual void onMenuQuickGameCallback(CCObject* pSender);

	//������EditBox����Ҫ�����⼸������
	virtual void editBoxEditingDidBegin(extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(extension::CCEditBox* editBox);
     virtual void editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text);
     virtual void editBoxReturn(extension::CCEditBox* editBox);

	 //��Ӧ���ؼ�  
	 virtual void keyBackClicked();  

	CREATE_FUNC(LoginScene);
};

#endif