//
//  ContentView.swift
//  No Time To Dial Watch App
//
//  Created by Emmett Cocke on 11/18/23.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject private var model: ItemListModel

    var body: some View {
        List {
            ForEach(model.devices.keys.sorted(), id: \.self) { deviceName in
                Section(header: Text("Device: \(deviceName)")) {
                    ForEach(model.devices[deviceName] ?? [], id: \.self) { message in
                        Text(message)
                    }
                }
            }
            
            if model.devices.isEmpty {
                Text("No Current Messages")
                    .foregroundStyle(.gray)
            }
        }
        .navigationTitle("Connections")
    }
}


#Preview {
    ContentView()
}
