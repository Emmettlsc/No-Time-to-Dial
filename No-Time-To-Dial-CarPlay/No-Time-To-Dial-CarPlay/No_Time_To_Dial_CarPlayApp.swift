//
//  No_Time_To_Dial_CarPlayApp.swift
//  No-Time-To-Dial-CarPlay
//
//  Created by Emmett Cocke on 12/6/23.
//

import SwiftUI
import CarPlay

@main
struct No_Time_To_Dial_CarPlayApp: App {
    @UIApplicationDelegateAdaptor(AppDelegate.self) var appDelegate

    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}

class AppDelegate: UIResponder, UIApplicationDelegate, CPApplicationDelegate {
    
    func application(_ application: UIApplication,
                     didConnectCarInterfaceController interfaceController: CPInterfaceController,
                     to window: CPWindow) {
        // Your CarPlay setup code goes here
        // This is where you set up the CarPlay interface
    }
    
    func application(_ application: UIApplication,
                     didDisconnectCarInterfaceController interfaceController: CPInterfaceController,
                     from window: CPWindow) {
        // Handle the disconnection of CarPlay here
    }

    // Other AppDelegate methods...
}
