/*
 * MainForm.cpp
 *
 *  Created on: May 20, 2013
 *      Author: sergey
 */

#include "Views/MainForm.h"

namespace Views {

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using std::unique_ptr;

const String MainForm::ID = L"form_main";

static const int BUTTON_ID_SENDRESPONSE = 10;


MainForm::MainForm(): lastReqId(-1), lastRequest(null) {
}

MainForm::~MainForm() {
}


bool MainForm::Initialize() {
	result r = E_SUCCESS;
	r = Construct(ID);
	TryReturn(!IsFailed(r), false, "Can't initialize main form. Error: %s", GetErrorMessage(r));

	return true;
}


result MainForm::OnInitializing() {

	btn_sendResponse = static_cast<Button*>(GetControl(L"btn_sendResponse"));
	AppAssert(btn_sendResponse);
	btn_sendResponse->SetActionId(BUTTON_ID_SENDRESPONSE);
	btn_sendResponse->AddActionEventListener(*this);
	btn_sendResponse->SetEnabled(false);

	txt_request = static_cast<TextBox*>(GetControl(L"txt_request"));
	txt_response = static_cast<TextBox*>(GetControl(L"txt_response"));
	AppAssert(txt_request && txt_response);

	handleReceivedRequest();

	return E_SUCCESS;
}


result MainForm::OnTerminating() {
	return E_SUCCESS;
}


void MainForm::OnActionPerformed(const Control& source, int actionId) {
	AppLog("Action performed, id: %d", actionId);
	switch(actionId) {
	case BUTTON_ID_SENDRESPONSE: {
		sendResponse();
		break;
	}
	default: {
		AppLogDebug("Unknown actionId: %d", actionId);
		break;
	}
	}
}


void MainForm::OnAppControlRequestReceived(RequestId reqId, const String& operationId,
		const String* uriData,
		const String* mimeType,
		const IMap* extraData) {
	AppLog("AppControl request was received");
	using namespace Tizen::App;

	Tizen::App::App* app = Tizen::App::App::GetInstance();
	AppAssert(app);

	lastReqId = reqId;

	if (extraData) {
		String key = L"request";
		const Object* value = extraData->GetValue(key);
		const String* req = static_cast<const String*>(value);
		if (req) {
			AppLog("Save request string");
			lastRequest = unique_ptr<String>(new String(*req));
		} else {
			AppLogDebug("ExtraData doesn't contain nessessary args");
		}
	}
	if (app->GetAppState() == INITIALIZING) {
		AppLog("AppControl request had been received while initializing");
	} else {
		handleReceivedRequest();
	}
}

void MainForm::handleReceivedRequest() {
	if (lastReqId != -1) {
		if (lastRequest.get()) {
			showRequest(*lastRequest);

			String response = *(new String(L"Handeled request: ")) + *lastRequest;
			showResponse(response);

			btn_sendResponse->SetEnabled(true);
			btn_sendResponse->RequestRedraw();
		} else {
			AppLogDebug("ReqId is exist, but extra data not valid.");
			using namespace Tizen::App;
			AppControlProviderManager* mgr =
					AppControlProviderManager::GetInstance();
			AppAssert(mgr);
			mgr->SendAppControlResult(lastReqId, APP_CTRL_RESULT_FAILED, null);
		}
	} else {
		AppLogDebug("last request doesn't exist");
	}
}


void MainForm::sendResponse() {
	HashMap* map = new (std::nothrow) HashMap;
	map->Construct();
	String key = L"response";
	String value = txt_response->GetText();
	map->Add(key, value);

	using namespace Tizen::App;

	AppControlProviderManager* mgr = AppControlProviderManager::GetInstance();
	AppAssert(mgr);
	mgr->SendAppControlResult(lastReqId, APP_CTRL_RESULT_SUCCEEDED, map);

	App* app = Tizen::App::App::GetInstance();
	AppAssert(app);

	app->Terminate();
}


void MainForm::showRequest(const String& mes) {
	txt_request->SetText(mes);
	txt_request->RequestRedraw();
}


void MainForm::showResponse(const String& mes) {
	txt_response->SetText(mes);
	txt_response->RequestRedraw();
}

} /* namespace Views */
