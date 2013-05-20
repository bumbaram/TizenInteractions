/*
 * MainForm.h
 *
 *  Created on: May 20, 2013
 *      Author: sergey
 */

#ifndef MAINFORM_H_
#define MAINFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

namespace Views {

class MainForm: public Tizen::Ui::Controls::Form,
		public Tizen::Ui::IActionEventListener,
		public Tizen::App::IAppControlResponseListener {
public:
	static const Tizen::Base::String ID;
	MainForm();
	virtual ~MainForm();

	bool Initialize();

	result OnInitializing();
	result OnTerminating();

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	void OnAppControlCompleteResponseReceived(const Tizen::App::AppId& appId,
			const Tizen::Base::String& operationId,
			Tizen::App::AppCtrlResult appCtrlResult,
			const Tizen::Base::Collection::IMap* extraData);

private:
	void findAll();
	void sendText();
	void showMessage(const Tizen::Base::String& mes);

	Tizen::Ui::Controls::Button* btn_findAll;
	Tizen::Ui::Controls::Button* btn_sendText;

	Tizen::Ui::Controls::EditArea* txt_input;
	Tizen::Ui::Controls::TextBox* txt_output;
};

} /* namespace Views */
#endif /* MAINFORM_H_ */
