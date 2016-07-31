#include "RegisterLayer.h"

#include "Common\CommonFunction.h"
#include "cocos2d.h"

USING_NS_CC;

RegisterLayer::RegisterLayer(void)
{
}

RegisterLayer::~RegisterLayer(void)
{
}

//ʵ�ֳ�ʼ����������������ɽ���ؼ������
bool RegisterLayer::init()
{

	if(!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);

	CCLOG("and here is RegisterLayer");
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLOG("origin:%f %f", origin.x, origin.y);

	//����ͼƬ
	CCSprite * bgSprite = CCSprite::create("MengBgImage.png");
	//bgSprite->setAnchorPoint(ccp(0.5, 0.5));
	bgSprite->setPosition(ccp(size.width/2.0f, size.height/2.0f));
	CCLOG("size: %f %f", size.width, size.height);
	float spx = bgSprite->getTextureRect().getMaxX();
	float spy = bgSprite->getTextureRect().getMaxY();
	CCLOG("spx,spy:%f %f", spx, spy);
	float scaleW = size.width / spx;
	float scaleH = size.height / spy;
	CCLOG("scale: %f %f", scaleW, scaleH);
	//�ñ���ͼƬȫ��
	bgSprite->setScaleX(scaleH); //���þ��������ű���
	bgSprite->setScaleY(scaleH);
	/*bgSprite->setAnchorPoint(CCPointZero);*/
	this->addChild(bgSprite, 0);

	//���ذ�ť
	CCMenuItemImage * backBtn = CCMenuItemImage::create(
		"CloseWin1.png","CloseWin2.png",this,
		menu_selector(RegisterLayer::onMenuBackCallback)
		 );
	 CCSize backViewSize = backBtn->getContentSize();
	 CCLOG("backview.width:%f", backViewSize.width);
	 backBtn->setPosition(ccp(origin.x + backViewSize.width , size.height  - 40));
	 CCMenu * backMenu = CCMenu::create(backBtn, NULL);
	 backMenu->setPosition(CCPointZero);
	 this->addChild(backMenu);

	 //��������
	 CCLabelTTF* pLabel = CCLabelTTF::create("Register Account", "Thonburi", 24);
	 pLabel->setPosition(ccp(size.width/2, size.height - 40));
	 this->addChild(pLabel);

	 //������¼��ť
	 CCMenuItemImage * loginNowBtn = CCMenuItemImage::create(
		"RegisterAndLogin.png","RegisterAndLogin.png",this,
		menu_selector(RegisterLayer::onMenuLoginNowCallback)
		 );
	 CCSize loginSize = loginNowBtn->getContentSize();
	 loginNowBtn->setPosition(ccp(size.width/2 , 100));
	 CCMenu * loginMenu = CCMenu::create(loginNowBtn, NULL);
	 loginMenu->setPosition(CCPointZero);
	 this->addChild(loginMenu);

	 //���ע������������
	 //����ǳ�����򱳾�
	 CCSprite* userNameSprite = CCSprite::create("Register1.png");
	 CCSize inputBgSize = userNameSprite->getContentSize();
	 //����򱳾��ĸ߶�
	 float itemHeight = inputBgSize.height;
	 userNameSprite->setPosition(ccp(size.width/2, size.height - 140));
	 this->addChild(userNameSprite);
	 //����ǳ������
	 CCSize editSize = CCSizeMake(288, 32);
	 ebUserName = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint userNamePoint = CCPointMake(size.width / 2 + 80, size.height - 140);
	 addEditBox(ebUserName, userNamePoint, UTEXT("username"),false);

	 //��Ϸ�˺�����򱳾�
	 CCSprite* gameAccountSprite = CCSprite::create("Register2.png");
	 gameAccountSprite->setPosition(ccp(size.width/2, size.height - itemHeight - 200));
	 this->addChild(gameAccountSprite);
	 //��Ϸ�˺������
	 ebGameAccount = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint gameAccountPoint = CCPointMake(size.width / 2 + 80, size.height -  itemHeight - 200);
	 addEditBox(ebGameAccount, gameAccountPoint, UTEXT("game account"),false);

	 //��Ϸ��������򱳾�
	 CCSprite* passwordSprite = CCSprite::create("Register3.png");
	 passwordSprite->setPosition(ccp(size.width/2, size.height - itemHeight * 2 -240));
	 this->addChild(passwordSprite);
	 //��Ϸ���������
	 ebPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint passwordPoint = CCPointMake(size.width / 2 + 80, size.height - itemHeight * 2 -240);
	 addEditBox(ebPassword, passwordPoint, UTEXT("password"),true);

	 //ȷ����������򱳾�
	 CCSprite* confirmPasswordSprite = CCSprite::create("Register4.png");
	 confirmPasswordSprite->setPosition(ccp(size.width/2, size.height - itemHeight *3  -280));
	 this->addChild(confirmPasswordSprite);
	 //ȷ�����������
	 ebConfirmPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint confirmPasswordPoint = CCPointMake(size.width / 2 + 80, size.height - itemHeight * 3 -280);
	 addEditBox(ebConfirmPassword, confirmPasswordPoint, UTEXT("confirm password"),true);

	 this->setVisible(false);

	return true;
}

