import Toybox.Application;
import Toybox.Lang;
import Toybox.WatchUi;

using Toybox.Application;
using Toybox.BluetoothLowEnergy as Ble;
 

class Demo2App extends Application.AppBase {
    private var bleDevice;

    function initialize() {
        AppBase.initialize();
    }

    // onStart() is called on application start up
    function onStart(state as Dictionary?) as Void {
        // bleDevice = new Ble.BleDelegate();
        bleDevice = new BleDevice();
        Ble.setDelegate(bleDevice);
        bleDevice.open();
    }

    // onStop() is called when your application is exiting
    function onStop(state as Dictionary?) as Void {
        bleDevice.close();
    }

    // Return the initial view of your application here
    // function getInitialView() as Array<Views or InputDelegates>? {
    //     return [ new Demo2View() ] as Array<Views or InputDelegates>;
    // }

    // function getInitialView() {
	// 	return [new DataField(bleDevice)];
	// }

    function getInitialView() {
        return [new DataField(bleDevice)];
    }

}

function getApp() as Demo2App {
    return Application.getApp() as Demo2App;
}