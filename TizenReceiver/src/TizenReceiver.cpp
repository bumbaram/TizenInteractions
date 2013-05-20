/**
 * Name        : TizenReceiver
 * Version     :
 * Vendor      :
 * Description :
 */


#include "TizenReceiver.h"
#include "TizenReceiverFrame.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenReceiverApp::TizenReceiverApp(void) {
}

TizenReceiverApp::~TizenReceiverApp(void) {
}

UiApp*
TizenReceiverApp::CreateInstance(void)
{
	return new TizenReceiverApp();
}

bool
TizenReceiverApp::OnAppInitializing(AppRegistry& appRegistry)
{
	mainForm = new (std::nothrow) Views::MainForm;
	setAppControlListener(mainForm);
	return true;
}

bool
TizenReceiverApp::OnAppInitialized(void)
{
	TizenReceiverFrame* pTizenReceiverFrame = new TizenReceiverFrame();
	pTizenReceiverFrame->Construct();
	pTizenReceiverFrame->SetName(L"TizenReceiver");
	pTizenReceiverFrame->Initialize(*mainForm);
	AddFrame(*pTizenReceiverFrame);

	return true;
}

bool
TizenReceiverApp::OnAppWillTerminate(void)
{
	return true;
}

bool TizenReceiverApp::OnAppTerminating(AppRegistry& appRegistry,
		bool forcedTermination) {
	return true;
}

void TizenReceiverApp::OnForeground(void) {
}

void TizenReceiverApp::OnBackground(void) {
}

void TizenReceiverApp::OnLowMemory(void) {
}

void TizenReceiverApp::OnBatteryLevelChanged(BatteryLevel batteryLevel) {
}

void TizenReceiverApp::OnScreenOn(void) {
}

void TizenReceiverApp::OnScreenOff(void) {
}


void TizenReceiverApp::setAppControlListener(Tizen::App::IAppControlProviderEventListener* listener) {
	using namespace Tizen::App;

	AppControlProviderManager* mgr = AppControlProviderManager::GetInstance();
	AppAssert(mgr);

	result r = mgr->SetAppControlProviderEventListener(listener);
	TryReturnVoid(!IsFailed(r), "Setting AppControlProviderEventListener failed. Error: %s",
			GetErrorMessage(r));
	AppLog("AppControlProviderEventListener was registered successfully");
}