/*
* ���� �� �򳡾�����������������Ӧ����
* editBox : �����  
*editPoint : λ��
* defaultValue : ȱʡ�ı�
* isPassword : true-���룬false-������
*/
void RegisterLayer::addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword)
{
	editBox->CCNode::setPosition(editPoint.x, editPoint.y);
	editBox->setFontName("GeezaPro");
	editBox->setFontSize(18);
	//�����������ɫ
	editBox->setFontColor(ccBLACK);
	//�����ȱʡ����
	editBox->setPlaceHolder(defaultValue);
	//ȱʡ������ɫ
	ccColor3B hintColor = {118,114,114};
	editBox->setPlaceholderFontColor(hintColor); 
	//��󳤶�
	editBox->setMaxLength(20); 
	//Ĭ��ʹ�ü���return����ΪDone
	editBox->setReturnType(kKeyboardReturnTypeDone); 
	////�������ģʽ
	editBox->setInputMode(kEditBoxInputModeEmailAddr); 
	if (isPassword) {
		//��������ʱ�������
        editBox->setInputFlag(kEditBoxInputFlagPassword);
     }
	editBox->setDelegate(this); //����ί�д������Ϊ��ǰ��
	this->addChild(editBox);
}

void RegisterLayer::onMenuLoginNowCallback(CCObject* pSender)
{
	//������¼��ť���
	CCLOG("on Login now menu clicked");
	//��ʼע��
	//��ȡ������е�����
	const char * userName = ebUserName->getText();
	const char * gameAccount = ebGameAccount->getText();
	const char * password = ebPassword->getText();
	const char * confirmPassword = ebConfirmPassword->getText();
	CCLOG("result:[%s, %s, %s, %s]", userName, gameAccount, password, confirmPassword);
}

void RegisterLayer::onMenuBackCallback(CCObject* pSender)
{
	//���ذ�ť���
	CCLOG("on back menu clicked");
	this->setVisible(false);
}

//���̵�����������ý���ʱ����
void RegisterLayer::editBoxEditingDidBegin(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
}

//�������غ������ʧȥ����ʱ����
void RegisterLayer::editBoxEditingDidEnd(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidEnd");
}

//��������ı��仯ʱ����
void RegisterLayer::editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text)
{
	//CCLOG("editBoxTextChanged:%s", text);
}

//���·��ؼ������������λ��ʱ�����������ǰ�����ʱ��������
void RegisterLayer::editBoxReturn(extension::CCEditBox* editBox)
{
	CCLOG("editBoxReturn");
}

void RegisterLayer::onExit()
{
	CCLayer::onExit();
}
