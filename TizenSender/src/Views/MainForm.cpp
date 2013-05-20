/*
 * MainForm.cpp
 *
 *  Created on: May 20, 2013
 *      Author: sergey
 */

#include "Views/MainForm.h"

namespace Views {


using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;

const String APP_OPERATION_ID = L"http://example.org/tizen/communication";
const String MainForm::ID = L"form_main";

static const int BUTTON_ID_FINDALL = 10;
static const int BUTTON_ID_SENDTEXT = 11;


MainForm::MainForm() {
}

MainForm::~MainForm() {
}


bool MainForm::Initialize() {
	result r = E_SUCCESS;
	r = Construct(ID);
	TryReturn(!IsFailed(r), false, "Can't initialize main form: %s", GetErrorMessage(r));

	return true;
}


result MainForm::OnInitializing() {

	btn_findAll = static_cast<Button*>(GetControl(L"btn_findAll"));
	btn_sendText = static_cast<Button*>(GetControl(L"btn_sendText"));

	AppAssert(btn_findAll && btn_sendText);
	btn_findAll->SetActionId(BUTTON_ID_FINDALL);
	btn_findAll->AddActionEventListener(*this);

	btn_sendText->SetActionId(BUTTON_ID_SENDTEXT);
	btn_sendText->AddActionEventListener(*this);

	txt_input = static_cast<EditArea*>(GetControl(L"txt_input"));
	txt_output = static_cast<TextBox*>(GetControl(L"txt_output"));
	AppAssert(txt_input && txt_output);

	return E_SUCCESS;
}


result MainForm::OnTerminating() {
	return E_SUCCESS;
}


void MainForm::OnActionPerformed(const Control& source, int actionId) {
	AppLog("Action perform, id: %d", actionId);
	switch(actionId) {
	case BUTTON_ID_FINDALL: {
		findAll();
		break;
	}
	case BUTTON_ID_SENDTEXT: {
		sendText();
		break;
	}
	default: {
		AppLogDebug("Unknown action size: %d", actionId);
		break;
	}
	}
}


void MainForm::OnAppControlCompleteResponseReceived(const AppId& appId, const String& operationId,
		AppCtrlResult opResult, const IMap* extraData) {
	AppLog("Response received");

	if (opResult == APP_CTRL_RESULT_SUCCEEDED && extraData) {
		String key = L"response";
		const String* value = static_cast<const String*>(extraData->GetValue(key));
		if (value) {
			showMessage(*value);
		} else {
			AppLogDebug("Args doesn't content nessessary keys");
		}
	}
}


void MainForm::findAll() {
	AppManager *mgr = AppManager::GetInstance();
	AppAssert(mgr);

	IList* ctrls = mgr->FindAppControlsN(&APP_OPERATION_ID, null, null, null);
	if (!ctrls) {
		showMessage(L"No one AppControl was found");
		return;
	}
	String controlsList;
	controlsList.Format(100, L"Total count: %d\n", ctrls->GetCount());

	IEnumerator* it = ctrls->GetEnumeratorN();
	for(it->Reset(); it->MoveNext() == E_SUCCESS; ) {
		AppControl* curr = static_cast<AppControl*>(it->GetCurrent());
		String line;
		line.Format(100, L"App name: %S; id: %S\n",
				curr->GetAppName().GetPointer(),
				curr->GetAppId().GetPointer());

		controlsList.Append(line);
	}
	showMessage(controlsList);
	delete it;
}


void MainForm::sendText() {
	HashMap* map = new HashMap(SingleObjectDeleter);
	map->Construct();
	String key = L"request";
	String value = txt_input->GetText();
	map->Add(key, value);

	result r = AppControl::FindAndStart(APP_OPERATION_ID, null, null, null, map, this);
	if (r != E_SUCCESS) {
		String mes;
		mes.Format(100, L"Can't launch app. Error: %s", GetErrorMessage(r));
		showMessage(mes);
	}
}


void MainForm::showMessage(const String& mes) {
	txt_output->SetText(mes);
	txt_output->RequestRedraw();
}

} /* namespace Views */
