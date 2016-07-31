//
//  RegisterLayer.h
//
//  ע�����
//  
//

#pragma once

#ifndef yuri_RegisterLayer_h
#define yuri_RegisterLayer_h

#include "cocos2d.h"
//CCEditBox,�����ͷ�ļ���Ҫ��Ӷ�Ӧ�������ռ䣬c++���鷳
//ͬʱ����Ҫ�̳�CCEditBoxDelegate
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RegisterLayer : public CCLayer, public CCEditBoxDelegate
{
private:
	//����ǳ�
	CCEditBox * ebUserName;
	//��Ϸ�˺�
	CCEditBox * ebGameAccount;
	//��Ϸ����
	CCEditBox * ebPassword;
	//ȷ������
	CCEditBox * ebConfirmPassword;
	//��������    
	void addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword);

public:
	RegisterLayer(void);
	virtual ~RegisterLayer(void);

	virtual bool init();
	virtual void onExit();

	virtual void onMenuBackCallback(CCObject* pSender);
	virtual void onMenuLoginNowCallback(CCObject* pSender);

	//������EditBox����Ҫ�����⼸������
	virtual void editBoxEditingDidBegin(extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(extension::CCEditBox* editBox);

	 CREATE_FUNC(RegisterLayer);
};

#endif