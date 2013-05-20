#ifndef _TIZENRECEIVER_H_
#define _TIZENRECEIVER_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include "Views/MainForm.h"


/**
 * [TizenReceiverApp] UiApp must inherit from UiApp class
 * which provides basic features necessary to define an UiApp.
 */
class TizenReceiverApp
	: public Tizen::App::UiApp
	, public Tizen::System::IScreenEventListener
{
public:
	/**
	 * [Test] UiApp must have a factory method that creates an instance of itself.
	 */
	static Tizen::App::UiApp* CreateInstance(void);

public:
	TizenReceiverApp(void);
	virtual~TizenReceiverApp(void);

public:
	virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);
	virtual bool OnAppInitialized(void); 
	virtual bool OnAppWillTerminate(void); 
	virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);
	virtual void OnForeground(void);
	virtual void OnBackground(void);
	virtual void OnLowMemory(void);
	virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);
	virtual void OnScreenOn(void);
	virtual void OnScreenOff(void);

private:
	void setAppControlListener(Tizen::App::IAppControlProviderEventListener* listener);

	Views::MainForm* mainForm;
};

#endif // _TIZENRECEIVER_H_
