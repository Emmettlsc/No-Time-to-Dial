using Toybox.WatchUi;
using Toybox.System;

class DataField extends WatchUi.SimpleDataField {
    private var bleDevice;

    function initialize(device) {
        SimpleDataField.initialize();
        bleDevice = device;
    }

    function compute(info) {
        // bleDevice.scan();
        return "test";
    }
}