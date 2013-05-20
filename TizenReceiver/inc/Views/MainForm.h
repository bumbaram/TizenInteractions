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
#include <unique_ptr.h>

namespace Views {

class MainForm: public Tizen::Ui::Controls::Form,
		public Tizen::Ui::IActionEventListener,
		public Tizen::App::IAppControlProviderEventListener {
public:
	static const Tizen::Base::String ID;

	MainForm();
	virtual ~MainForm();

	bool Initialize();

	result OnInitializing();
	result OnTerminating();

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	void OnAppControlRequestReceived(RequestId reqId,
			const Tizen::Base::String& operationId,
			const Tizen::Base::String* uriData,
			const Tizen::Base::String* mimeType,
			const Tizen::Base::Collection::IMap* extraData);
private:
	void sendResponse();
	void showRequest(const Tizen::Base::String& mes);
	void showResponse(const Tizen::Base::String& mes);
	void handleReceivedRequest();

	Tizen::Ui::Controls::Button* btn_sendResponse;

	Tizen::Ui::Controls::TextBox* txt_request;
	Tizen::Ui::Controls::TextBox* txt_response;

	RequestId lastReqId;
	std::unique_ptr<Tizen::Base::String> lastRequest;
};

} /* namespace Views */
#endif /* MAINFORM_H_ */
