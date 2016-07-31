#include "LoginScene.h"

#include "Common\CommonFunction.h"
#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;

LoginScene::LoginScene(void)
{
}


LoginScene::~LoginScene(void)
{
}

CCScene* LoginScene::scene()
{
	//����һ������
	CCScene* scene = CCScene::create();
	//����һ����¼��Layer
	LoginScene* layer = LoginScene::create();
	//��Layer��ӵ�������ȥ
	scene->addChild(layer);
	//������¼�ĳ������㴴�������
	return scene;
}

//ʵ�ֳ�ʼ����������������ɾ��鰴ť�����
bool LoginScene::init()
{

	if(!CCLayer::init())
	{
		return false;
	}

	setKeypadEnabled(true);

	//��ʼ��ע�����
	registerLayer = RegisterLayer::create();
	this->addChild(registerLayer, 2);

	CCLOG("and here is LoginScene");
	CCSprite * bgSprite = CCSprite::create("LoginBg_1.png");

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLOG("origin:%f %f", origin.x, origin.y);

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

	this->addChild(bgSprite, 0);

	 CCLabelTTF* pLabel = CCLabelTTF::create("LoginScene...", "Thonburi", 24);

	 pLabel->setPosition(ccp(size.width/2, size.height/2 +290));

	 this->addChild(pLabel);

	 //��¼��ť
	 CCMenuItemImage * loginBtn = CCMenuItemImage::create(
		"LoginBtn_1.png","LoginBtn_1.png",this,
		menu_selector(LoginScene::onMenuLoginCallback)
		 );
	 //�����¼��ť�Ĵ�С
	 CCSize loginSize = loginBtn->getContentSize();
	 loginBtn->setPosition(ccp(size.width - loginSize.width - 100, size.height / 2 - 20));
	 CCMenu * loginMenu = CCMenu::create(loginBtn, NULL);
	 loginMenu->setPosition(CCPointZero);
	 this->addChild(loginMenu);

	 //ע�ᰴť
	 CCMenuItemImage * registerBtn = CCMenuItemImage::create(
		"RegisterBtn.png","RegisterBtn.png",this,
		menu_selector(LoginScene::onMenuRegisterCallback)
		 );
	 //CCSize registerSize = registerBtn->getContentSize();
	 registerBtn->setPosition(ccp(size.width/2 - 80, size.height / 2 - 120));
	 CCMenu * registerMenu = CCMenu::create(registerBtn, NULL);
	 registerMenu->setPosition(CCPointZero);
	 this->addChild(registerMenu);
	 //������Ϸ��ť
	 CCMenuItemImage * quickGameBtn = CCMenuItemImage::create(
		"QuickLogin.png","QuickLogin.png",this,
		menu_selector(LoginScene::onMenuQuickGameCallback)
		 );
	 //CCSize quickGameSize = quickGameBtn->getContentSize();
	 quickGameBtn->setPosition(ccp(size.width/2 + 80, size.height / 2 - 120));
	 CCMenu * quickGameMenu = CCMenu::create(quickGameBtn, NULL);
	 quickGameMenu->setPosition(CCPointZero);
	 this->addChild(quickGameMenu);

	 //������������һ���˺�һ����������
	 //ʹ������float���͵����ִ���һ��size
	 CCSize editSize = CCSizeMake(300, 48);
	 ebUserName = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint userNamePoint = CCPointMake(size.width / 2 + 100, size.height / 2 + 10);
	 addEditBox(ebUserName, userNamePoint, UTEXT("account"),false);

	 ebPassword = CCEditBox::create(editSize, CCScale9Sprite::create());
	 CCPoint passwordPoint = CCPointMake(size.width / 2 + 100, size.height / 2 - 40);
	 addEditBox(ebPassword, passwordPoint, UTEXT("pasword"),true);

	 //��ʼ����ȡ�ϴ��û�������û���ֱ������
	 string username = CCUserDefault::sharedUserDefault()->getStringForKey("username");
	 //string תchar
	 const char *string=std::string(username).c_str();
	 CCLOG("username:%s", string);
	 ebUserName->setText(string);

	return true;
}

/*
* ���� �� �򳡾�����������������Ӧ����
* editBox : �����  
*editPoint : λ��
* defaultValue : ȱʡ�ı�
* isPassword : true-���룬false-������
*/
void LoginScene::addEditBox(CCEditBox * editBox,CCPoint editPoint, char * defaultValue,bool isPassword)
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

void LoginScene::onMenuLoginCallback(CCObject* pSender)
{
	//��¼��ť���
	CCLOG("on Login menu clicked");

	//ʹ��CCUserDefault��ʵ��һ��ע�Ṧ��
	CCUserDefault::sharedUserDefault()->setStringForKey("username", ebUserName->getText());
	CCUserDefault::sharedUserDefault()->setStringForKey("password", ebPassword->getText());
	CCUserDefault::sharedUserDefault()->flush();

	//�����ڿ��ٵ�¼�Ļص�������ֻ��Ҫ��ȡ��Ӧ��"userName"��"password"����.
	string username = CCUserDefault::sharedUserDefault()->getStringForKey("username");
	string password = CCUserDefault::sharedUserDefault()->getStringForKey("password");

	//c_str()��������һ��ָ������C�ַ�����ָ��, �����뱾string����ͬ
	CCLOG("username:%s,pasword:%s", username.c_str(), password.c_str());
}

void LoginScene::onMenuRegisterCallback(CCObject* pSender)
{
	//ע�ᰴť���
	CCLOG("on register menu clicked");
	registerLayer->setVisible(true);
}

void LoginScene::onMenuQuickGameCallback(CCObject* pSender)
{
	//������Ϸ��ť���
	CCLOG("on quickgame menu clicked");
	//���������Ϸ��ť����ʱ�����ֱ�ӽ���˵���ť����ʼ��Ϸ��
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

//���̵�����������ý���ʱ����
void LoginScene::editBoxEditingDidBegin(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
}

//�������غ������ʧȥ����ʱ����
void LoginScene::editBoxEditingDidEnd(extension::CCEditBox* editBox)
{
	CCLOG("editBoxEditingDidEnd");
}

//��������ı��仯ʱ����
void LoginScene::editBoxTextChanged(extension::CCEditBox* editBox, const std::string& text)
{
	//CCLOG("editBoxTextChanged:%s", text);
}

//���·��ؼ������������λ��ʱ�����������ǰ�����ʱ��������
void LoginScene::editBoxReturn(extension::CCEditBox* editBox)
{
	CCLOG("editBoxReturn");
}

void LoginScene::keyBackClicked()
{
	//����˷��ذ�ť,ִ���˳�����
	CCLOG("keyBackClicked");
	onExit();
	exit(0);
}

void LoginScene::onExit()
{
	CCLayer::onExit();
}
